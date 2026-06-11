#ifndef LOCATION_LOOKUP_H
#define LOCATION_LOOKUP_H

#include <iostream>
#include <string>
#include <unordered_map>

struct Location {
  double latitude;
  double longitude;
};

class LocationLookup {
private:
  std::unordered_map<int, Location> locationMap; // Hash Table

public:
  void addLocation(int requestID, double lat, double lon);
  bool searchLocation(int requestID, Location &loc);
  bool updateLocation(int requestID, double lat, double lon);
  void displayAllLocations() const;
};

#endif
