#ifndef TRIP_HISTORY_H
#define TRIP_HISTORY_H

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Logs completed sessions including participant data.
struct Trip {
  string tripID;
  vector<int> riderIDs;
  vector<string> riderNames;
  string carModel;
  vector<string> path;
  double totalCost;
  int travelTime;
  string date;
};

// Keeps track of the past journeys via dynamic arrays (std::vector).
class TripHistory {
private:
  vector<Trip> trips; // Sequential Log Array

public:
  void addTrip(const Trip &t);      // Push trip record into the historical log
  void viewAllTrips() const;        // Present past records linearly
  void searchTrip(string id) const; // Find target trip by its unique ID string
  const vector<Trip> &getTrips() const {
    return trips;
  } // Expose completed records
};

#endif
