#include "../include/CarSorter.h"
#include <iomanip>
#include <iostream>

void CarSorter::addCar(const Car &c) { carHeap.push(c); }

bool CarSorter::allocateBestCar(Car &c) {
  if (carHeap.empty())
    return false;
  c = carHeap.top();
  carHeap.pop();
  return true;
}

void CarSorter::viewAllCars() const {
  if (carHeap.empty()) {
    std::cout << "No cars available." << std::endl;
    return;
  }
  std::priority_queue<Car> temp = carHeap;
  std::cout << "\n--- Available Cars (Max Heap by Seats) ---" << std::endl;
  std::cout << std::left << std::setw(10) << "ID" << std::setw(15) << "Driver"
            << std::setw(15) << "Type" << std::setw(15) << "Seats" << std::endl;
  while (!temp.empty()) {
    temp.top().display();
    temp.pop();
  }
}

void CarSorter::removeCar(int carID) {
  std::vector<Car> tempVec;
  bool found = false;
  while (!carHeap.empty()) {
    if (carHeap.top().carID == carID) {
      found = true;
    } else {
      tempVec.push_back(carHeap.top());
    }
    carHeap.pop();
  }
  for (const auto &c : tempVec) {
    carHeap.push(c);
  }
  if (found)
    std::cout << "Car ID " << carID << " removed." << std::endl;
  else
    std::cout << "Car ID " << carID << " not found." << std::endl;
}
