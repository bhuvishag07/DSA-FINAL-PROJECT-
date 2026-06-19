#ifndef LOCATION_LOOKUP_H
#define LOCATION_LOOKUP_H

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// Represents the geographic coordinates of a location.
struct Location {
  double latitude;
  double longitude;
};

// Provides rapid O(1) access to coordinate data using a Hash Table.
class LocationLookup {
private:
  unordered_map<int, Location> locationMap; // Hash Table

  // Used to map a unique request ID to a specific map location quickly.

public:
  void addLocation(int requestID, double lat,
                   double lon); // Insert new location into the system
  bool searchLocation(int requestID,
                      Location &loc); // Lookup existing coordinate data
  bool updateLocation(int requestID, double lat,
                      double lon);  // Modify an existing location entry
  void displayAllLocations() const; // Print all tracked geographic data
};

#endif
