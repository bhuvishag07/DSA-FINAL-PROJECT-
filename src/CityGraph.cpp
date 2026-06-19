#include "../include/CityGraph.h"
#include <iomanip>

using namespace std;

// Allocate space for an upcoming location inside our adjacency list.
void CityGraph::addIntersection(const string &name) {
  if (adjacencyList.find(name) == adjacencyList.end()) {
    adjacencyList[name] = vector<Road>();
  }
}

// Add bidirectional road connection between locations.
void CityGraph::addRoad(const string &src, const string &dest, int time,
                        int toll) {
  addIntersection(src);
  addIntersection(dest);

  // Create edges mapping both directions to simulate two-way roads.
  adjacencyList[src].push_back({dest, time, time, toll});
  adjacencyList[dest].push_back(
      {src, time, time, toll}); // Assuming undirected roads for simplicity
}

// Adjust base graph weights using a simulated multiplier map based on
// congestion.
void CityGraph::updateTraffic(TrafficLevel level) {
  currentTraffic = level;
  double multiplier = (double)level;

  // Re-calculate effective travel durations locally inside Adjacency List
  // edges.
  for (auto &pair : adjacencyList) {
    for (auto &road : pair.second) {
      road.currentTravelTime =
          (int)(road.baseTravelTime * (multiplier * 0.5 + 0.5));
    }
  }
  cout << "Traffic updated to Level: " << (int)level << endl;
}

// Draw the underlying data structure representing connected neighborhoods.
void CityGraph::displayMap() const {
  cout << "\n--- Bengaluru City Map (Adjacency List) ---" << endl;
  for (const auto &pair : adjacencyList) {
    cout << pair.first << " -> ";
    for (const auto &road : pair.second) {
      cout << "[" << road.destination << ": " << road.currentTravelTime
           << "m (\xe2\x8a\xbb" << road.baseTravelTime << "m), \xe2\x82\xb9"
           << road.tollCost << "] ";
    }
    cout << endl;
  }
}

// Display immediately traversable nodes from a specified origin point.
void CityGraph::viewConnectedLocations(const string &name) const {
  if (adjacencyList.find(name) == adjacencyList.end()) {
    cout << "Location not found in map." << endl;
    return;
  }
  cout << "Roads from " << name << ":" << endl;
  for (const auto &road : adjacencyList.at(name)) {
    cout << "- To " << road.destination << " (" << road.currentTravelTime
         << " mins, Toll: \xe2\x82\xb9" << road.tollCost << ")" << endl;
  }
}
