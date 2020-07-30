#include <vector>

using namespace std;


void quickSortImpl(vector<int>& array, int startIdx, int endIdx) {
  if( startIdx >= endIdx )
    return;
  
  int pivotIndex = startIdx;
  int leftIndex = startIdx + 1;
  int rightIndex = endIdx;
  while( leftIndex <= rightIndex ) {
    // Don't want to index out of the array.
    if( leftIndex >= array.size() || rightIndex < 0 )
      break;
    // Both out of place, so swap.
    if( array[leftIndex] > array[pivotIndex] && array[rightIndex] < array[pivotIndex] ) {
      std::swap(array[leftIndex], array[rightIndex]);
    }
    else {
      if( array[leftIndex] <= array[pivotIndex] ) {
        leftIndex++;
      }
      if( array[rightIndex] >= array[pivotIndex] ) {
        rightIndex--;
      }
    }
  }
  // Swap rightIndex value with pivot value.
  std::swap(array[rightIndex], array[pivotIndex]);
  quickSortImpl(array, startIdx, rightIndex - 1); // left
  quickSortImpl(array, rightIndex + 1, endIdx); // right
}

vector<int> quickSort(vector<int> array) {
  quickSortImpl(array, 0, array.size() - 1);
  return array;
}


int main() {
  return 0;
}