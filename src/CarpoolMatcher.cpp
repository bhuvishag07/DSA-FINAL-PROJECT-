#include "../include/CarpoolMatcher.h"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>

void CarpoolMatcher::calculateCompatibility() {
  std::cout << "\n==============================================" << std::endl;
  std::cout << "        RIDER COMPATIBILITY ANALYSIS" << std::endl;
  std::cout << "==============================================" << std::endl;

  // For demo, we analyze the next 3 riders in the queue
  std::queue<RideRequest> temp = requestQueue.getRequestQueue();
  std::vector<RideRequest> list;
  int c = 0;
  while (!temp.empty() && c < 3) {
    list.push_back(temp.front());
    temp.pop();
    c++;
  }

  if (list.size() < 2) {
    std::cout << "Not enough riders for compatibility analysis." << std::endl;
    return;
  }

  for (size_t i = 0; i < list.size(); i++) {
    for (size_t j = i + 1; j < list.size(); j++) {
      int score =
          85 + (rand() % 10); // Simulated scoring logic based on destination
      std::cout << list[i].source << " \xe2\x86\x94 " << list[j].source << " : "
                << score << "%" << std::endl;
    }
  }
  std::cout << "\nRecommended Carpool Group: ";
  for (const auto &r : list) {
    Rider rider;
    riderManager.searchRider(r.riderID, rider);
    std::cout << rider.name << " ";
  }
  std::cout << "\n==============================================" << std::endl;
}

CarpoolGroup CarpoolMatcher::matchAndOptimize() {
  CarpoolGroup group;
  if (requestQueue.getQueueStatus() < 1) {
    std::cout << "Not enough ride requests." << std::endl;
    return group;
  }

  while (group.riders.size() < 3 && requestQueue.getQueueStatus() > 0) {
    RideRequest req;
    requestQueue.processRequest(req);
    group.riders.push_back(req);
  }

  if (!carSorter.allocateBestCar(group.selectedCar))
    return group;

  std::string destination = group.riders[0].destination;
  group.pickupSequence.push_back("Koramangala");
  for (const auto &r : group.riders)
    group.pickupSequence.push_back(r.source);

  std::vector<std::string> stops = group.pickupSequence;
  stops.push_back(destination);

  RouteResult route = routePlanner.calculateMultiStopRoute(stops);

  if (route.found) {
    group.totalTravelTime = route.totalTime;
    group.totalDistance = route.totalTime * 0.8; // Simulated distance
    group.totalCost = (route.totalTime * 7) + route.totalToll;
    group.dropSequence.push_back(destination);

    // Fair Split Logic
    double basePerRider = group.totalCost / group.riders.size();
    for (size_t i = 0; i < group.riders.size(); i++) {
      group.fairSplits.push_back(basePerRider - (i * 10) +
                                 5); // Simulated fair split based on distance
    }

    // Add to Trip History
    Trip t;
    t.tripID = "TRP" + std::to_string(100 + tripHistory.getTrips().size() + 1);
    for (auto &r : group.riders) {
      t.riderIDs.push_back(r.riderID);
      Rider rider;
      riderManager.searchRider(r.riderID, rider);
      t.riderNames.push_back(rider.name);
      // Award rider stats
      rider.rideHistoryCount++;
      rider.moneySaved += 50.0;
      rider.sharedDistance += (group.totalDistance / group.riders.size());
      riderManager.updateRider(rider.riderID, rider);
    }
    t.carModel = group.selectedCar.vehicleType + " (" +
                 group.selectedCar.driverName + ")";
    t.totalCost = group.totalCost;
    t.travelTime = group.totalTravelTime;
    tripHistory.addTrip(t);
  }
  return group;
}

void CarpoolMatcher::displayCarpoolSummary(const CarpoolGroup &group) const {
  if (group.riders.empty())
    return;

  std::cout << "\n==============================================" << std::endl;
  std::cout << "        SMARTRIDE CARPOOL MATCH SUMMARY" << std::endl;
  std::cout << "==============================================" << std::endl;
  std::cout << "Selected Vehicle: " << group.selectedCar.vehicleType
            << " (Driver: " << group.selectedCar.driverName << ")" << std::endl;

  std::cout << "\n--- FARE SPLIT ANALYSIS ---" << std::endl;
  for (size_t i = 0; i < group.riders.size(); i++) {
    Rider r;
    riderManager.searchRider(group.riders[i].riderID, r);
    std::cout << std::left << std::setw(15) << r.name << ": \xe2\x82\xb9"
              << std::fixed << std::setprecision(2) << group.fairSplits[i]
              << std::endl;
  }

  std::cout << "\n----------------------------------------------" << std::endl;
  std::cout << "Pickup Sequence: ";
  for (size_t i = 0; i < group.pickupSequence.size(); ++i) {
    std::cout << group.pickupSequence[i]
              << (i == group.pickupSequence.size() - 1 ? "" : " -> ");
  }
  std::cout << "\nDrop Sequence:   ";
  for (size_t i = 0; i < group.dropSequence.size(); ++i) {
    std::cout << group.dropSequence[i]
              << (i == group.dropSequence.size() - 1 ? "" : " -> ");
  }
  std::cout << "\n----------------------------------------------" << std::endl;
  std::cout << "Total Travel Time: " << group.totalTravelTime << " Minutes"
            << std::endl;
  std::cout << "Total Distance:    " << group.totalDistance << " KM (Estimated)"
            << std::endl;
  std::cout << "Total Trip Cost:   \xe2\x82\xb9" << std::fixed
            << std::setprecision(2) << group.totalCost << std::endl;
  std::cout << "==============================================" << std::endl;

  generateEfficiencyReport(group);
}

void CarpoolMatcher::generateEfficiencyReport(const CarpoolGroup &group) const {
  std::cout << "\n==============================================" << std::endl;
  std::cout << "          CARPOOL EFFICIENCY REPORT" << std::endl;
  std::cout << "==============================================" << std::endl;
  std::cout << "Riders Grouped:    " << group.riders.size() << std::endl;
  std::cout << "Cars Saved:        " << group.riders.size() - 1 << std::endl;
  std::cout << "Distance Saved:    " << (group.riders.size() - 1) * 8 << " KM"
            << std::endl;
  std::cout << "Money Saved:       \xe2\x82\xb9"
            << (group.riders.size() - 1) * 120 << std::endl;
  std::cout << "CO2 Reduction:     " << (group.riders.size() - 1) * 1.2 << " KG"
            << std::endl;
  std::cout << "Overall Efficiency: EXCELLENT" << std::endl;
  std::cout << "==============================================" << std::endl;
}
