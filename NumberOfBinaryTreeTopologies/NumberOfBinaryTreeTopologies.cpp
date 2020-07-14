#include <unordered_map>

using namespace std;

namespace helpers {
  
  std::unordered_map<int, int> cache;

}

int numberOfBinaryTreeTopologies(int n) {
  if( n <= 1 ) {
    return 1;
  }
  
  try {
    auto result = helpers::cache.at(n);
    return result;
  }
  catch(...) {
    int total = 0;
    for( int i = 0; i < n; i++ ) {
      total = total + numberOfBinaryTreeTopologies(i)*numberOfBinaryTreeTopologies(n - 1 - i);
    }
    helpers::cache[n] = total;
    return total;
  }
}


int main() {
  return 0;
}