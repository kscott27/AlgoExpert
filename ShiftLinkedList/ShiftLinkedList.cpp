using namespace std;

class LinkedList {
public:
  int value;
  LinkedList *next;

  LinkedList(int value) {
    this->value = value;
    next = NULL;
  }
};

int adjustK(int k, int nodes) {
  return abs(k) % nodes;
}

LinkedList *shiftLinkedList(LinkedList *head, int k) {
  if( k == 0 ) {
    return head;
  }

  // Determine the number of nodes in the list and the tail
  // node.
  LinkedList* tail = head;
  int nodes = 1;
  while( tail->next != NULL ) {
    tail = tail->next;
    nodes++;
  }
  
  // Adjust the k value to account for multiple "laps"
  // through the list.
  int adjustedK = adjustK(k, nodes);
  if( adjustedK == 0 || adjustedK == nodes )
    return head;

  // Determine forward traversals needed to reach the
  // swap node depending on if k is +\-.
  int forwardTraversals = k > 0 ? nodes - adjustedK : adjustedK;

  // Iterate to the junction point of the list.
  LinkedList* currentNode = head;
  for( int n = 1; n < forwardTraversals; n++ )
    currentNode = currentNode->next;
  
  // Perform swappage.
  tail->next = head;
  head = currentNode->next;
  currentNode->next = NULL;

  return head;
}
