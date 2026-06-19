#include "../include/PriceManager.h"
#include <iomanip>

using namespace std;

PriceManager::PriceManager(double initialPrice) : currentPrice(initialPrice) {
  priceHistory.push(initialPrice); // Stack tracks baseline initialization
}

// Push a newly evaluated surge rate on top of the Stack.
void PriceManager::applySurge(double newPrice) {
  priceHistory.push(newPrice);
  currentPrice = newPrice;
  cout << "Surge applied! New Fare: \xe2\x82\xb9" << fixed << setprecision(2)
       << currentPrice << endl;
}

// Revert back to the previous pricing model by popping the Stack.
void PriceManager::undoPriceChange() {
  if (priceHistory.size() > 1) {
    priceHistory.pop();                // Remove the top surge value
    currentPrice = priceHistory.top(); // Retrieve earlier price
    cout << "Undo successful. Reverted to: \xe2\x82\xb9" << fixed
         << setprecision(2) << currentPrice << endl;
  } else {
    cout << "Cannot undo. This is the base fare." << endl;
  }
}

double PriceManager::getCurrentPrice() const { return currentPrice; }

// Visualize Stack by creating a copy to not destruct actual history.
void PriceManager::viewPriceHistory() const {
  stack<double> temp = priceHistory;
  cout << "\n--- Fare Revision History (Latest First) ---" << endl;
  while (!temp.empty()) {
    cout << "\xe2\x82\xb9" << fixed << setprecision(2) << temp.top() << endl;
    temp.pop();
  }
}
