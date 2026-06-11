#ifndef CITY_GRAPH_H
#define CITY_GRAPH_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

enum class TrafficLevel { LOW = 1, MEDIUM = 2, HEAVY = 3 };

struct Road {
  std::string destination;
  int baseTravelTime;
  int currentTravelTime;
  int tollCost;
};

class CityGraph {
private:
  std::unordered_map<std::string, std::vector<Road>> adjacencyList;
  TrafficLevel currentTraffic;

public:
  CityGraph() : currentTraffic(TrafficLevel::MEDIUM) {}
  void addIntersection(const std::string &name);
  void addRoad(const std::string &src, const std::string &dest, int time,
               int toll);
  void updateTraffic(TrafficLevel level);
  void displayMap() const;
  void viewConnectedLocations(const std::string &name) const;
  const std::unordered_map<std::string, std::vector<Road>> &
  getAdjacencyList() const {
    return adjacencyList;
  }
  TrafficLevel getTrafficLevel() const { return currentTraffic; }
};

#endif
