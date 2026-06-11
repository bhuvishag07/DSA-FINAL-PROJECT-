#ifndef CAR_SORTER_H
#define CAR_SORTER_H

#include "Car.h"
#include <queue>
#include <vector>

class CarSorter {
private:
  std::priority_queue<Car> carHeap; // Max Heap

public:
  void addCar(const Car &c);
  bool allocateBestCar(Car &c);
  void viewAllCars() const;
  void removeCar(
      int carID); // Note: priority_queue doesn't support random access/removal
                  // easily, might need a workaround for "Remove Car"
  int getCount() const { return carHeap.size(); }
};

#endif
