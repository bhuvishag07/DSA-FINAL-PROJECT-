#include "../include/TripHistory.h"

using namespace std;

// Add a finalized trip record to the sequential log.
void TripHistory::addTrip(const Trip &t) { trips.push_back(t); }

// Present all historical records stored in memory over time.
void TripHistory::viewAllTrips() const {
  if (trips.empty()) {
    cout << "No trip history found." << endl;
    return;
  }
  cout << "\n==============================================" << endl;
  cout << "             COMPLETED TRIPS HISTORY" << endl;
  cout << "==============================================" << endl;
  for (const auto &t : trips) {
    cout << "Trip ID:     " << t.tripID << endl;
    cout << "Riders:      ";
    for (size_t i = 0; i < t.riderNames.size(); ++i) {
      cout << t.riderNames[i] << (i == t.riderNames.size() - 1 ? "" : ", ");
    }
    cout << "\nVehicle:     " << t.carModel << endl;
    cout << "Cost:        \xe2\x82\xb9" << fixed << setprecision(2)
         << t.totalCost << endl;
    cout << "Status:      Completed" << endl;
    cout << "----------------------------------------------" << endl;
  }
}

// Interrogates the Vector linearly to discover a target trip by ID.
void TripHistory::searchTrip(string id) const {
  for (const auto &t : trips) {
    if (t.tripID == id) {
      cout << "Trip Found!" << endl;
      // (Re-use display logic or simple print)
      cout << "ID: " << t.tripID << " | Riders: " << t.riderNames.size()
           << " | Cost: \xe2\x82\xb9" << t.totalCost << endl;
      return;
    }
  }
  cout << "Trip not found." << endl;
}
