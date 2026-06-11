#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "CarSorter.h"
#include "RequestQueue.h"
#include "RiderManager.h"

class Dashboard {
private:
  RiderManager &riderManager;
  RequestQueue &requestQueue;
  CarSorter &carSorter;
  int completedTrips;
  double totalDistance;
  double totalRevenue;
  int carpoolsCreated;

public:
  Dashboard(RiderManager &rm, RequestQueue &rq, CarSorter &cs)
      : riderManager(rm), requestQueue(rq), carSorter(cs), completedTrips(0),
        totalDistance(0), totalRevenue(0), carpoolsCreated(0) {}

  void updateStats(int trips, double distance, double revenue, int carpools);
  void displayDashboard() const;
  void displayComplexityAnalysis() const;
  void displayBestRider() const;
};

#endif
