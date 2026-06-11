#include "../include/CarSorter.h"
#include "../include/CarpoolMatcher.h"
#include "../include/CityGraph.h"
#include "../include/Dashboard.h"
#include "../include/LocationLookup.h"
#include "../include/PriceManager.h"
#include "../include/RequestQueue.h"
#include "../include/RiderManager.h"
#include "../include/RoutePlanner.h"
#include "../include/TripHistory.h"
#include <ctime>
#include <iostream>
#include <limits>
#include <string>

// Helper to clear console and wait for user
void waitAndClear() {
  std::cout << "\nPress Enter to continue...";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.get();
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

void preloadData(RiderManager &rm, CarSorter &cs, CityGraph &cg,
                 LocationLookup &ll) {
  // 1. Preload Riders
  rm.addRider(
      Rider(1, "Arjun", "Koramangala", "Whitefield", "Koramangala Metro", 5));
  rm.addRider(
      Rider(2, "Priya", "HSR Layout", "Whitefield", "HSR Junction", 12));
  rm.addRider(
      Rider(3, "Rohan", "Bellandur", "Whitefield", "Bellandur Signal", 8));
  rm.addRider(
      Rider(4, "Neha", "Indiranagar", "Marathahalli", "Indiranagar Metro", 3));
  rm.addRider(Rider(5, "Rahul", "Electronic City", "MG Road", "EC Toll", 15));

  // 2. Preload Cars
  cs.addCar(Car(101, "Amit", "SUV", 4));
  cs.addCar(Car(102, "Vikram", "Sedan", 2));
  cs.addCar(Car(103, "Sneha", "Van", 6));
  cs.addCar(Car(104, "Karan", "Compact", 3));

  // 3. Preload City Map
  cg.addRoad("Koramangala", "HSR Layout", 8, 0);
  cg.addRoad("HSR Layout", "Bellandur", 12, 20);
  cg.addRoad("Bellandur", "Whitefield", 18, 50);
  cg.addRoad("Marathahalli", "Whitefield", 10, 30);
  cg.addRoad("Electronic City", "Silk Board", 15, 10);
  cg.addRoad("Silk Board", "HSR Layout", 5, 0);
  cg.addRoad("Indiranagar", "Marathahalli", 15, 0);
  cg.addRoad("MG Road", "Indiranagar", 10, 0);
  cg.addRoad("Jayanagar", "BTM Layout", 7, 0);
  cg.addRoad("BTM Layout", "Silk Board", 8, 0);
  cg.addRoad("Hebbal", "Indiranagar", 25, 40);

  // 4. Preload Locations for current requests (dummy)
  ll.addLocation(1001, 12.9344, 77.6192); // Koramangala
  ll.addLocation(1002, 12.9105, 77.6450); // HSR
  ll.addLocation(1003, 12.9260, 77.6762); // Bellandur
}

int main() {
  RiderManager riderManager;
  PriceManager priceManager(100.0);
  RequestQueue requestQueue;
  LocationLookup locationLookup;
  CarSorter carSorter;
  CityGraph cityGraph;
  TripHistory tripHistory;
  RoutePlanner routePlanner(cityGraph);
  CarpoolMatcher carpoolMatcher(requestQueue, carSorter, routePlanner,
                                riderManager, locationLookup, tripHistory);
  Dashboard dashboard(riderManager, requestQueue, carSorter);

  srand(time(0));
  preloadData(riderManager, carSorter, cityGraph, locationLookup);

  int choice;
  while (true) {
    std::cout << "\n=============================================="
              << std::endl;
    std::cout << "      SMARTRIDE CARPOOL SIMULATOR" << std::endl;
    std::cout << "==============================================" << std::endl;
    std::cout << "1. Rider Management" << std::endl;
    std::cout << "2. Price Management" << std::endl;
    std::cout << "3. Ride Request Management" << std::endl;
    std::cout << "4. Location Lookup" << std::endl;
    std::cout << "5. Car Management" << std::endl;
    std::cout << "6. City Map Management" << std::endl;
    std::cout << "7. Best Pickup Route" << std::endl;
    std::cout << "8. Toll Saver Route" << std::endl;
    std::cout << "9. Smart Carpool Matching" << std::endl;
    std::cout << "10. Traffic & History Controls" << std::endl;
    std::cout << "11. System Dashboard" << std::endl;
    std::cout << "12. Complexity Analysis" << std::endl;
    std::cout << "13. Exit" << std::endl;
    std::cout << "Select Option: ";
    std::cin >> choice;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input. Please enter a number." << std::endl;
      continue;
    }

    switch (choice) {
    case 1: { // Rider Management
      int rChoice;
      std::cout << "\n1. Add Rider\n2. Search Rider\n3. Display All Riders\n4. "
                   "Back\nSelect: ";
      std::cin >> rChoice;
      if (rChoice == 1) {
        int id;
        std::string name, home, office, pickup;
        std::cout << "Enter ID, Name, Home, Office, Pickup: ";
        std::cin >> id >> name >> home >> office >> pickup;
        riderManager.addRider(Rider(id, name, home, office, pickup, 0));
      } else if (rChoice == 2) {
        int id;
        std::cout << "Enter ID: ";
        std::cin >> id;
        Rider r;
        if (riderManager.searchRider(id, r))
          r.display();
        else
          std::cout << "Not found.";
      } else if (rChoice == 3) {
        riderManager.displayAllRiders();
      }
      break;
    }
    case 2: { // Price Management
      int pChoice;
      std::cout << "\n1. Apply Surge\n2. Undo Last Change\n3. View current\n4. "
                   "View History\nSelect: ";
      std::cin >> pChoice;
      if (pChoice == 1) {
        double p;
        std::cout << "New Fare: ";
        std::cin >> p;
        priceManager.applySurge(p);
      } else if (pChoice == 2)
        priceManager.undoPriceChange();
      else if (pChoice == 3)
        std::cout << "Current: " << priceManager.getCurrentPrice() << std::endl;
      else if (pChoice == 4)
        priceManager.viewPriceHistory();
      break;
    }
    case 3: { // Request Queue
      int qChoice;
      std::cout << "\n1. Add Request\n2. View Queue\n3. Back\nSelect: ";
      std::cin >> qChoice;
      if (qChoice == 1) {
        int rid, id;
        std::string s, d;
        std::cout << "Req ID, Rider ID, Source, Dest: ";
        std::cin >> rid >> id >> s >> d;
        requestQueue.addRequest({rid, id, s, d});
      } else if (qChoice == 2)
        requestQueue.viewPendingRequests();
      break;
    }
    case 4:
      locationLookup.displayAllLocations();
      break;
    case 5: { // Car Management
      int cChoice;
      std::cout << "\n1. Add Car\n2. View All Cars\n3. Back\nSelect: ";
      std::cin >> cChoice;
      if (cChoice == 1) {
        int id, seats;
        std::string d, t;
        std::cout << "ID, Driver, Type, Seats: ";
        std::cin >> id >> d >> t >> seats;
        carSorter.addCar(Car(id, d, t, seats));
      } else if (cChoice == 2)
        carSorter.viewAllCars();
      break;
    }
    case 6:
      cityGraph.displayMap();
      break;
    case 7: { // Best Pickup Route
      std::string s, e;
      std::cout << "Start Node: ";
      std::cin >> s;
      std::cout << "End Node: ";
      std::cin >> e;
      RouteResult r = routePlanner.calculateFastestRoute(s, e);
      if (r.found) {
        std::cout << "Path: ";
        for (auto p : r.path)
          std::cout << p << " -> ";
        std::cout << "END\nTime: " << r.totalTime
                  << " mins, Toll: " << r.totalToll << std::endl;
      } else
        std::cout << "No route found." << std::endl;
      break;
    }
    case 8: { // Toll Saver
      std::string s, e;
      std::cout << "Start Node: ";
      std::cin >> s;
      std::cout << "End Node: ";
      std::cin >> e;
      RouteResult fastest = routePlanner.calculateFastestRoute(s, e);
      RouteResult cheapest = routePlanner.calculateCheapestRoute(s, e);
      std::cout << "\n1. Fastest: " << fastest.totalTime
                << " mins, Toll: " << fastest.totalToll << std::endl;
      std::cout << "2. Cheapest: " << cheapest.totalTime
                << " mins, Toll: " << cheapest.totalToll << std::endl;
      break;
    }
    case 9: { // Flagship Demonstration
      std::cout << "\n--- Initializing Carpool Demonstration ---" << std::endl;
      requestQueue.addRequest({1001, 1, "Koramangala", "Whitefield"});
      requestQueue.addRequest({1002, 2, "HSR Layout", "Whitefield"});
      requestQueue.addRequest({1003, 3, "Bellandur", "Whitefield"});

      carpoolMatcher.calculateCompatibility();
      CarpoolGroup group = carpoolMatcher.matchAndOptimize();
      if (!group.riders.empty()) {
        carpoolMatcher.displayCarpoolSummary(group);
        dashboard.updateStats(1, group.totalDistance, group.totalCost, 1);
      }
      break;
    }
    case 10: { // Extra Features: Traffic & History
      int sub;
      std::cout << "\n1. Update Traffic Level\n2. View Trip History\n3. Best "
                   "Rider Award\nSelect: ";
      std::cin >> sub;
      if (sub == 1) {
        int t;
        std::cout << "1. Low\n2. Medium\n3. Heavy\nSelect: ";
        std::cin >> t;
        cityGraph.updateTraffic((TrafficLevel)t);
      } else if (sub == 2)
        tripHistory.viewAllTrips();
      else if (sub == 3)
        dashboard.displayBestRider();
      break;
    }
    case 11:
      dashboard.displayDashboard();
      break;
    case 12:
      dashboard.displayComplexityAnalysis();
      break;
    case 13:
      return 0;
    default:
      std::cout << "Invalid choice." << std::endl;
    }
    waitAndClear();
  }

  return 0;
}
