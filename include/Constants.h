#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <vector>

const std::string RIDERS_FILE = "data/riders.txt";
const std::string CARS_FILE = "data/cars.txt";

struct Edge {
  std::string destination;
  int travelTime;
  int tollCost;
};

#endif
