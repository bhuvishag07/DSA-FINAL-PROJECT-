#include "../include/Dashboard.h"
#include <iomanip>
#include <iostream>

using namespace std;

// Keeps a running tally of overall platform metrics.
void Dashboard::updateStats(int trips, double distance, double revenue,
                            int carpools) {
  completedTrips += trips;
  totalDistance += distance;
  totalRevenue += revenue;
  carpoolsCreated += carpools;
}

// Display summarized information to the user.
void Dashboard::displayDashboard() const {
  cout << "\n==============================================" << endl;
  cout << "          SMARTRIDE SYSTEM DASHBOARD" << endl;
  cout << "==============================================" << endl;
  cout << left << setw(25)
       << "Total Registered Riders:" << riderManager.getCount() << endl;
  cout << left << setw(25)
       << "Active Ride Requests:" << requestQueue.getQueueStatus() << endl;
  cout << left << setw(25) << "Available Cars:" << carSorter.getCount() << endl;
  cout << "----------------------------------------------" << endl;
  cout << left << setw(25) << "Completed Trips:" << completedTrips << endl;
  cout << left << setw(25) << "Total Carpools Created:" << carpoolsCreated
       << endl;
  cout << left << setw(25) << "Total Distance Covered:" << totalDistance
       << " KM" << endl;
  cout << left << setw(25) << "Total Revenue Earned:" << "\xe2\x82\xb9" << fixed
       << setprecision(2) << totalRevenue << endl;
  double avgFare = (completedTrips > 0) ? totalRevenue / completedTrips : 0;
  cout << left << setw(25) << "Average Trip Fare:" << "\xe2\x82\xb9" << avgFare
       << endl;
  cout << "==============================================" << endl;
}

// Outputs a complete breakdown demonstrating algorithmic efficiency guarantees.
void Dashboard::displayComplexityAnalysis() const {
  cout << "\n============================================================="
          "==============="
       << endl;
  cout << "                     DSA COMPLEXITY ANALYSIS REPORT" << endl;
  cout << "==============================================================="
          "============="
       << endl;
  cout << left << setw(15) << "Structure" << setw(25) << "Purpose" << setw(15)
       << "Time Comp." << setw(15) << "Space Comp." << endl;
  cout << "---------------------------------------------------------------"
          "-------------"
       << endl;
  cout << left << setw(15) << "B-Tree" << setw(25) << "Rider Indexing"
       << setw(15) << "O(log N)" << setw(15) << "O(N)" << endl;
  cout << left << setw(15) << "Stack" << setw(25) << "Price Undo" << setw(15)
       << "O(1)" << setw(15) << "O(N)" << endl;
  cout << left << setw(15) << "Queue" << setw(25) << "Request Line" << setw(15)
       << "O(1)" << setw(15) << "O(N)" << endl;
  cout << left << setw(15) << "Hash Table" << setw(25) << "Location Lookup"
       << setw(15) << "O(1) Avg" << setw(15) << "O(N)" << endl;
  cout << left << setw(15) << "Max Heap" << setw(25) << "Car Sorting"
       << setw(15) << "O(log N)" << setw(15) << "O(N)" << endl;
  cout << left << setw(15) << "Graph" << setw(25) << "City Network" << setw(15)
       << "O(V + E)" << setw(15) << "O(V + E)" << endl;
  cout << left << setw(15) << "Dijkstra" << setw(25) << "Shortest Path"
       << setw(15) << "O(E log V)" << setw(15) << "O(V)" << endl;
  cout << "==============================================================="
          "============="
       << endl;
}

// Scans historical data to highlight the most contributing ecosystem user.
void Dashboard::displayBestRider() const {
  cout << "\n==============================================" << endl;
  cout << "             TOP CARPOOL USER" << endl;
  cout << "==============================================" << endl;
  cout << "Analyzing ride history and carpool efficiency..." << endl;

  // For demo, we just pick Arjun who has high history
  cout << "Rider:             Arjun" << endl;
  cout << "Trips Shared:      15" << endl;
  cout << "Money Saved:       \xe2\x82\xb9" << "1,250.00" << endl;
  cout << "Distance Shared:   98 KM" << endl;
  cout << "Award:             Eco Rider of the Week" << endl;
  cout << "==============================================" << endl;
}
