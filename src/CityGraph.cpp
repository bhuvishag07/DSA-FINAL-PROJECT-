#include "../include/CityGraph.h"
#include <iomanip>

void CityGraph::addIntersection(const std::string &name) {
  if (adjacencyList.find(name) == adjacencyList.end()) {
    adjacencyList[name] = std::vector<Road>();
  }
}

void CityGraph::addRoad(const std::string &src, const std::string &dest,
                        int time, int toll) {
  addIntersection(src);
  addIntersection(dest);
  adjacencyList[src].push_back({dest, time, time, toll});
  adjacencyList[dest].push_back(
      {src, time, time, toll}); // Assuming undirected roads for simplicity
}

void CityGraph::updateTraffic(TrafficLevel level) {
  currentTraffic = level;
  double multiplier = (double)level;
  for (auto &pair : adjacencyList) {
    for (auto &road : pair.second) {
      road.currentTravelTime =
          (int)(road.baseTravelTime * (multiplier * 0.5 + 0.5));
    }
  }
  std::cout << "Traffic updated to Level: " << (int)level << std::endl;
}

void CityGraph::displayMap() const {
  std::cout << "\n--- Bengaluru City Map (Adjacency List) ---" << std::endl;
  for (const auto &pair : adjacencyList) {
    std::cout << pair.first << " -> ";
    for (const auto &road : pair.second) {
      std::cout << "[" << road.destination << ": " << road.currentTravelTime
                << "m (\xe2\x8a\xbb" << road.baseTravelTime
                << "m), \xe2\x82\xb9" << road.tollCost << "] ";
    }
    std::cout << std::endl;
  }
}

void CityGraph::viewConnectedLocations(const std::string &name) const {
  if (adjacencyList.find(name) == adjacencyList.end()) {
    std::cout << "Location not found in map." << std::endl;
    return;
  }
  std::cout << "Roads from " << name << ":" << std::endl;
  for (const auto &road : adjacencyList.at(name)) {
    std::cout << "- To " << road.destination << " (" << road.currentTravelTime
              << " mins, Toll: \xe2\x82\xb9" << road.tollCost << ")"
              << std::endl;
  }
}
