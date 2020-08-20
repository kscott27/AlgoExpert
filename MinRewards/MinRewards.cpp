#include <vector>
using namespace std;

int minRewards(vector<int> scores) {
  // Iterate to the right, incrementing the number
  // of consecutive positive slopes as they occur.
  vector<int> right(scores.size(), 1);
  for( int i = 1; i < scores.size(); i++ ) {
    if( scores[i] > scores[i - 1] ) {
      right[i] += right[i - 1];
    }
  }
  
  // Iterate to the left and increment the number
  // of consecutive positive slopes (from the perspective
  // of moving left).
  vector<int> left(scores.size(), 1);
  // left.front() is guaranteed to be <= to right.back(),
  // so we take right.back() here so we don't need to iterate
  // over it.
  int rewardSum = right.back();
  for( int i = scores.size() - 2; i >= 0; i-- ) {
    if( scores[i] > scores[i + 1] ) {
      left[i] += left[i + 1];
    }
    // At the current index, add the max consecutive positive
    // slopes (choosing between both directions).
    rewardSum += max(left[i], right[i]);
  }

  return rewardSum;
}
