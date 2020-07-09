#include <vector>

using namespace std;


vector<int> bubbleSort(vector<int> array) {
  int maxIndex = array.size() - 1;
  bool swapOccurred = false;
  while( maxIndex > 0 ) {
    for( int i = 0; i < maxIndex; i++ ) {
      if( array[i] > array[i+1] ) {
        int currentVal = array[i];
        array[i] = array[i+1];
        array[i+1] = currentVal;
        swapOccurred = true;
      }
    }
    if(!swapOccurred) {
      break;
    }
    maxIndex--;
  }
  return array;
}


int main() {
  return 0;
}