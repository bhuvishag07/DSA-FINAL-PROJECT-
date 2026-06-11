#ifndef TRIP_HISTORY_H
#define TRIP_HISTORY_H

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct Trip {
  std::string tripID;
  std::vector<int> riderIDs;
  std::vector<std::string> riderNames;
  std::string carModel;
  std::vector<std::string> path;
  double totalCost;
  int travelTime;
  std::string date;
};

class TripHistory {
private:
  std::vector<Trip> trips;

public:
  void addTrip(const Trip &t);
  void viewAllTrips() const;
  void searchTrip(std::string id) const;
  const std::vector<Trip> &getTrips() const { return trips; }
};

#endif
