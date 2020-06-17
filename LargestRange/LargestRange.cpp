#include <vector>
#include <map>

using namespace std;

vector<int> largestRange(vector<int> array) {
  std::map<int, bool> visitationMap;

  for( auto&& i : array ) {
    visitationMap.insert({i, false});
  }

  int maxRange = 0;
  int startingIndex = 0;
  for( auto&& it : visitationMap ) {
    // Only proceed if this iterator has not already been visited
    // in a previous scan.
    if( it.second == false ) {
      int upIndex = it.first;
      // Scan up
      for( auto&& index = visitationMap.find(++upIndex); index != visitationMap.end(); index = visitationMap.find(upIndex) ) {
        index->second = true;
        upIndex++;
      }
      upIndex--; // Restore back to previous value before the range was broken.

      int downIndex = it.first;
      // Scan down
      for( auto&& index = visitationMap.find(--downIndex); index != visitationMap.end(); index = visitationMap.find(downIndex) ) {
        index->second = true;
        downIndex--;
      }
      downIndex++; // Restore back to previous value before the range was broken.

      int range = upIndex - downIndex;
      if( range > maxRange ) {
        maxRange = range;
        startingIndex = downIndex;
      }
    }
  }

  return {startingIndex, startingIndex + maxRange};
}

int main() {
  return 0;
}