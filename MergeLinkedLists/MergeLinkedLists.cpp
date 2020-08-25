#include <vector>

using namespace std;

// This is an input class. Do not edit.
class LinkedList {
public:
  int value;
  LinkedList *next;

  LinkedList(int value) {
    this->value = value;
    next = NULL;
  }
};

void updatePointers( LinkedList*& tail, LinkedList*& current ) {
  tail->next = current;
  tail = current;
  current = current->next;
}

LinkedList *mergeLinkedLists(LinkedList *headOne, LinkedList *headTwo) {
  LinkedList* tail;
  LinkedList* currOne;
  LinkedList* currTwo;
  // Determine starting location of the 'tail' ptr
  if( headOne->value < headTwo->value ) {
    tail = headOne;
    currOne = tail->next;
    currTwo = headTwo;
  }
  else {
    tail = headTwo;
    currOne = headOne;
    currTwo = tail->next;
  }
  // Stash the head pointer so we can return it at the end.
  LinkedList* head = tail;
  while( currOne != NULL || currTwo != NULL ) {
    if( currOne == NULL ) {
      updatePointers(tail, currTwo);
    }
    else if( currTwo == NULL ) {
      updatePointers(tail, currOne);
    }
    else if( currOne->value < currTwo->value ) {
      updatePointers(tail, currOne);
    }
    else {
      updatePointers(tail, currTwo);
    }
  }
  return head;
}
