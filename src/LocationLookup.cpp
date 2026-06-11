#include "../include/LocationLookup.h"
#include <iomanip>

void LocationLookup::addLocation(int requestID, double lat, double lon) {
  locationMap[requestID] = {lat, lon};
}

bool LocationLookup::searchLocation(int requestID, Location &loc) {
  if (locationMap.find(requestID) != locationMap.end()) {
    loc = locationMap[requestID];
    return true;
  }
  return false;
}

bool LocationLookup::updateLocation(int requestID, double lat, double lon) {
  if (locationMap.find(requestID) != locationMap.end()) {
    locationMap[requestID] = {lat, lon};
    return true;
  }
  return false;
}

void LocationLookup::displayAllLocations() const {
  std::cout << "\n--- Location Lookup Table (Hash Map) ---" << std::endl;
  std::cout << std::left << std::setw(15) << "Request ID" << std::setw(15)
            << "Latitude" << std::setw(15) << "Longitude" << std::endl;
  for (const auto &pair : locationMap) {
    std::cout << std::left << std::setw(15) << pair.first << std::setw(15)
              << pair.second.latitude << std::setw(15) << pair.second.longitude
              << std::endl;
  }
}
