#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include "CityGraph.h"
#include <map>
#include <string>
#include <vector>

using namespace std;

// Structure holding the finalized path data returned from route calculations.
struct RouteResult {
  vector<string> path;
  int totalTime;
  int totalToll;
  bool found;

  RouteResult() : totalTime(0), totalToll(0), found(false) {}
};

// Responsible for resolving navigation algorithms across the CityGraph.
class RoutePlanner {
private:
  const CityGraph &cityGraph;

public:
  // Inject context of the city layout for algorithm processing.
  RoutePlanner(const CityGraph &graph) : cityGraph(graph) {}

  RouteResult calculateFastestRoute(
      const string &start,
      const string &end); // Implement Dijkstra's logic optimizing for shortest
                          // travel time
  RouteResult calculateCheapestRoute(
      const string &start,
      const string &end); // Implement Dijkstra's logic optimizing for lowest
                          // financial cost
  RouteResult calculateBalancedRoute(
      const string &start,
      const string &end); // Implement algorithmic blend of time vs money

  // For Multi-stop
  RouteResult calculateMultiStopRoute(
      const vector<string>
          &stops); // Generate TSP/Graph logic for sequence points
};

#endif
