using namespace std;

// Do not edit the class below except for the insertKeyValuePair,
// getValueFromKey, and getMostRecentKey methods. Feel free
// to add new properties and methods to the class.
class LRUCache {
public:
  int maxSize;

  LRUCache(int maxSize) { this->maxSize = maxSize > 1 ? maxSize : 1; }

  void insertKeyValuePair(string key, int value) {
    // Check if the key is already present.
    auto oldIt = cache_.find(key);
    if( oldIt != cache_.end() ) {
      updateValue(oldIt->second, value);
      pushToHead(oldIt->second);
    }
    else {
      Node* nodeToInsert = new Node(key, value, NULL, NULL);
      cache_.insert({key, nodeToInsert});
      pushToHead(nodeToInsert);
    }

    // Pop the tail if the cache is at max capacity.
    if( cache_.size() > this->maxSize ) {
      auto tail = cache_.find(tailKey_);
      if( tail != cache_.end() )
        removeNode(tail);
    }
  }

  int *getValueFromKey(string key) {
    auto it = cache_.find(key);
    if( it == cache_.end() )
      return NULL;

    pushToHead(it->second);
    
    return &(it->second->value);
  }

  string getMostRecentKey() {
    return headKey_;
  }
  
private:
  struct Node {
    Node( string k, int v, Node* p, Node* n )
      : key(k),
        value(v),
        prev(p),
        next(n)
    {}
    
    string key;
    int value;
    Node* prev;
    Node* next;
  };
  
  void pushToHead(Node* node) {
    // If the node had already existed, remove its
    // links before updating. Does nothing if it
    // was not in the list to begin with.
    removeNodeLinks(node);
    
    // Grab current head node
    auto head = cache_.find(headKey_);
    if( head != cache_.end() ) {
      // Place the new node at the head by setting
      // it as the old head's prev ptr.
      head->second->prev = node;
      node->next = head->second;
      node->prev = NULL;
    }
    
    if( cache_.size() == 1 )
      tailKey_ = node->key;
    
    headKey_ = node->key;
  }
    
  void updateValue(Node* node, int value) {
    node->value = value;
  }
  
  void removeNodeLinks(Node* node) {
    if( node->prev != NULL )
      node->prev->next = node->next;
    if( node->next != NULL )
      node->next->prev = node->prev;
    
    if( tailKey_ == node->key ) {
      // Update the tail key if we are moving the old tail
      // to the head.
      if( node->prev != NULL )
        tailKey_ = node->prev->key;
    }
  }
    
  void removeNode(unordered_map<string, Node*>::iterator& it) {
    removeNodeLinks(it->second);
    cache_.erase(it);
  }
  
  unordered_map<string, Node*> cache_;
  string headKey_;
  string tailKey_;
};
