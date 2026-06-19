#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "CarSorter.h"
#include "RequestQueue.h"
#include "RiderManager.h"

using namespace std;

// Provides a summary of application statistics and runtime analysis.
class Dashboard {
private:
  // References to active sub-systems for data collection.
  RiderManager &riderManager;
  RequestQueue &requestQueue;
  CarSorter &carSorter;

  int completedTrips;
  double totalDistance;
  double totalRevenue;
  int carpoolsCreated;

public:
  // Initializes the dashboard tracking system using core modules.
  Dashboard(RiderManager &rm, RequestQueue &rq, CarSorter &cs)
      : riderManager(rm), requestQueue(rq), carSorter(cs), completedTrips(0),
        totalDistance(0), totalRevenue(0), carpoolsCreated(0) {}

  void updateStats(int trips, double distance, double revenue,
                   int carpools);         // Accumulate application usage data
  void displayDashboard() const;          // Present live system metrics
  void displayComplexityAnalysis() const; // Output Big-O algorithms review
  void displayBestRider() const; // Display the most active user in the network
};

#endif
