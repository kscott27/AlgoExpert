#include <vector>
#include <unordered_map>

using namespace std;

int apartmentHunting(vector<unordered_map<string, bool>> blocks,
                     vector<string> reqs) {
  vector<vector<int>> reqDistancesLeft(blocks.size(), vector<int>(reqs.size(), INT_MAX));
  // Iterate to the right, capturing req building distances from each
  // block in that direction.
  for( int i = 0; i < blocks.size(); i++ ) {
    for( int reqIndex = 0; reqIndex < reqs.size(); reqIndex++ ) {
      if( blocks[i][reqs[reqIndex]] == true ) {
        reqDistancesLeft[i][reqIndex] = 0;
      }
      else {
        if( reqDistancesLeft[i][reqIndex] != INT_MAX || (i > 0 && reqDistancesLeft[i - 1][reqIndex] != INT_MAX) ) {
          // Add one more block from the previous block.
          reqDistancesLeft[i][reqIndex] = reqDistancesLeft[i - 1][reqIndex] + 1;
        }
      }
    }
  }
  
  vector<vector<int>> reqDistancesRight(blocks.size(), vector<int>(reqs.size(), INT_MAX));
  // Iterate to the left, capturing req building distances from each
  // block in that direction.
  for( int i = blocks.size() - 1; i >= 0; i-- ) {
    for( int reqIndex = 0; reqIndex < reqs.size(); reqIndex++ ) {
      if( blocks[i][reqs[reqIndex]] == true ) {
        reqDistancesRight[i][reqIndex] = 0;
      }
      else {
        if( reqDistancesRight[i][reqIndex] != INT_MAX || (i < blocks.size() - 1 && reqDistancesRight[i + 1][reqIndex] != INT_MAX) ) {
          // Add one more block from the previous block.
          reqDistancesRight[i][reqIndex] = reqDistancesRight[i + 1][reqIndex] + 1;
        }
      }
    }
  }
  
  int optimalBlock = -1;
  int optimalScore = INT_MAX;
  // Iterate one more time, taking the minimum distance from our 2 arrays,
  // and tracking the block with the lowest total distance score.
  for( int i = 0; i < blocks.size(); i++ ) {
    int currentScore = 0;
    for( int reqIndex = 0; reqIndex < reqs.size(); reqIndex++ ) {
      currentScore = std::max(currentScore, std::min(reqDistancesLeft[i][reqIndex], reqDistancesRight[i][reqIndex]));
    }
    if( currentScore < optimalScore ) {
      optimalBlock = i;
      optimalScore = currentScore;
    }
  }
  return optimalBlock;
}
