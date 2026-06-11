#ifndef ROUTE_PLANNER_H
#define ROUTE_PLANNER_H

#include "CityGraph.h"
#include <map>
#include <string>
#include <vector>

struct RouteResult {
  std::vector<std::string> path;
  int totalTime;
  int totalToll;
  bool found;

  RouteResult() : totalTime(0), totalToll(0), found(false) {}
};

class RoutePlanner {
private:
  const CityGraph &cityGraph;

public:
  RoutePlanner(const CityGraph &graph) : cityGraph(graph) {}

  RouteResult calculateFastestRoute(const std::string &start,
                                    const std::string &end);
  RouteResult calculateCheapestRoute(const std::string &start,
                                     const std::string &end);
  RouteResult calculateBalancedRoute(const std::string &start,
                                     const std::string &end);

  // For Multi-stop
  RouteResult calculateMultiStopRoute(const std::vector<std::string> &stops);
};

#endif
