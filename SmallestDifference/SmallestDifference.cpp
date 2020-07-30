#include <vector>

using namespace std;


vector<int> smallestDifference(vector<int> arrayOne, vector<int> arrayTwo) {
  std::sort(arrayOne.begin(), arrayOne.end());
  std::sort(arrayTwo.begin(), arrayTwo.end());

  vector<int> minDiffPair(2);
  int minDiff = INT_MAX;
  int idx1 = 0;
  int idx2 = 0;
  // Compare the current indexes of the respective arrays, and update
  // the smallest difference and smallest difference pair if the
  // current difference is smaller. Then increment the index of the array
  // with the lower value, effectively attempting to close the gap.
  // If you try to increment a lower value and you drop off the edge
  // of an array, you know you have already found the smallest difference
  // pair.
  while( idx1 < arrayOne.size() && idx2 < arrayTwo.size() ) {
    int currentDiff = std::abs(arrayOne[idx1] - arrayTwo[idx2]);
    if( currentDiff < minDiff ) {
      minDiffPair[0] = arrayOne[idx1];
      minDiffPair[1] = arrayTwo[idx2];
      minDiff = currentDiff;
    }
    if( arrayOne[idx1] < arrayTwo[idx2] ) {
      idx1 += 1;
    }
    else {
      idx2 += 1;
    }
  }
  return minDiffPair;
}


int main() {
  return 0;
}
