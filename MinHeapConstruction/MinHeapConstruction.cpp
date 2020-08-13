#include <vector>
#include <algorithm>

using namespace std;

// Do not edit the class below except for the buildHeap,
// siftDown, siftUp, peek, remove, and insert methods.
// Feel free to add new properties and methods to the class.
class MinHeap {
public:
  vector<int> heap;

  MinHeap(vector<int> vector) { heap = buildHeap(vector); }

  vector<int> buildHeap(vector<int> &vector) {
    // Start with largest parent idx and work back
    // to the top of the heap.
    int firstParentIdx = (vector.size() - 1) / 2;
    for( int currentIdx = firstParentIdx; currentIdx >= 0; currentIdx-- ) {
      siftDown(currentIdx, vector.size() - 1, vector);
    }
    return vector;
  }

  void siftDown(int currentIdx, int endIdx, vector<int> &heap) {
    int leftChildIdx = currentIdx*2 + 1;
    while( leftChildIdx <= endIdx ) {
      int rightChildIdx = currentIdx*2 + 2;
      int nextIdx;
      // The right child must be a valid idx and the value must be less than the left.
      if( rightChildIdx <= endIdx && heap[rightChildIdx] < heap[leftChildIdx] ) {
        nextIdx = rightChildIdx;
      }
      else {
        nextIdx = leftChildIdx;
      }
      // Now that we have the lesser value of the 2 child nodes,
      // see if that is less than the parent, and swap if so.
      // Then update the currentIdx to be the child idx we just swapped.
      if( heap[nextIdx] < heap[currentIdx] ) {
        std::swap(heap[nextIdx], heap[currentIdx]);
        currentIdx = nextIdx;
        leftChildIdx = currentIdx*2 + 1;
      }
      else {
        return;
      }
    }
  }

  void siftUp(int currentIdx, vector<int> &heap) {
    int parentIdx = (currentIdx - 1) / 2;
    while( heap[currentIdx] < heap[parentIdx] ) {
      // If the current item is less than its parent,
      // swap them, update the current idx to be where
      // the parent had been, and try again.
      std::swap(heap[currentIdx], heap[parentIdx]);
      currentIdx = parentIdx;
      parentIdx = (currentIdx - 1) / 2;
    }
  }

  int peek() {
    return heap.front();
  }

  // Removes the top of the heap
  int remove() {
    // Swap the top and bottom of the heap
    std::swap(heap.front(), heap.back());
    int item = heap.back();
    heap.pop_back();
    // Re-organize the heap now that we arbitrarily
    // placed the original back of the heap up to the front.
    siftDown(0, heap.size() - 1, heap);
    return item;
  }

  void insert(int value) {
    // Place the item in the back
    heap.push_back(value);
    // Re-organize the heap now that the item has
    // just been arbitrarily placed in the back.
    siftUp(heap.size() - 1, heap);
  }
};
