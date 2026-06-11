#include "../include/Car.h"
#include <iomanip>
#include <iostream>

void Car::display() const {
  std::cout << std::left << std::setw(10) << carID << std::setw(15)
            << driverName << std::setw(15) << vehicleType << std::setw(15)
            << availableSeats << std::endl;
}
