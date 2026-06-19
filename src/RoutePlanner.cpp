#include "../include/RoutePlanner.h"
#include <algorithm>
#include <climits>
#include <queue>
#include <unordered_map>

using namespace std;

// Dijkstra's Algorithm is used to find the shortest route based on total travel
// time.
RouteResult RoutePlanner::calculateFastestRoute(const string &start,
                                                const string &end) {
  auto adj = cityGraph.getAdjacencyList();
  if (adj.find(start) == adj.end() || adj.find(end) == adj.end())
    return RouteResult();

  unordered_map<string, int> distances;
  unordered_map<string, string> parent;
  for (auto const &[name, roads] : adj)
    distances[name] = INT_MAX;

  // Custom comparator for min-heap priority queue behavior.
  auto compare = [](pair<string, int> left, pair<string, int> right) {
    return left.second > right.second;
  };
  priority_queue<pair<string, int>, vector<pair<string, int>>,
                 decltype(compare)>
      pq(compare);

  distances[start] = 0;
  pq.push({start, 0});

  // Extract shortest-time nodes sequentially.
  while (!pq.empty()) {
    string u = pq.top().first;
    int d = pq.top().second;
    pq.pop();

    if (d > distances[u])
      continue;
    if (u == end)
      break;

    // Evaluate connected roads and perform relaxation.
    for (auto const &road : adj.at(u)) {
      // Update distance if a shorter path is found.
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

  // Reconstruct path backward using parent links.
  string curr = end;
  while (curr != start) {
    result.path.push_back(curr);
    string prev = parent[curr];
    for (auto const &road : adj.at(prev)) {
      if (road.destination == curr) {
        result.totalToll += road.tollCost;
        break;
      }
    }
    curr = prev;
  }
  result.path.push_back(start);
  reverse(result.path.begin(), result.path.end());
  return result;
}

// Dijkstra's Algorithm optimizing for minimal financial toll impact.
RouteResult RoutePlanner::calculateCheapestRoute(const string &start,
                                                 const string &end) {
  auto adj = cityGraph.getAdjacencyList();
  if (adj.find(start) == adj.end() || adj.find(end) == adj.end())
    return RouteResult();

  unordered_map<string, int> costs;
  unordered_map<string, string> parent;
  for (auto const &[name, roads] : adj)
    costs[name] = INT_MAX;

  auto compare = [](pair<string, int> left, pair<string, int> right) {
    return left.second > right.second;
  };
  priority_queue<pair<string, int>, vector<pair<string, int>>,
                 decltype(compare)>
      pq(compare);

  costs[start] = 0;
  pq.push({start, 0});

  while (!pq.empty()) {
    string u = pq.top().first;
    int c = pq.top().second;
    pq.pop();

    if (c > costs[u])
      continue;
    if (u == end)
      break;

    // Use tollCost directly for relaxation instead of time.
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

  string curr = end;
  while (curr != start) {
    result.path.push_back(curr);
    string prev = parent[curr];
    for (auto const &road : adj.at(prev)) {
      if (road.destination == curr) {
        result.totalTime += road.currentTravelTime;
        break;
      }
    }
    curr = prev;
  }
  result.path.push_back(start);
  reverse(result.path.begin(), result.path.end());
  return result;
}

// Uses a heuristic combining time and toll calculations.
RouteResult RoutePlanner::calculateBalancedRoute(const string &start,
                                                 const string &end) {
  auto adj = cityGraph.getAdjacencyList();
  if (adj.find(start) == adj.end() || adj.find(end) == adj.end())
    return RouteResult();

  unordered_map<string, int> weights;
  unordered_map<string, string> parent;
  for (auto const &[name, roads] : adj)
    weights[name] = INT_MAX;

  auto compare = [](pair<string, int> left, pair<string, int> right) {
    return left.second > right.second;
  };
  priority_queue<pair<string, int>, vector<pair<string, int>>,
                 decltype(compare)>
      pq(compare);

  weights[start] = 0;
  pq.push({start, 0});

  while (!pq.empty()) {
    string u = pq.top().first;
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
  string curr = end;
  while (curr != start) {
    result.path.push_back(curr);
    string prev = parent[curr];
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
  reverse(result.path.begin(), result.path.end());
  return result;
}

// Splices individual routing jumps sequentially to simulate dropping
// multiple carpool riders at varying destinations.
RouteResult RoutePlanner::calculateMultiStopRoute(const vector<string> &stops) {
  RouteResult combinedResult;
  combinedResult.found = true;
  if (stops.size() < 2)
    return combinedResult;

  // Stitch routes between sequential waypoints.
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
