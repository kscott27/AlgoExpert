#include <vector>

using namespace std;


int waterArea(vector<int> heights) {
  vector<int> left(heights.size(), 0);
  vector<int> right(heights.size(), 0);
  // Iterate to the right, constantly tracking the highest
  // pillar to the left at each index.
  int leftMax = 0;
  for( int i = 0; i < left.size(); i++ ) {
    leftMax = std::max(leftMax, heights[i]);
    left[i] = leftMax;
  }
  // Iterate to the left, constantly tracking the highest
  // pillar to the right at each index.
  int rightMax = 0;
  for( int i = right.size() - 1; i >= 0; i-- ) {
    rightMax = std::max(rightMax, heights[i]);
    right[i] = rightMax;
  }
  
  int waterArea = 0;
  for( int i = 0; i < heights.size(); i++ ) {
    waterArea = waterArea + std::min(left[i], right[i]) - heights[i];
  }
  return waterArea;
}


int main() {
  return 0;
}
