#include "../include/Rider.h"
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

// Streamlines user information into a clean column layout.
void Rider::display() const {
  cout << left << setw(10) << riderID << setw(15) << name << setw(20)
       << homeAddress << setw(20) << officeAddress << setw(20)
       << preferredPickup << setw(10) << rideHistoryCount << endl;
}

// Converts memory data into a string format explicitly for file storage.
string Rider::serialize() const {
  stringstream ss;
  ss << riderID << "|" << name << "|" << homeAddress << "|" << officeAddress
     << "|" << preferredPickup << "|" << rideHistoryCount;
  return ss.str();
}

// Decodes a stored string line back into an active memory Object.
Rider Rider::deserialize(const string &data) {
  stringstream ss(data);
  string item;
  vector<string> parts;
  while (getline(ss, item, '|')) {
    parts.push_back(item);
  }
  if (parts.size() == 6) {
    return Rider(stoi(parts[0]), parts[1], parts[2], parts[3], parts[4],
                 stoi(parts[5]));
  }
  return Rider();
}
