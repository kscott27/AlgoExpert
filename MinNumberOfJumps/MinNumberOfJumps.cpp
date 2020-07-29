#include <vector>

using namespace std;


int minNumberOfJumps(vector<int> array) {
  if( array.size() == 1 )
    return 0;
  
  int steps = array[0];
  int maxReach = array[0];
  int jumps = 0;
  for( int i = 1; i < array.size() - 1; i++ ) {
    maxReach = std::max(maxReach, array[i] + i);
    steps--;
    if( steps == 0 ) {
      jumps++;
      steps = maxReach - i;
    }
  }
  return jumps + 1;
}


int main() {
  return 0;
}
