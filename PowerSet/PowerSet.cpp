#include <vector>

using namespace std;


vector<vector<int>> powerset(vector<int> array) {
  vector<vector<int>> result;
  result.push_back({});
  for( auto element : array ) {
    // The result array will grow during the for-loop as we add more to it.
    // We must end the for-loop after we have reached the starting length
    // of this array, otherwise the loop will iterate infinitely.
    int startingLength = result.size();
    for( int i = 0; i < startingLength; i++ ) {
      vector<int> subset = result[i];
      subset.push_back(element);
      result.push_back(subset);
    }
  }
  return result;
}



int main() {
  return 0;
}