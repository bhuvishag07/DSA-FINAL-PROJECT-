#include "../include/RiderManager.h"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

RiderManager::RiderManager() { loadFromFile(); }

// Adds a new rider to the system and stores the data in memory.
void RiderManager::addRider(const Rider &r) {
  riders[r.riderID] = r; // Map insertion
  saveToFile();
}

// Access rider details securely from the Tree via ID log(n).
bool RiderManager::searchRider(int id, Rider &r) {
  if (riders.find(id) != riders.end()) {
    r = riders[id];
    return true;
  }
  return false;
}

// Applies edits down to persistent records if a match exists.
bool RiderManager::updateRider(int id, const Rider &r) {
  if (riders.find(id) != riders.end()) {
    riders[id] = r;
    saveToFile();
    return true;
  }
  return false;
}

// Expunge user records and persist the structure state.
bool RiderManager::deleteRider(int id) {
  if (riders.find(id) != riders.end()) {
    riders.erase(id); // O(log N) deletion operation
    saveToFile();
    return true;
  }
  return false;
}

// In-order traversal across BST nodes effectively sorting users by their IDs
// automatically.
void RiderManager::displayAllRiders() const {
  cout << "\n-------------------------------------------------------------"
          "---------------------------------------\n";
  cout << left << setw(10) << "ID" << setw(15) << "Name" << setw(20) << "Home"
       << setw(20) << "Office" << setw(20) << "Pickup" << setw(10) << "History"
       << endl;
  cout << "---------------------------------------------------------------"
          "-------------------------------------\n";
  for (const auto &pair : riders) {
    pair.second.display();
  }
  cout << "---------------------------------------------------------------"
          "-------------------------------------\n";
}

// Save updated rider information to persistent storage.
void RiderManager::saveToFile() {
#if __cplusplus >= 201703L
  filesystem::create_directories("data");
#endif
  ofstream outFile(filename);
  if (outFile.is_open()) {
    for (const auto &pair : riders) {
      outFile << pair.second.serialize() << "\n";
    }
    outFile.close();
  }
}

// Loads rider records from the data file during startup.
void RiderManager::loadFromFile() {
  ifstream inFile(filename);
  if (inFile.is_open()) {
    string line;
    while (getline(inFile, line)) {
      if (!line.empty()) {
        Rider r = Rider::deserialize(line);
        if (r.riderID != 0) {
          riders[r.riderID] = r;
        }
      }
    }
    inFile.close();
  }
}
