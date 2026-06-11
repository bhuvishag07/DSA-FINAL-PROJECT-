#ifndef CARPOOL_MATCHER_H
#define CARPOOL_MATCHER_H

#include "CarSorter.h"
#include "LocationLookup.h"
#include "RequestQueue.h"
#include "RiderManager.h"
#include "RoutePlanner.h"
#include "TripHistory.h"
#include <vector>

struct CarpoolGroup {
  Car selectedCar;
  std::vector<RideRequest> riders;
  std::vector<std::string> pickupSequence;
  std::vector<std::string> dropSequence;
  int totalTravelTime;
  double totalDistance;
  double totalCost;
  std::vector<double> fairSplits; // Cost per individual rider
  double efficiencyScore;
};

class CarpoolMatcher {
private:
  RequestQueue &requestQueue;
  CarSorter &carSorter;
  RoutePlanner &routePlanner;
  RiderManager &riderManager;
  LocationLookup &locationLookup;
  TripHistory &tripHistory;

public:
  CarpoolMatcher(RequestQueue &rq, CarSorter &cs, RoutePlanner &rp,
                 RiderManager &rm, LocationLookup &ll, TripHistory &th)
      : requestQueue(rq), carSorter(cs), routePlanner(rp), riderManager(rm),
        locationLookup(ll), tripHistory(th) {}

  void calculateCompatibility();
  CarpoolGroup matchAndOptimize();
  void displayCarpoolSummary(const CarpoolGroup &group) const;
  void generateEfficiencyReport(const CarpoolGroup &group) const;
};

#endif
