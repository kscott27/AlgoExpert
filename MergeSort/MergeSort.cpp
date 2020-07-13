#include <vector>

using namespace std;


namespace helpers {
  
  /* It is assumed that the left and right arrays are both sorted.
     Compare the first index of each array, selecting the lower value.
     Increment the index of the array with the lower value, and continue
     until all values have been selected from both arrays.
  **/
  vector<int> sortImpl(vector<int> leftArray, vector<int> rightArray) {
    int leftIndex = 0;
    int rightIndex = 0;
    bool leftDone = false;
    bool rightDone = false;
    vector<int> sortedArray;
    while( leftIndex < leftArray.size() || rightIndex < rightArray.size() ) {
      int r = 0;
      int l = 0;
      if( !rightDone && rightArray.size() > 0 ) {
        r = rightArray[rightIndex];
      }
      else {
        rightDone = true;
      }
      if( !leftDone && leftArray.size() > 0 ) {
        l = leftArray[leftIndex];
      }
      else {
        leftDone = true;
      }
      
      if(leftDone || (r < l && !rightDone)) {
        sortedArray.push_back(r);
        if( ++rightIndex >= rightArray.size() ) {
          rightDone = true;
        }
      }
      else {
        sortedArray.push_back(l);
        if( ++leftIndex >= leftArray.size() ) {
          leftDone = true;
        }
      }
    }
    return sortedArray;
  }
  
}

vector<int> mergeSort(vector<int> array) {
  int size = array.size();
  if( size <= 1 ) {
    return array;
  }
  // This will be rounded down for odd numbers, meaning the left side will be
  // one less than the right side.
  int rightStartingIndex = size / 2;
  // This constructor is non-inclusive of the second index parameter supplied.
  vector<int> leftArray(array.begin(), array.begin() + rightStartingIndex);
  vector<int> rightArray(array.begin() + rightStartingIndex, array.end());
  
  return helpers::sortImpl(mergeSort(leftArray), mergeSort(rightArray));
}


int main() {
  return 0;
}