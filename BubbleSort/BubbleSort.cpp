#include <vector>
using namespace std;

vector<int> bubbleSort(vector<int> array) {
  int maxIndex = array.size() - 1;
  bool swapOccurred = false;
  while( maxIndex > 0 ) {
    for( int i = 0; i < maxIndex; i++ ) {
      if( array[i] > array[i+1] ) {
        std::swap(array[i], array[i+1]);
        swapOccurred = true;
      }
    }
    if(!swapOccurred) {
      // It is sorted!
      break;
    }
    maxIndex--;
  }
  return array;
}

int main() {
  return 0;
}