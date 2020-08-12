#include <vector>

using namespace std;


vector<int> longestIncreasingSubsequence(vector<int> array) {
  vector<int> previousIndexes(array.size(), INT_MIN);
  vector<int> subseqSizes(array.size(), 1);
  int overallMaxIdx = 0;
  for( int currentIdx = 0; currentIdx < array.size(); currentIdx++ ) {
    for( int n = 0; n < currentIdx; n++ ) {
      if( array[currentIdx] > array[n] && subseqSizes[n] >= subseqSizes[currentIdx] ) {
        subseqSizes[currentIdx] = subseqSizes[n] + 1;
        previousIndexes[currentIdx] = n;
      }
    }
    if( subseqSizes[currentIdx] >= subseqSizes[overallMaxIdx] ) {
      overallMaxIdx = currentIdx;
    }
  }
  // Create our subsequence by iterating back through our linked indexes
  // starting at the end.
  vector<int> longestSubseq(subseqSizes[overallMaxIdx]);
  int currentIdx = overallMaxIdx;
  for( int i = longestSubseq.size() - 1; i >= 0; i-- ) {
    longestSubseq[i] = array[currentIdx];
    currentIdx = previousIndexes[currentIdx];
  }
  return longestSubseq;
}
