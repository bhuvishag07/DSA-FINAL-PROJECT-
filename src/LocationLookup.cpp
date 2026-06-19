#include "../include/LocationLookup.h"
#include <iomanip>

using namespace std;

// Register coordinates correlated with an active ride request.
void LocationLookup::addLocation(int requestID, double lat, double lon) {
  // O(1) average time complexity for Hash Map insertion.
  locationMap[requestID] = {lat, lon};
}

// Find latitude and longitude for a specific request ID in O(1) time.
bool LocationLookup::searchLocation(int requestID, Location &loc) {
  if (locationMap.find(requestID) != locationMap.end()) {
    loc = locationMap[requestID];
    return true;
  }
  return false;
}

// Override previous coordinate details for a specific request ID.
bool LocationLookup::updateLocation(int requestID, double lat, double lon) {
  if (locationMap.find(requestID) != locationMap.end()) {
    locationMap[requestID] = {lat, lon};
    return true;
  }
  return false;
}

// Traverse the unordered_map to display all currently tracked coordinates.
void LocationLookup::displayAllLocations() const {
  cout << "\n--- Location Lookup Table (Hash Map) ---" << endl;
  cout << left << setw(15) << "Request ID" << setw(15) << "Latitude" << setw(15)
       << "Longitude" << endl;
  for (const auto &pair : locationMap) {
    cout << left << setw(15) << pair.first << setw(15) << pair.second.latitude
         << setw(15) << pair.second.longitude << endl;
  }
}
