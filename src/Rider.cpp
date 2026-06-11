#include "../include/Rider.h"
#include <iomanip>
#include <iostream>
#include <sstream>

void Rider::display() const {
  std::cout << std::left << std::setw(10) << riderID << std::setw(15) << name
            << std::setw(20) << homeAddress << std::setw(20) << officeAddress
            << std::setw(20) << preferredPickup << std::setw(10)
            << rideHistoryCount << std::endl;
}

std::string Rider::serialize() const {
  std::stringstream ss;
  ss << riderID << "|" << name << "|" << homeAddress << "|" << officeAddress
     << "|" << preferredPickup << "|" << rideHistoryCount;
  return ss.str();
}

Rider Rider::deserialize(const std::string &data) {
  std::stringstream ss(data);
  std::string item;
  std::vector<std::string> parts;
  while (std::getline(ss, item, '|')) {
    parts.push_back(item);
  }
  if (parts.size() == 6) {
    return Rider(std::stoi(parts[0]), parts[1], parts[2], parts[3], parts[4],
                 std::stoi(parts[5]));
  }
  return Rider();
}
