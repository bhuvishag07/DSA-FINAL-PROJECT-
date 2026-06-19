#include "../include/RequestQueue.h"
#include <iomanip>

using namespace std;

// Insert request into FIFO queue for fair processing.
void RequestQueue::addRequest(const RideRequest &req) {
  requests.push(req);
  cout << "Request added to queue! ID: " << req.requestID
       << " for Rider ID: " << req.riderID << endl;
}

// Hand off the oldest waiting request from the front of the queue.
bool RequestQueue::processRequest(RideRequest &req) {
  if (requests.empty()) {
    return false;
  }
  req = requests.front(); // Read oldest element
  requests.pop();         // Remote it
  return true;
}

// Copy and display all currently unmet requests without disrupting the real
// queue.
void RequestQueue::viewPendingRequests() const {
  if (requests.empty()) {
    cout << "No pending requests." << endl;
    return;
  }
  queue<RideRequest> temp = requests;
  cout << "\n--- Pending Requests (Queue) ---" << endl;
  cout << left << setw(15) << "Request ID" << setw(15) << "Rider ID" << setw(20)
       << "Source" << setw(20) << "Destination" << endl;
  while (!temp.empty()) {
    RideRequest r = temp.front();
    cout << left << setw(15) << r.requestID << setw(15) << r.riderID << setw(20)
         << r.source << setw(20) << r.destination << endl;
    temp.pop();
  }
}

int RequestQueue::getQueueStatus() const { return requests.size(); }
