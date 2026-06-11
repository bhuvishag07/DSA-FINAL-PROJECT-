
#ifndef PRICE_MANAGER_H
#define PRICE_MANAGER_H

#include <iostream>
#include <stack>
#include <vector>

class PriceManager {
private:
  std::stack<double> priceHistory;
  double currentPrice;

public:
  PriceManager(double initialPrice = 100.0);
  void applySurge(double newPrice);
  void undoPriceChange();
  double getCurrentPrice() const;
  void viewPriceHistory() const;
};

#endif
