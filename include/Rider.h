#ifndef RIDER_H
#define RIDER_H

#include <string>
#include <vector>

class Rider {
public:
  int riderID;
  std::string name;
  std::string homeAddress;
  std::string officeAddress;
  std::string preferredPickup;
  int rideHistoryCount;
  double moneySaved;
  double sharedDistance;

  Rider() : riderID(0), rideHistoryCount(0), moneySaved(0), sharedDistance(0) {}
  Rider(int id, std::string n, std::string home, std::string office,
        std::string pickup, int history)
      : riderID(id), name(n), homeAddress(home), officeAddress(office),
        preferredPickup(pickup), rideHistoryCount(history), moneySaved(0),
        sharedDistance(0) {}

  void display() const;
  std::string serialize() const;
  static Rider deserialize(const std::string &data);
};

#endif
