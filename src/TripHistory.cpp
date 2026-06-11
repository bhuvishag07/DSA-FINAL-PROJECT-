#include "../include/TripHistory.h"

void TripHistory::addTrip(const Trip &t) { trips.push_back(t); }

void TripHistory::viewAllTrips() const {
  if (trips.empty()) {
    std::cout << "No trip history found." << std::endl;
    return;
  }
  std::cout << "\n==============================================" << std::endl;
  std::cout << "             COMPLETED TRIPS HISTORY" << std::endl;
  std::cout << "==============================================" << std::endl;
  for (const auto &t : trips) {
    std::cout << "Trip ID:     " << t.tripID << std::endl;
    std::cout << "Riders:      ";
    for (size_t i = 0; i < t.riderNames.size(); ++i) {
      std::cout << t.riderNames[i]
                << (i == t.riderNames.size() - 1 ? "" : ", ");
    }
    std::cout << "\nVehicle:     " << t.carModel << std::endl;
    std::cout << "Cost:        \xe2\x82\xb9" << std::fixed
              << std::setprecision(2) << t.totalCost << std::endl;
    std::cout << "Status:      Completed" << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
  }
}

void TripHistory::searchTrip(std::string id) const {
  for (const auto &t : trips) {
    if (t.tripID == id) {
      std::cout << "Trip Found!" << std::endl;
      // (Re-use display logic or simple print)
      std::cout << "ID: " << t.tripID << " | Riders: " << t.riderNames.size()
                << " | Cost: \xe2\x82\xb9" << t.totalCost << std::endl;
      return;
    }
  }
  std::cout << "Trip not found." << std::endl;
}
