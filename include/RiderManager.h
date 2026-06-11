#ifndef RIDER_MANAGER_H
#define RIDER_MANAGER_H

#include "Rider.h"
#include <fstream>
#include <iostream>
#include <map>

class RiderManager {
private:
  std::map<int, Rider>
      riders; // Indexed by Rider ID (BST/Red-Black Tree simulation)
  const std::string filename = "data/riders.txt";

public:
  RiderManager();
  void addRider(const Rider &r);
  bool searchRider(int id, Rider &r);
  bool updateRider(int id, const Rider &r);
  bool deleteRider(int id);
  void displayAllRiders() const;
  void saveToFile();
  void loadFromFile();
  int getCount() const { return riders.size(); }
};

#endif
