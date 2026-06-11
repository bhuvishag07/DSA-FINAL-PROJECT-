#include "../include/RoutePlanner.h"
#include <algorithm>
#include <climits>
#include <queue>
#include <unordered_map>

RouteResult RoutePlanner::calculateFastestRoute(const std::string &start,
                                                const std::string &end) {
  auto adj = cityGraph.getAdjacencyList();
  if (adj.find(start) == adj.end() || adj.find(end) == adj.end())
    return RouteResult();

  std::unordered_map<std::string, int> distances;
  std::unordered_map<std::string, std::string> parent;
  for (auto const &[name, roads] : adj)
    distances[name] = INT_MAX;

  auto compare = [](std::pair<std::string, int> left,
                    std::pair<std::string, int> right) {
    return left.second > right.second;
  };
  std::priority_queue<std::pair<std::string, int>,
                      std::vector<std::pair<std::string, int>>,
                      decltype(compare)>
      pq(compare);

  distances[start] = 0;
  pq.push({start, 0});

  while (!pq.empty()) {
    std::string u = pq.top().first;
    int d = pq.top().second;
    pq.pop();

    if (d > distances[u])
      continue;
    if (u == end)
      break;

    for (auto const &road : adj.at(u)) {
      if (distances[u] + road.currentTravelTime < distances[road.destination]) {
        distances[road.destination] = distances[u] + road.currentTravelTime;
        parent[road.destination] = u;
        pq.push({road.destination, distances[road.destination]});
      }
    }
  }

  RouteResult result;
  if (distances[end] == INT_MAX)
    return result;

  result.found = true;
  result.totalTime = distances[end];

  std::string curr = end;
  while (curr != start) {
    result.path.push_back(curr);
    std::string prev = parent[curr];
    for (auto const &road : adj.at(prev)) {
      if (road.destination == curr) {
        result.totalToll += road.tollCost;
        break;
      }
    }
    curr = prev;
  }
  result.path.push_back(start);
  std::reverse(result.path.begin(), result.path.end());
  return result;
}

RouteResult RoutePlanner::calculateCheapestRoute(const std::string &start,
                                                 const std::string &end) {
  auto adj = cityGraph.getAdjacencyList();
  if (adj.find(start) == adj.end() || adj.find(end) == adj.end())
    return RouteResult();

  std::unordered_map<std::string, int> costs;
  std::unordered_map<std::string, std::string> parent;
  for (auto const &[name, roads] : adj)
    costs[name] = INT_MAX;

  auto compare = [](std::pair<std::string, int> left,
                    std::pair<std::string, int> right) {
    return left.second > right.second;
  };
  std::priority_queue<std::pair<std::string, int>,
                      std::vector<std::pair<std::string, int>>,
                      decltype(compare)>
      pq(compare);

  costs[start] = 0;
  pq.push({start, 0});

  while (!pq.empty()) {
    std::string u = pq.top().first;
    int c = pq.top().second;
    pq.pop();

    if (c > costs[u])
      continue;
    if (u == end)
      break;

    for (auto const &road : adj.at(u)) {
      if (costs[u] + road.tollCost < costs[road.destination]) {
        costs[road.destination] = costs[u] + road.tollCost;
        parent[road.destination] = u;
        pq.push({road.destination, costs[road.destination]});
      }
    }
  }

  RouteResult result;
  if (costs[end] == INT_MAX)
    return result;

  result.found = true;
  result.totalToll = costs[end];

  std::string curr = end;
  while (curr != start) {
    result.path.push_back(curr);
    std::string prev = parent[curr];
    for (auto const &road : adj.at(prev)) {
      if (road.destination == curr) {
        result.totalTime += road.currentTravelTime;
        break;
      }
    }
    curr = prev;
  }
  result.path.push_back(start);
  std::reverse(result.path.begin(), result.path.end());
  return result;
}

RouteResult RoutePlanner::calculateBalancedRoute(const std::string &start,
                                                 const std::string &end) {
  auto adj = cityGraph.getAdjacencyList();
  if (adj.find(start) == adj.end() || adj.find(end) == adj.end())
    return RouteResult();

  std::unordered_map<std::string, int> weights;
  std::unordered_map<std::string, std::string> parent;
  for (auto const &[name, roads] : adj)
    weights[name] = INT_MAX;

  auto compare = [](std::pair<std::string, int> left,
                    std::pair<std::string, int> right) {
    return left.second > right.second;
  };
  std::priority_queue<std::pair<std::string, int>,
                      std::vector<std::pair<std::string, int>>,
                      decltype(compare)>
      pq(compare);

  weights[start] = 0;
  pq.push({start, 0});

  while (!pq.empty()) {
    std::string u = pq.top().first;
    int w = pq.top().second;
    pq.pop();

    if (w > weights[u])
      continue;
    if (u == end)
      break;

    for (auto const &road : adj.at(u)) {
      int balancedWeight =
          (road.currentTravelTime * 2) + road.tollCost; // Balanced heuristic
      if (weights[u] + balancedWeight < weights[road.destination]) {
        weights[road.destination] = weights[u] + balancedWeight;
        parent[road.destination] = u;
        pq.push({road.destination, weights[road.destination]});
      }
    }
  }

  RouteResult result;
  if (weights[end] == INT_MAX)
    return result;

  result.found = true;
  std::string curr = end;
  while (curr != start) {
    result.path.push_back(curr);
    std::string prev = parent[curr];
    for (auto const &road : adj.at(prev)) {
      if (road.destination == curr) {
        result.totalTime += road.currentTravelTime;
        result.totalToll += road.tollCost;
        break;
      }
    }
    curr = prev;
  }
  result.path.push_back(start);
  std::reverse(result.path.begin(), result.path.end());
  return result;
}

RouteResult
RoutePlanner::calculateMultiStopRoute(const std::vector<std::string> &stops) {
  RouteResult combinedResult;
  combinedResult.found = true;
  if (stops.size() < 2)
    return combinedResult;

  for (size_t i = 0; i < stops.size() - 1; ++i) {
    RouteResult segment = calculateFastestRoute(stops[i], stops[i + 1]);
    if (!segment.found) {
      combinedResult.found = false;
      return combinedResult;
    }
    if (i > 0) {
      // Avoid duplicate node at joints
      combinedResult.path.insert(combinedResult.path.end(),
                                 segment.path.begin() + 1, segment.path.end());
    } else {
      combinedResult.path.insert(combinedResult.path.end(),
                                 segment.path.begin(), segment.path.end());
    }
    combinedResult.totalTime += segment.totalTime;
    combinedResult.totalToll += segment.totalToll;
  }
  return combinedResult;
}
