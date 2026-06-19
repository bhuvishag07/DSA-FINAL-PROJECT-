#ifndef CAR_H
#define CAR_H

#include <string>

using namespace std;

// Represents a vehicle in the SmartRide system.
// Used as the element type inside the Max Heap (priority_queue) in CarSorter.
class Car {
public:
  // Stores vehicle details required for ride allocation.
  int carID;
  string driverName;
  string vehicleType;
  int availableSeats;

  // Default constructor — initializes IDs to zero.
  Car() : carID(0), availableSeats(0) {}

  // Parameterized constructor — initializes all vehicle fields.
  Car(int id, string driver, string type, int seats)
      : carID(id), driverName(driver), vehicleType(type),
        availableSeats(seats) {}

  void display() const; // Prints vehicle details to the console.

  // Operator overloading for the Max Heap comparison.
  // The priority_queue uses this to rank cars — more seats = higher priority.
  // For Priority Queue (Max Heap) - Compare by available seats
  bool operator<(const Car &other) const {
    return availableSeats < other.availableSeats;
  }
};

#endif
