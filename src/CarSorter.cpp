#include "../include/CarSorter.h"
#include <iomanip>
#include <iostream>

using namespace std;

// Insert a newly available car into the Max Heap.
void CarSorter::addCar(const Car &c) { carHeap.push(c); }

// Extract the highest-capacity vehicle from the Max Heap.
bool CarSorter::allocateBestCar(Car &c) {
  if (carHeap.empty())
    return false;
  c = carHeap.top(); // Get maximum element
  carHeap.pop();     // Remove it from queue
  return true;
}

// Shows all items currently inside the heap for debugging.
void CarSorter::viewAllCars() const {
  if (carHeap.empty()) {
    cout << "No cars available." << endl;
    return;
  }
  // Copy priority queue to preserve original data during display.
  priority_queue<Car> temp = carHeap;
  cout << "\n--- Available Cars (Max Heap by Seats) ---" << endl;
  cout << left << setw(10) << "ID" << setw(15) << "Driver" << setw(15) << "Type"
       << setw(15) << "Seats" << endl;
  while (!temp.empty()) {
    temp.top().display();
    temp.pop();
  }
}

// Priority Queue doesn't support random access removal,
// so we rebuild it using a temporary vector.
void CarSorter::removeCar(int carID) {
  vector<Car> tempVec;
  bool found = false;
  while (!carHeap.empty()) {
    if (carHeap.top().carID == carID) {
      found = true;
    } else {
      tempVec.push_back(carHeap.top());
    }
    carHeap.pop();
  }

  // Re-insert remaining elements to restore Max Heap structure.
  for (const auto &c : tempVec) {
    carHeap.push(c);
  }

  if (found)
    cout << "Car ID " << carID << " removed." << endl;
  else
    cout << "Car ID " << carID << " not found." << endl;
}
