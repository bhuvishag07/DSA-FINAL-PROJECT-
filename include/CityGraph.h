#ifndef CITY_GRAPH_H
#define CITY_GRAPH_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Represents the overall traffic delay multiplier.
enum class TrafficLevel { LOW = 1, MEDIUM = 2, HEAVY = 3 };

// Stores details about a connection route between two locations.
struct Road {
  string destination;
  int baseTravelTime;
  int currentTravelTime;
  int tollCost;
};

// Manages the city map using an Adjacency List (Graph).
class CityGraph {
private:
  // Maps location names to a list of connected roads.
  unordered_map<string, vector<Road>> adjacencyList;
  TrafficLevel currentTraffic;

public:
  // Initializes the city graph with default traffic conditions.
  CityGraph() : currentTraffic(TrafficLevel::MEDIUM) {}

  void addIntersection(const string &name); // Add a new location node
  void addRoad(const string &src, const string &dest, int time,
               int toll);                 // Create a connected edge
  void updateTraffic(TrafficLevel level); // Adjust travel times dynamically
  void displayMap() const; // Show all graph locations and connections
  void viewConnectedLocations(
      const string &name) const; // Find immediate destinations

  const unordered_map<string, vector<Road>> &getAdjacencyList() const {
    return adjacencyList; // Directly access the graph structure
  }
  TrafficLevel getTrafficLevel() const {
    return currentTraffic;
  } // Return active traffic state
};

#endif
