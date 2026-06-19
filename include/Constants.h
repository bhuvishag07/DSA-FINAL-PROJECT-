#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <vector>

using namespace std;

// File paths for persistent storage configuration.
const string RIDERS_FILE = "data/riders.txt";
const string CARS_FILE = "data/cars.txt";

// Defines a connection between nodes for generic graph algorithms.
struct Edge {
  string destination;
  int travelTime;
  int tollCost;
};

#endif
