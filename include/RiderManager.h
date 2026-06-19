#ifndef RIDER_MANAGER_H
#define RIDER_MANAGER_H

#include "Rider.h"
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

// Handles user data mapping using an ordered Map (BST/Red-Black Tree).
class RiderManager {
private:
  map<int, Rider> riders; // Indexed by Rider ID (BST/Red-Black Tree simulation)

  // Map ensures O(log n) time complexity for search, insert, and update.

  const string filename = "data/riders.txt";

public:
  RiderManager();                     // Ensure default setup for the manager
  void addRider(const Rider &r);      // Insert a new user into the tree
  bool searchRider(int id, Rider &r); // Locate specific user by their ID
  bool updateRider(int id, const Rider &r); // Modify user profile details
  bool deleteRider(int id);      // Completely remove user from the system
  void displayAllRiders() const; // Iterate over text file or tree to print info
  void saveToFile();             // Export all accounts to disk
  void loadFromFile();           // Import existing user records
  int getCount() const {
    return riders.size();
  } // Return tracked individuals count
};

#endif
