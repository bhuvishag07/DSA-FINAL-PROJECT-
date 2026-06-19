#ifndef CAR_SORTER_H
#define CAR_SORTER_H

#include "Car.h"
#include <queue>
#include <vector>

using namespace std;

// Manages vehicle allocation using a Max Heap.
class CarSorter {
private:
  priority_queue<Car> carHeap; // Max Heap

  // Priority queue is used to always select the vehicle
  // with the highest available seating capacity.

public:
  void addCar(const Car &c);    // Add a new vehicle to the heap
  bool allocateBestCar(Car &c); // Allocate the highest-capacity vehicle
  void viewAllCars() const;     // Display all available vehicles
  void removeCar(
      int carID); // Note: priority_queue doesn't support random access/removal
                  // easily, might need a workaround for "Remove Car"
  int getCount() const { return carHeap.size(); }
  // Returns the total number of vehicles currently available.
};

#endif
