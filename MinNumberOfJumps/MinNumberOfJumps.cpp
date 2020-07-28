#include <vector>
using namespace std;

int minNumberOfJumps(vector<int> array) {
  vector<int> minJumps(array.size(), 0);
  for( int i = 0; i < array.size(); i++ ) {
    int currentRange = array[i];
    for( int n = 1; n <= currentRange; n++ ) {
      // Don't index out of the array.
      if( i + n >= minJumps.size() )
        break;

      int currentTargetIndex = minJumps[i + n];
      if( currentTargetIndex < 1 ) {
        // If the currentTargetIndex is 0, it means it has
        // not yet been visited by any of the traversals, so
        // we cannot attempt to just take the min because the min
        // is 0.
        minJumps[i + n] = minJumps[i] + 1;
      }
      else {
        // If the current route is the fewest jumps, then update. Otherwise,
        // stick with a previously determined route that proved to be fewer jumps.
        minJumps[i + n] = std::min(currentTargetIndex, minJumps[i] + 1);
      }
    }
  }
  return minJumps.back();
}


int main() {
  return 0;
}