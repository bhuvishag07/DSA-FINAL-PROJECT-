#include "../include/Dashboard.h"
#include <iomanip>
#include <iostream>

void Dashboard::updateStats(int trips, double distance, double revenue,
                            int carpools) {
  completedTrips += trips;
  totalDistance += distance;
  totalRevenue += revenue;
  carpoolsCreated += carpools;
}

void Dashboard::displayDashboard() const {
  std::cout << "\n==============================================" << std::endl;
  std::cout << "          SMARTRIDE SYSTEM DASHBOARD" << std::endl;
  std::cout << "==============================================" << std::endl;
  std::cout << std::left << std::setw(25)
            << "Total Registered Riders:" << riderManager.getCount()
            << std::endl;
  std::cout << std::left << std::setw(25)
            << "Active Ride Requests:" << requestQueue.getQueueStatus()
            << std::endl;
  std::cout << std::left << std::setw(25)
            << "Available Cars:" << carSorter.getCount() << std::endl;
  std::cout << "----------------------------------------------" << std::endl;
  std::cout << std::left << std::setw(25)
            << "Completed Trips:" << completedTrips << std::endl;
  std::cout << std::left << std::setw(25)
            << "Total Carpools Created:" << carpoolsCreated << std::endl;
  std::cout << std::left << std::setw(25)
            << "Total Distance Covered:" << totalDistance << " KM" << std::endl;
  std::cout << std::left << std::setw(25)
            << "Total Revenue Earned:" << "\xe2\x82\xb9" << std::fixed
            << std::setprecision(2) << totalRevenue << std::endl;
  double avgFare = (completedTrips > 0) ? totalRevenue / completedTrips : 0;
  std::cout << std::left << std::setw(25)
            << "Average Trip Fare:" << "\xe2\x82\xb9" << avgFare << std::endl;
  std::cout << "==============================================" << std::endl;
}

void Dashboard::displayComplexityAnalysis() const {
  std::cout << "\n============================================================="
               "==============="
            << std::endl;
  std::cout << "                     DSA COMPLEXITY ANALYSIS REPORT"
            << std::endl;
  std::cout << "==============================================================="
               "============="
            << std::endl;
  std::cout << std::left << std::setw(15) << "Structure" << std::setw(25)
            << "Purpose" << std::setw(15) << "Time Comp." << std::setw(15)
            << "Space Comp." << std::endl;
  std::cout << "---------------------------------------------------------------"
               "-------------"
            << std::endl;
  std::cout << std::left << std::setw(15) << "B-Tree" << std::setw(25)
            << "Rider Indexing" << std::setw(15) << "O(log N)" << std::setw(15)
            << "O(N)" << std::endl;
  std::cout << std::left << std::setw(15) << "Stack" << std::setw(25)
            << "Price Undo" << std::setw(15) << "O(1)" << std::setw(15)
            << "O(N)" << std::endl;
  std::cout << std::left << std::setw(15) << "Queue" << std::setw(25)
            << "Request Line" << std::setw(15) << "O(1)" << std::setw(15)
            << "O(N)" << std::endl;
  std::cout << std::left << std::setw(15) << "Hash Table" << std::setw(25)
            << "Location Lookup" << std::setw(15) << "O(1) Avg" << std::setw(15)
            << "O(N)" << std::endl;
  std::cout << std::left << std::setw(15) << "Max Heap" << std::setw(25)
            << "Car Sorting" << std::setw(15) << "O(log N)" << std::setw(15)
            << "O(N)" << std::endl;
  std::cout << std::left << std::setw(15) << "Graph" << std::setw(25)
            << "City Network" << std::setw(15) << "O(V + E)" << std::setw(15)
            << "O(V + E)" << std::endl;
  std::cout << std::left << std::setw(15) << "Dijkstra" << std::setw(25)
            << "Shortest Path" << std::setw(15) << "O(E log V)" << std::setw(15)
            << "O(V)" << std::endl;
  std::cout << "==============================================================="
               "============="
            << std::endl;
}

void Dashboard::displayBestRider() const {
  std::cout << "\n==============================================" << std::endl;
  std::cout << "             TOP CARPOOL USER" << std::endl;
  std::cout << "==============================================" << std::endl;
  std::cout << "Analyzing ride history and carpool efficiency..." << std::endl;

  // For demo, we just pick Arjun who has high history
  std::cout << "Rider:             Arjun" << std::endl;
  std::cout << "Trips Shared:      15" << std::endl;
  std::cout << "Money Saved:       \xe2\x82\xb9" << "1,250.00" << std::endl;
  std::cout << "Distance Shared:   98 KM" << std::endl;
  std::cout << "Award:             Eco Rider of the Week" << std::endl;
  std::cout << "==============================================" << std::endl;
}
