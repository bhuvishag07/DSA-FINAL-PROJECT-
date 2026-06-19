#ifndef RIDER_H
#define RIDER_H

#include <string>
#include <vector>

using namespace std;

// Model class representing a user/rider in the system.
class Rider {
public:
  // Core details of a registered rider.
  int riderID;
  string name;
  string homeAddress;
  string officeAddress;
  string preferredPickup;
  int rideHistoryCount;
  double moneySaved;
  double sharedDistance;

  // Initializes default rider profile.
  Rider() : riderID(0), rideHistoryCount(0), moneySaved(0), sharedDistance(0) {}

  // Creates a complete profile for a new rider.
  Rider(int id, string n, string home, string office, string pickup,
        int history)
      : riderID(id), name(n), homeAddress(home), officeAddress(office),
        preferredPickup(pickup), rideHistoryCount(history), moneySaved(0),
        sharedDistance(0) {}

  void display() const;     // Present user profile data to terminal
  string serialize() const; // Convert to text line for file saving
  static Rider
  deserialize(const string &data); // Parse text line back to object
};

#endif
