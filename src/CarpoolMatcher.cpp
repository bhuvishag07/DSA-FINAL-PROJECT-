#include "../include/CarpoolMatcher.h"
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>

using namespace std;

// Calculates rider compatibility before forming groups.
void CarpoolMatcher::calculateCompatibility() {
  cout << "\n==============================================" << endl;
  cout << "        RIDER COMPATIBILITY ANALYSIS" << endl;
  cout << "==============================================" << endl;

  // For demo, we analyze the next 3 riders in the FIFO queue.
  queue<RideRequest> temp = requestQueue.getRequestQueue();
  vector<RideRequest> list;
  int c = 0;
  while (!temp.empty() && c < 3) {
    list.push_back(temp.front());
    temp.pop();
    c++;
  }

  if (list.size() < 2) {
    cout << "Not enough riders for compatibility analysis." << endl;
    return;
  }

  // Iterate over pair combinations to generate compatibility scores.
  for (size_t i = 0; i < list.size(); i++) {
    for (size_t j = i + 1; j < list.size(); j++) {
      int score =
          85 + (rand() % 10); // Simulated scoring logic based on destination
      cout << list[i].source << " \xe2\x86\x94 " << list[j].source << " : "
           << score << "%" << endl;
    }
  }

  cout << "\nRecommended Carpool Group: ";
  for (const auto &r : list) {
    Rider rider;
    riderManager.searchRider(r.riderID, rider); // Log(N) search in BST
    cout << rider.name << " ";
  }
  cout << "\n==============================================" << endl;
}

// Responsible for selecting the most suitable vehicle for the generated group
// and executing the final ride allocation.
CarpoolGroup CarpoolMatcher::matchAndOptimize() {
  CarpoolGroup group;
  if (requestQueue.getQueueStatus() < 1) {
    cout << "Not enough ride requests." << endl;
    return group;
  }

  // Process waiting users from the RequestQueue.
  while (group.riders.size() < 3 && requestQueue.getQueueStatus() > 0) {
    RideRequest req;
    requestQueue.processRequest(req);
    group.riders.push_back(req);
  }

  // Extract the highest-capacity vehicle from the Max Heap.
  if (!carSorter.allocateBestCar(group.selectedCar))
    return group;

  string destination = group.riders[0].destination;
  group.pickupSequence.push_back("Koramangala");
  for (const auto &r : group.riders)
    group.pickupSequence.push_back(r.source);

  vector<string> stops = group.pickupSequence;
  stops.push_back(destination);

  // Compute total traversal path using RoutePlanner graph operations.
  RouteResult route = routePlanner.calculateMultiStopRoute(stops);

  if (route.found) {
    group.totalTravelTime = route.totalTime;
    group.totalDistance = route.totalTime * 0.8; // Simulated distance
    group.totalCost = (route.totalTime * 7) + route.totalToll;
    group.dropSequence.push_back(destination);

    // Fair Split Logic based on distance/time ratios.
    double basePerRider = group.totalCost / group.riders.size();
    for (size_t i = 0; i < group.riders.size(); i++) {
      group.fairSplits.push_back(basePerRider - (i * 10) +
                                 5); // Simulated fair split based on distance
    }

    // Add to Trip History
    Trip t;
    t.tripID = "TRP" + to_string(100 + tripHistory.getTrips().size() + 1);
    for (auto &r : group.riders) {
      t.riderIDs.push_back(r.riderID);
      Rider rider;
      riderManager.searchRider(r.riderID, rider);
      t.riderNames.push_back(rider.name);

      // Award rider stats to persist history points.
      rider.rideHistoryCount++;
      rider.moneySaved += 50.0;
      rider.sharedDistance += (group.totalDistance / group.riders.size());
      riderManager.updateRider(rider.riderID, rider); // Update BST record
    }
    t.carModel = group.selectedCar.vehicleType + " (" +
                 group.selectedCar.driverName + ")";
    t.totalCost = group.totalCost;
    t.travelTime = group.totalTravelTime;
    tripHistory.addTrip(t); // Append completed run array
  }
  return group;
}

// Output detailed metrics and breakdown of the successfully matched group.
void CarpoolMatcher::displayCarpoolSummary(const CarpoolGroup &group) const {
  if (group.riders.empty())
    return;

  cout << "\n==============================================" << endl;
  cout << "        SMARTRIDE CARPOOL MATCH SUMMARY" << endl;
  cout << "==============================================" << endl;
  cout << "Selected Vehicle: " << group.selectedCar.vehicleType
       << " (Driver: " << group.selectedCar.driverName << ")" << endl;

  cout << "\n--- FARE SPLIT ANALYSIS ---" << endl;
  for (size_t i = 0; i < group.riders.size(); i++) {
    Rider r;
    riderManager.searchRider(group.riders[i].riderID, r);
    cout << left << setw(15) << r.name << ": \xe2\x82\xb9" << fixed
         << setprecision(2) << group.fairSplits[i] << endl;
  }

  cout << "\n----------------------------------------------" << endl;
  cout << "Pickup Sequence: ";
  for (size_t i = 0; i < group.pickupSequence.size(); ++i) {
    cout << group.pickupSequence[i]
         << (i == group.pickupSequence.size() - 1 ? "" : " -> ");
  }
  cout << "\nDrop Sequence:   ";
  for (size_t i = 0; i < group.dropSequence.size(); ++i) {
    cout << group.dropSequence[i]
         << (i == group.dropSequence.size() - 1 ? "" : " -> ");
  }
  cout << "\n----------------------------------------------" << endl;
  cout << "Total Travel Time: " << group.totalTravelTime << " Minutes" << endl;
  cout << "Total Distance:    " << group.totalDistance << " KM (Estimated)"
       << endl;
  cout << "Total Trip Cost:   \xe2\x82\xb9" << fixed << setprecision(2)
       << group.totalCost << endl;
  cout << "==============================================" << endl;

  generateEfficiencyReport(group);
}

// Display summarized information regarding trip environmental advantages.
void CarpoolMatcher::generateEfficiencyReport(const CarpoolGroup &group) const {
  cout << "\n==============================================" << endl;
  cout << "          CARPOOL EFFICIENCY REPORT" << endl;
  cout << "==============================================" << endl;
  cout << "Riders Grouped:    " << group.riders.size() << endl;
  cout << "Cars Saved:        " << group.riders.size() - 1 << endl;
  cout << "Distance Saved:    " << (group.riders.size() - 1) * 8 << " KM"
       << endl;
  cout << "Money Saved:       \xe2\x82\xb9" << (group.riders.size() - 1) * 120
       << endl;
  cout << "CO2 Reduction:     " << (group.riders.size() - 1) * 1.2 << " KG"
       << endl;
  cout << "Overall Efficiency: EXCELLENT" << endl;
  cout << "==============================================" << endl;
}
