#include <vector>
using namespace std;

struct Element {
  Element( int i, int s ) 
    : idx(i),
      sum(s)
  {}
  
  int idx;
  int sum;
};

int maxSubsetSumNoAdjacent(vector<int> array) {
  // Since the maximum sum could quite possibly not be applicable
  // if it is adjacent to the current idx being observed, we must
  // track both the max sum and the runner-up sum.
  Element max(INT_MIN, 0);
  Element runnerUp(INT_MIN, 0);
  for( int i = 0; i < array.size(); i++ ) {
    if( i - 1 != max.idx ) {
      // If the idx of the max is non-adjacent,
      // update the runner-up to be the max, AND THEN
      // update the max.
      runnerUp.sum = max.sum;
      runnerUp.idx = max.idx;
      max.sum += array[i];
      max.idx = i;
    }
    else {
      // If the max is adjacent, update the runner-up and
      // then swap it with the max if it exceeds it.
      runnerUp.sum += array[i];
      runnerUp.idx = i;
      if( max.sum < runnerUp.sum )
        std::swap(max, runnerUp);
    }
  }
  return max.sum;
}
