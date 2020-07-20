using namespace std;

class BST {
public:
  int value;
  BST *left;
  BST *right;

  BST(int value) {
    this->value = value;
    left = NULL;
    right = NULL;
  }

  void insert(int value) {
    if (value < this->value) {
      if (left == NULL) {
        left = new BST(value);
      } else {
        left->insert(value);
      }
    } else {
      if (right == NULL) {
        right = new BST(value);
      } else {
        right->insert(value);
      }
    }
  }
};

BST *minHeightBstImpl(vector<int> array, BST* bst) {
  if( array.size() == 0 )
    return bst;
  
  int middleIndex = (array.size() - 1) / 2;
  
  // Insert the middle item in the array to the BST,
  // then erase that item from the array.
  {
    auto middleIt = array.begin() + middleIndex;
    if( bst == nullptr ) {
      bst = new BST(array[middleIndex]);
    }
    else {
      bst->insert(array[middleIndex]);
    }
    array.erase(middleIt);
  }
  
  // With the middle item now erased from the array,
  // split the array into a left side and a right side
  // and recursively call this function again, passing each
  // side as an argument.
  {
    middleIndex = array.size() / 2;
    auto middleIt = array.begin() + middleIndex;
    vector<int> left(array.begin(), middleIt);
    vector<int> right(middleIt, array.end());
    bst = minHeightBstImpl(left, bst);
    bst = minHeightBstImpl(right, bst);
  }
  return bst;
}

BST *minHeightBst(vector<int> array) {
  return minHeightBstImpl(array, nullptr);
}


int main() {
  return 0;
}