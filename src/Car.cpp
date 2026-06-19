#include "../include/Car.h"
#include <iomanip>
#include <iostream>

using namespace std;

// Displays the car's current data details to standard output in a clean layout.
void Car::display() const {
  cout << left << setw(10) << carID << setw(15) << driverName << setw(15)
       << vehicleType << setw(15) << availableSeats << endl;
}
