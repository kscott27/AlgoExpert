#include <vector>
using namespace std;


int traverseRiver( int j, int i, int riverSize, vector<vector<int>>& matrix, vector<vector<bool>>& visited ) {
  // First check if the current node has been visited - skip if so.
  if( visited[j][i] == false ) {
    // Mark the node as visited.
    visited[j][i] = true;
    if( matrix[j][i] == 1 ) {
      // If the current node is part of a river, increment the riverSize variable.
      riverSize++;
      // Attempt to expand out in all 4 potential directions, recursively calling this method
      // on each new node we branch out to.
      if( i + 1 < matrix[0].size() )
        riverSize = traverseRiver(j, i + 1, riverSize, matrix, visited);
      if( j + 1 < matrix.size() )
        riverSize = traverseRiver(j + 1, i, riverSize, matrix, visited);
      if( i > 0 )
        riverSize = traverseRiver(j, i - 1, riverSize, matrix, visited);
      if( j > 0 )
        riverSize = traverseRiver(j - 1, i, riverSize, matrix, visited);
    }
  }
  return riverSize;
}

vector<int> riverSizes(vector<vector<int>> matrix) {
  // Handle corner case
  if( matrix.size() == 0 || matrix[0].size() == 0 ) {
    return {};
  }

  vector<int> sizes;
  vector<vector<bool>> visited(matrix.size(), vector<bool>(matrix[0].size(), false));

  // Iterate through each node in the matrix, calling traverseRiver() on each.
  for( int j = 0; j < matrix.size(); j++ ) {
    for( int i = 0; i < matrix[0].size(); i++ ) {
      int riverSize = 0;
      riverSize = traverseRiver(j, i, riverSize, matrix, visited);
      if( riverSize > 0 ) {
        // If the initial traverseRiver() call returned a river of any size,
        // add it to the output array of river sizes.
        sizes.push_back(riverSize);
      }
    }
  }

  return sizes;
}


int main() {
  return 0;
}
