#ifndef CAR_H
#define CAR_H

#include <string>

class Car {
public:
  int carID;
  std::string driverName;
  std::string vehicleType;
  int availableSeats;

  Car() : carID(0), availableSeats(0) {}
  Car(int id, std::string driver, std::string type, int seats)
      : carID(id), driverName(driver), vehicleType(type),
        availableSeats(seats) {}

  void display() const;

  // For Priority Queue (Max Heap) - Compare by available seats
  bool operator<(const Car &other) const {
    return availableSeats < other.availableSeats;
  }
};

#endif
