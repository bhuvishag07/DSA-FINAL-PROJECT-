#ifndef CARPOOL_MATCHER_H
#define CARPOOL_MATCHER_H

#include "CarSorter.h"
#include "LocationLookup.h"
#include "RequestQueue.h"
#include "RiderManager.h"
#include "RoutePlanner.h"
#include "TripHistory.h"
#include <vector>

using namespace std;

// Stores complete information about a generated carpool group.
struct CarpoolGroup {
  Car selectedCar;
  vector<RideRequest> riders;
  vector<string> pickupSequence;
  vector<string> dropSequence;
  int totalTravelTime;
  double totalDistance;
  double totalCost;
  vector<double> fairSplits; // Cost per individual rider
  double efficiencyScore;
};

// Responsible for matching riders to the most optimal carpool groups.
class CarpoolMatcher {
private:
  RequestQueue &requestQueue;
  CarSorter &carSorter;
  RoutePlanner &routePlanner;
  RiderManager &riderManager;
  LocationLookup &locationLookup;
  TripHistory &tripHistory;

public:
  // Initializes the matcher with references to all core subsystems.
  CarpoolMatcher(RequestQueue &rq, CarSorter &cs, RoutePlanner &rp,
                 RiderManager &rm, LocationLookup &ll, TripHistory &th)
      : requestQueue(rq), carSorter(cs), routePlanner(rp), riderManager(rm),
        locationLookup(ll), tripHistory(th) {}

  void calculateCompatibility();   // Evaluates compatibility between riders
  CarpoolGroup matchAndOptimize(); // Creates the optimal carpool group based on
                                   // requests and cars available
  void displayCarpoolSummary(const CarpoolGroup &group)
      const; // Previews the resulting carpool allocation
  void generateEfficiencyReport(const CarpoolGroup &group)
      const; // Calculates and outputs the benefits of the group ride
};

#endif
