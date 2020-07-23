#include <vector>

using namespace std;


namespace helpers {
  
  bool splitAndCheck(vector<int> arrayOne, vector<int> arrayTwo);
  void split(vector<int>& original, vector<int>& left, vector<int>& right);
  
}

bool sameBsts(vector<int> arrayOne, vector<int> arrayTwo) {
  return helpers::splitAndCheck(arrayOne, arrayTwo);
}

bool helpers::splitAndCheck(vector<int> arrayOne, vector<int> arrayTwo) {
  // Verify that the arrays are equal length and the root values
  // are equal.
  if( arrayOne.size() != arrayTwo.size() )
    return false;
  
  if( arrayOne.size() == 0 )
    return true;
  
  if( arrayOne[0] != arrayTwo[0] )
    return false;
  
  // If the arrays are reduced to one, the recursion is over.
  // If the remaining values match, it is a success, otherwise,
  // a failure.
  if( arrayOne.size() == 1 ) {
    if( arrayOne[0] == arrayTwo[0] ) {
      return true;
    }
    else {
      return false;
    }
  }
  
  vector<int> left1;
  vector<int> right1;
  split(arrayOne, left1, right1);
  
  vector<int> left2;
  vector<int> right2;
  split(arrayTwo, left2, right2);
  
  // Once both arrays are split, recursively check them - both sides
  // of each tree must return true.
  return splitAndCheck(left1, left2) && splitAndCheck(right1, right2);
}

void helpers::split(vector<int>& original, vector<int>& left, vector<int>& right) {
  int root = original.front();
  for( int i = 1; i < original.size(); i++ ) {
    int currentValue = original[i];
    if( currentValue < root ) {
      left.push_back(currentValue);
    }
    else {
      right.push_back(currentValue);
    }
  }
}


int main() {
  return 0;
}
