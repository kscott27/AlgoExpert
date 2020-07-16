#include <vector>

using namespace std;


vector<vector<int>> diskStacking(vector<vector<int>> disks) {
  // Sort the input array so it is least to greatest heights.
  std::sort(disks.begin(), disks.end(), [](vector<int> a, vector<int> b) {
    return a[2] < b[2];
  });
  
  // Create an array to track the max height that can be achieved
  // by each disk in its currently sorted index.
  vector<int> maxHeights(disks.size(), 0);
  for( int i = 0; i < maxHeights.size(); i++ ) {
    maxHeights[i] = disks[i][2];
  }
  
  // Create an array to link each index to the previous index that achieved the max
  // (ultimately the bottom index of the stack that was placed on top of it)
  vector<int> previousIndex(disks.size(), -1);
  
  int ultimateMaxIndex = 0;
  int ultimateMaxHeight = 0;
  for( int currentIndex = 0; currentIndex < disks.size(); currentIndex++ ) {
    int maxHeight = maxHeights[currentIndex];
    for( int i = 0; i < currentIndex; i++ ) {
      if( disks[i][0] < disks[currentIndex][0] && 
          disks[i][1] < disks[currentIndex][1] &&
          disks[i][2] < disks[currentIndex][2] ) {
        int potentialMax = maxHeights[i] + maxHeights[currentIndex];
        if( potentialMax > maxHeight ) {
          // Update max height and previous index of the stack placed on top
          previousIndex[currentIndex] = i;
          maxHeight = potentialMax;
        }
      }
    }
    maxHeights[currentIndex] = maxHeight;
    if( maxHeight > ultimateMaxHeight ) {
      // Update the ultimate max height and index
      // if the current index exceeds the old value.
      ultimateMaxHeight = maxHeight;
      ultimateMaxIndex = currentIndex;
    }
  }
  
  // Create our resulting vector by plugging the ultimate
  // max index into the disks array, which should get us the
  // base of our stack. Then use that index to query the 
  // previousIndex array for the next disk to stack on top.
  vector<vector<int>> result;
  int i = ultimateMaxIndex;
  while( i != -1 ) {
    result.push_back(disks[i]);
    i = previousIndex[i];
  }
  
  // Invert the array to make it go from top to bottom.
  std::sort(result.begin(), result.end(), [](vector<int> a, vector<int> b) {
    return a[2] < b[2];
  });
  
  return result;
}


int main() {
  return 0;
}