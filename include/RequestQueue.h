#ifndef REQUEST_QUEUE_H
#define REQUEST_QUEUE_H

#include <iostream>
#include <queue>
#include <string>

using namespace std;

// Encapsulates all necessary details for a single ride booking.
struct RideRequest {
  int requestID;
  int riderID;
  string source;
  string destination;
};

// Manages incoming ride bookings in a First In First Out (FIFO) manner.
class RequestQueue {
private:
  queue<RideRequest> requests; // Standard Queue

  // Ensures fairness because requests are processed
  // sequentially based on arrival time.

public:
  void addRequest(const RideRequest &req); // Append booking to end of queue
  bool processRequest(RideRequest &req);   // Retrieve and handle next booking
  void viewPendingRequests() const;        // Check existing line of requests
  int getQueueStatus() const;              // Return number of waiting bookings
  queue<RideRequest> getRequestQueue() const {
    return requests;
  } // Get full queue copy
};

#endif
