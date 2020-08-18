#include <vector>
using namespace std;

int minNumberOfCoinsForChange(int n, vector<int> denoms) {
  vector<int> minCoins(n + 1, INT_MAX);
  minCoins[0] = 0;
  for( int amt = 1; amt <= n; amt++ ) {
    int currentMin = minCoins[amt];
    for( auto denom : denoms ) {
      if( denom <= amt ) {
        // If the min coins for the difference between the amt and the denom
        // is still INT_MAX, it means that amt of change cannot be made,
        // so we cannot update currentMin on this iteration.
        if( minCoins[amt - denom] != INT_MAX ) {
          // Take the min coins for the difference between the amt
          // in question and the denom, and then add 1 coin representing
          // the denom.
          currentMin = min(currentMin, minCoins[amt - denom] + 1);
        }
      }
    }
    minCoins[amt] = currentMin;
  }
  return minCoins[n] != INT_MAX ? minCoins[n] : -1;
}
