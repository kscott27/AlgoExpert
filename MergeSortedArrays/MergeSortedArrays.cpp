using namespace std;

struct HeapElement {
  HeapElement( int v, int i ) : value(v),
                                idx(i) {}
  int value;
  int idx;
};

class MinHeap {
public:
  MinHeap(vector<HeapElement>& heap);
  void insert(HeapElement element);
  HeapElement pop();
  int size() { return heap_.size(); }
private:
  void siftUp(int currentIdx);
  void siftDown(int currentIdx);
  vector<HeapElement>& heap_;
};

MinHeap::MinHeap( vector<HeapElement>& heap ) : heap_(heap) {
  // Locate first parent node
  int lowestParentIdx = ( heap.size() - 2 ) / 2;
  for( int currentParentIdx = lowestParentIdx; currentParentIdx >= 0; currentParentIdx-- ) {
    siftDown(currentParentIdx);
  }
}

void MinHeap::siftUp( int currentIdx ) {
  int parentIdx = (currentIdx - 1) / 2;
  while( heap_[parentIdx].value > heap_[currentIdx].value ) {
    std::swap(heap_[parentIdx], heap_[currentIdx]);
    currentIdx = parentIdx;
    parentIdx = (currentIdx - 1) / 2;
  }
}

void MinHeap::siftDown( int currentIdx ) {
  int leftChildIdx = (currentIdx * 2) + 1;
  while( leftChildIdx < heap_.size() ) {
    int rightChildIdx = (currentIdx * 2) + 2;
    int lesserChildIdx;
    if( rightChildIdx < heap_.size() && heap_[rightChildIdx].value < heap_[leftChildIdx].value ) {
      lesserChildIdx = rightChildIdx;
    }
    else {
      lesserChildIdx = leftChildIdx;
    }
    // Compare lesser child to current and swap if needed.
    if( heap_[lesserChildIdx].value < heap_[currentIdx].value ) {
      std::swap(heap_[lesserChildIdx], heap_[currentIdx]);
      currentIdx = lesserChildIdx;
      leftChildIdx = (currentIdx * 2) + 1;
    }
    else {
      return;
    }
  }
}

void MinHeap::insert( HeapElement element ) {
  heap_.push_back(element);
  siftUp(heap_.size() - 1);
}

HeapElement MinHeap::pop() {
  std::swap(heap_.front(), heap_.back());
  HeapElement popped = heap_.back();
  heap_.pop_back();
  siftDown(0);
  return popped;
}

vector<int> mergeSortedArrays(vector<vector<int>> arrays) {
  // Keep track of the current idx of each subarray. Every time
  // we pop an element from the heap, we will increment the idx
  // for the subarray that element belonged to, and insert the next
  // element.
  vector<int> idxs(arrays.size(), 0);
  // We end up just passing this by reference to 
  // our MinHeap wrapper, which has all of the heap methods.
  vector<HeapElement> futureHeap;
  for( int a = 0; a < arrays.size(); a++ ) {
    // The heap will begin with the first element 
    // (the lowest) of each subarray.
    HeapElement elem(arrays[a].front(), a);
    futureHeap.push_back(elem);
  }
  MinHeap heap(futureHeap);
  vector<int> result;
  while( heap.size() > 0 ) {
    HeapElement top = heap.pop();
    result.push_back(top.value);
    // Only insert a new element from the array of the value
    // we just popped if we are not at the end of that array.
    if( ++idxs[top.idx] < arrays[top.idx].size() ) {
      int nextVal = arrays[top.idx][idxs[top.idx]];
      HeapElement elem(nextVal, top.idx);
      heap.insert(elem);
    }
  }
  return result;
}
