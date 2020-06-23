#include <vector>
#include <algorithm>

using namespace std;


int maxProfitWithKTransactions(vector<int> prices, int k) {
  int totalDays = prices.size();
  vector<vector<int>> profits(k + 1, vector<int>(totalDays, 0));
  for( int numTransactions = 1; numTransactions <= k; numTransactions++ ) {
    int maxRollingBal = -prices[0]; // On the first day (day 0), assume the stock was purchased.
    for( size_t day = 1; day < totalDays; day++ ) {
      // cout << "(pre) day: " << day << " numTransactions: " << numTransactions << endl;

      // Simulate buying the stock by taking profit from from the previous day
      // at the previous transaction number threshold and subtracting the price of 
      // the stock on the current day.
      int buyScenario = profits[numTransactions - 1][day - 1] - prices[day];
      // Compare the 2 options of either buying the stock today, or holding off and
      // doing nothing, to see which yields a higher rolling balance.
      maxRollingBal = std::max(maxRollingBal, buyScenario);
      // Take the current rolling balance and add the price of
      // the stock to it to simulate selling the stock on this day.
      int sellScenario = maxRollingBal + prices[day];
      // Hold the stock, meaning the profit from the previous day rolls over to today.
      int waitScenario = profits[numTransactions][day - 1];
      profits[numTransactions][day] = std::max(waitScenario, sellScenario);
      
      // cout << "(post) maxRollingBal: " << maxRollingBal << " profit: " << profits[numTransactions][day] << endl;
    }
  }

  return profits[k][totalDays - 1];
}

int main() {
  return 0;
}
