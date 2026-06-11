#include "../include/RequestQueue.h"
#include <iomanip>

void RequestQueue::addRequest(const RideRequest &req) {
  requests.push(req);
  std::cout << "Request added to queue! ID: " << req.requestID
            << " for Rider ID: " << req.riderID << std::endl;
}

bool RequestQueue::processRequest(RideRequest &req) {
  if (requests.empty()) {
    return false;
  }
  req = requests.front();
  requests.pop();
  return true;
}

void RequestQueue::viewPendingRequests() const {
  if (requests.empty()) {
    std::cout << "No pending requests." << std::endl;
    return;
  }
  std::queue<RideRequest> temp = requests;
  std::cout << "\n--- Pending Requests (Queue) ---" << std::endl;
  std::cout << std::left << std::setw(15) << "Request ID" << std::setw(15)
            << "Rider ID" << std::setw(20) << "Source" << std::setw(20)
            << "Destination" << std::endl;
  while (!temp.empty()) {
    RideRequest r = temp.front();
    std::cout << std::left << std::setw(15) << r.requestID << std::setw(15)
              << r.riderID << std::setw(20) << r.source << std::setw(20)
              << r.destination << std::endl;
    temp.pop();
  }
}

int RequestQueue::getQueueStatus() const { return requests.size(); }
