#ifndef REQUEST_QUEUE_H
#define REQUEST_QUEUE_H

#include <iostream>
#include <queue>
#include <string>

struct RideRequest {
  int requestID;
  int riderID;
  std::string source;
  std::string destination;
};

class RequestQueue {
private:
  std::queue<RideRequest> requests;

public:
  void addRequest(const RideRequest &req);
  bool processRequest(RideRequest &req);
  void viewPendingRequests() const;
  int getQueueStatus() const;
  std::queue<RideRequest> getRequestQueue() const { return requests; }
};

#endif
