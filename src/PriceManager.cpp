#include "../include/PriceManager.h"
#include <iomanip>

PriceManager::PriceManager(double initialPrice) : currentPrice(initialPrice) {
  priceHistory.push(initialPrice);
}

void PriceManager::applySurge(double newPrice) {
  priceHistory.push(newPrice);
  currentPrice = newPrice;
  std::cout << "Surge applied! New Fare: \xe2\x82\xb9" << std::fixed
            << std::setprecision(2) << currentPrice << std::endl;
}

void PriceManager::undoPriceChange() {
  if (priceHistory.size() > 1) {
    priceHistory.pop();
    currentPrice = priceHistory.top();
    std::cout << "Undo successful. Reverted to: \xe2\x82\xb9" << std::fixed
              << std::setprecision(2) << currentPrice << std::endl;
  } else {
    std::cout << "Cannot undo. This is the base fare." << std::endl;
  }
}

double PriceManager::getCurrentPrice() const { return currentPrice; }

void PriceManager::viewPriceHistory() const {
  std::stack<double> temp = priceHistory;
  std::cout << "\n--- Fare Revision History (Latest First) ---" << std::endl;
  while (!temp.empty()) {
    std::cout << "\xe2\x82\xb9" << std::fixed << std::setprecision(2)
              << temp.top() << std::endl;
    temp.pop();
  }
}
