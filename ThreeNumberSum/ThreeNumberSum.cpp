#include <vector>
using namespace std;

vector<vector<int>> threeNumberSum(vector<int> array, int targetSum) {
  vector<vector<int>> triplets;
  std::sort(array.begin(), array.end());
  for( int i = 0; i < array.size(); i++ ) {
    // The current item in the array is known to be the lowest
    // value we are checking because the array is sorted.
    // Start with an idx pointer directly to the right of the
    // current idx and one at the far right end. Adjust the pointers
    // based on the current sum compared to the target sum.
    int leftIdx = i + 1;
    int rightIdx = array.size() - 1;
    while( leftIdx < rightIdx ) {
      int currentSum = array[i] + array[leftIdx] + array[rightIdx];
      if( currentSum < targetSum ) {
        leftIdx++;
      }
      else if( currentSum > targetSum ) {
        rightIdx--;
      }
      else {
        triplets.push_back({ array[i], array[leftIdx], array[rightIdx] });
        leftIdx++;
        rightIdx--;
      }
    }
  }
  return triplets;
}
