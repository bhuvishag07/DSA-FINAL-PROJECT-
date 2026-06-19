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

using namespace std;

// Helper to clear console and wait for user, creating a clean GUI-like
// experience.
void waitAndClear() {
  cout << "\nPress Enter to continue...";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get();
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// Pre-populates application with existing ecosystem data to ease simulation.
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
  // Initialize foundational architectures and state managers.
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
    // Render dynamic menu interface mapping system tools cleanly.
    cout << "\n==============================================" << endl;
    cout << "      SMARTRIDE CARPOOL SIMULATOR" << endl;
    cout << "==============================================" << endl;
    cout << "1. Rider Management" << endl;
    cout << "2. Price Management" << endl;
    cout << "3. Ride Request Management" << endl;
    cout << "4. Location Lookup" << endl;
    cout << "5. Car Management" << endl;
    cout << "6. City Map Management" << endl;
    cout << "7. Best Pickup Route" << endl;
    cout << "8. Toll Saver Route" << endl;
    cout << "9. Smart Carpool Matching" << endl;
    cout << "10. Traffic & History Controls" << endl;
    cout << "11. System Dashboard" << endl;
    cout << "12. Complexity Analysis" << endl;
    cout << "13. Exit" << endl;
    cout << "Select Option: ";
    cin >> choice;

    // Fail-safe handler preventing continuous loop crash on bad inputs.
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input. Please enter a number." << endl;
      continue;
    }

    switch (choice) {
    case 1: { // Rider Management
      int rChoice;
      cout << "\n1. Add Rider\n2. Search Rider\n3. Display All Riders\n4. "
              "Back\nSelect: ";
      cin >> rChoice;
      if (rChoice == 1) {
        int id;
        string name, home, office, pickup;
        cout << "Enter ID, Name, Home, Office, Pickup: ";
        cin >> id >> name >> home >> office >> pickup;
        riderManager.addRider(Rider(id, name, home, office, pickup, 0));
      } else if (rChoice == 2) {
        int id;
        cout << "Enter ID: ";
        cin >> id;
        Rider r;
        if (riderManager.searchRider(id, r))
          r.display();
        else
          cout << "Not found.";
      } else if (rChoice == 3) {
        riderManager.displayAllRiders();
      }
      break;
    }
    case 2: { // Price Management
      int pChoice;
      cout << "\n1. Apply Surge\n2. Undo Last Change\n3. View current\n4. "
              "View History\nSelect: ";
      cin >> pChoice;
      if (pChoice == 1) {
        double p;
        cout << "New Fare: ";
        cin >> p;
        priceManager.applySurge(p);
      } else if (pChoice == 2)
        priceManager.undoPriceChange();
      else if (pChoice == 3)
        cout << "Current: " << priceManager.getCurrentPrice() << endl;
      else if (pChoice == 4)
        priceManager.viewPriceHistory();
      break;
    }
    case 3: { // Request Queue
      int qChoice;
      cout << "\n1. Add Request\n2. View Queue\n3. Back\nSelect: ";
      cin >> qChoice;
      if (qChoice == 1) {
        int rid, id;
        string s, d;
        cout << "Req ID, Rider ID, Source, Dest: ";
        cin >> rid >> id >> s >> d;
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
      cout << "\n1. Add Car\n2. View All Cars\n3. Back\nSelect: ";
      cin >> cChoice;
      if (cChoice == 1) {
        int id, seats;
        string d, t;
        cout << "ID, Driver, Type, Seats: ";
        cin >> id >> d >> t >> seats;
        carSorter.addCar(Car(id, d, t, seats));
      } else if (cChoice == 2)
        carSorter.viewAllCars();
      break;
    }
    case 6:
      cityGraph.displayMap();
      break;
    case 7: { // Best Pickup Route
      string s, e;
      cout << "Start Node: ";
      cin >> s;
      cout << "End Node: ";
      cin >> e;
      RouteResult r = routePlanner.calculateFastestRoute(s, e);
      if (r.found) {
        cout << "Path: ";
        for (auto p : r.path)
          cout << p << " -> ";
        cout << "END\nTime: " << r.totalTime << " mins, Toll: " << r.totalToll
             << endl;
      } else
        cout << "No route found." << endl;
      break;
    }
    case 8: { // Toll Saver
      string s, e;
      cout << "Start Node: ";
      cin >> s;
      cout << "End Node: ";
      cin >> e;
      RouteResult fastest = routePlanner.calculateFastestRoute(s, e);
      RouteResult cheapest = routePlanner.calculateCheapestRoute(s, e);
      cout << "\n1. Fastest: " << fastest.totalTime
           << " mins, Toll: " << fastest.totalToll << endl;
      cout << "2. Cheapest: " << cheapest.totalTime
           << " mins, Toll: " << cheapest.totalToll << endl;
      break;
    }
    case 9: { // Flagship Demonstration
      cout << "\n--- Initializing Carpool Demonstration ---" << endl;
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
      cout << "\n1. Update Traffic Level\n2. View Trip History\n3. Best "
              "Rider Award\nSelect: ";
      cin >> sub;
      if (sub == 1) {
        int t;
        cout << "1. Low\n2. Medium\n3. Heavy\nSelect: ";
        cin >> t;
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
      return 0; // Terminate normal execution
    default:
      cout << "Invalid choice." << endl;
    }
    waitAndClear();
  }

  return 0;
}
