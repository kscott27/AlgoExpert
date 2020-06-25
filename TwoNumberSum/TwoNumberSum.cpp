#include <vector>
#include <unordered_map>

using namespace std;


vector<int> twoNumberSum(vector<int> array, int targetSum) {
  unordered_map<int, int> targets; // key: target, value: int that created that target
  for( auto i : array ) {
    auto it = targets.find(i);
    if( it == targets.end() ) {
      int target = targetSum - i;
      targets.insert({target, i});
    }
    else {
      return {it->first, it->second};
    }
  }
  return {};
}


int main() {
  return 0;
}