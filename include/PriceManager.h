#ifndef PRICE_MANAGER_H
#define PRICE_MANAGER_H

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// Manages dynamic pricing utilizing a Stack to track rate changes over time.
class PriceManager {
private:
  stack<double> priceHistory; // Stack

  // Implements LIFO so the most recent surge price can
  // be reverted easily when demand drops.

  double currentPrice;

public:
  explicit PriceManager(
      double initialPrice = 100.0); // Initializes default base rate
  void applySurge(double newPrice); // Push new multiplied rate onto stack
  void undoPriceChange(); // Pop last rate, reverting to previous price level
  double getCurrentPrice() const; // Retrieve the active pricing tier
  void viewPriceHistory()
      const; // Output all prior pricing levels active in the session
};

#endif
