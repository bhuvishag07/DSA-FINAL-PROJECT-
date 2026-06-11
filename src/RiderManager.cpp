#include "../include/RiderManager.h"
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>

RiderManager::RiderManager() { loadFromFile(); }

void RiderManager::addRider(const Rider &r) {
  riders[r.riderID] = r;
  saveToFile();
}

bool RiderManager::searchRider(int id, Rider &r) {
  if (riders.find(id) != riders.end()) {
    r = riders[id];
    return true;
  }
  return false;
}

bool RiderManager::updateRider(int id, const Rider &r) {
  if (riders.find(id) != riders.end()) {
    riders[id] = r;
    saveToFile();
    return true;
  }
  return false;
}

bool RiderManager::deleteRider(int id) {
  if (riders.find(id) != riders.end()) {
    riders.erase(id);
    saveToFile();
    return true;
  }
  return false;
}

void RiderManager::displayAllRiders() const {
  std::cout << "\n-------------------------------------------------------------"
               "---------------------------------------\n";
  std::cout << std::left << std::setw(10) << "ID" << std::setw(15) << "Name"
            << std::setw(20) << "Home" << std::setw(20) << "Office"
            << std::setw(20) << "Pickup" << std::setw(10) << "History"
            << std::endl;
  std::cout << "---------------------------------------------------------------"
               "-------------------------------------\n";
  for (const auto &pair : riders) {
    pair.second.display();
  }
  std::cout << "---------------------------------------------------------------"
               "-------------------------------------\n";
}

void RiderManager::saveToFile() {
#if __cplusplus >= 201703L
  std::filesystem::create_directories("data");
#endif
  std::ofstream outFile(filename);
  if (outFile.is_open()) {
    for (const auto &pair : riders) {
      outFile << pair.second.serialize() << "\n";
    }
    outFile.close();
  }
}

void RiderManager::loadFromFile() {
  std::ifstream inFile(filename);
  if (inFile.is_open()) {
    std::string line;
    while (std::getline(inFile, line)) {
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
