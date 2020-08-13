using namespace std;

const string marker = "_";

string underscorifySubstring(string str, string subStr) {
  vector<vector<size_t>> indexes;
  size_t subStrLen = static_cast<size_t>(subStr.length());
  size_t lastPos = 0;
  // Find all instances of the substring, and mark the
  // lead and trail idx in an array.
  do {
    lastPos = str.find(subStr, lastPos);
    if( lastPos != string::npos ) {
      indexes.push_back({lastPos, lastPos + subStrLen});
    }
  } while( lastPos++ != string::npos );
  
  // If there were no instances, then just return the string.
  if( indexes.size() == 0 )
    return str;
  
  // Compress all of the idx pairs of substring instances
  // so that any that overlap only create one big compressed
  // instance.
  vector<vector<size_t>> compressed;
  compressed.push_back(indexes.front());
  for( int i = 1; i < indexes.size(); i++ ) {
    // Grab the trailing idx of the compressed list by ref
    // to check and potentially swap it out during our compression.
    auto& potentialSwap = compressed.back()[1];
    if( indexes[i][0] <= potentialSwap ) {
      potentialSwap = indexes[i][1];
    }
    else {
      compressed.push_back(indexes[i]);
    }
  }
  
  // Underscorify all of the compressed instances,
  // starting from the back in order to not mess up
  // the preceding positions for insertion.
  for( int i = compressed.size() - 1; i >= 0; i-- ) {
    str.insert(compressed[i][1], marker);
    str.insert(compressed[i][0], marker);
  }
  
  return str;
}
