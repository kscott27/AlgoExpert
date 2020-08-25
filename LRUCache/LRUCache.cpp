using namespace std;

// Do not edit the class below except for the insertKeyValuePair,
// getValueFromKey, and getMostRecentKey methods. Feel free
// to add new properties and methods to the class.
class LRUCache {
public:
  int maxSize;

  LRUCache(int maxSize) { this->maxSize = maxSize > 1 ? maxSize : 1; }

  void insertKeyValuePair(string key, int value) {
    Node* nodeToInsert = new Node(key, value, NULL, NULL);
    // Grab current head node
    auto head = cache_.find(headKey_);
    if( head != cache_.end() ) {
      // Place the new node at the head by setting
      // it as the old head's prev ptr.
      head->second->prev = nodeToInsert;
      nodeToInsert->next = head->second;
    }
    // Check if the key is already present.
    auto oldIt = cache_.find(key);
    if( oldIt != cache_.end() ) {
      // If the key is already present, update the links of
      // its surrounding nodes and then remove it from the map.
      if( oldIt->second->prev != NULL )
        oldIt->second->prev->next = oldIt->second->next;
      if( oldIt->second->next != NULL )
        oldIt->second->next->prev = oldIt->second->prev;

      if( tailKey_ == key ) {
        // Update the tail key if we are moving the old tail
        // to the head.
        if( oldIt->second->prev != NULL )
          tailKey_ = oldIt->second->prev->key;
      }
      cache_.erase(oldIt);
    }
    // Pop the tail if the cache is at max capacity.
    if( cache_.size() >= this->maxSize ) {
      auto tail = cache_.find(tailKey_);
      if( tail != cache_.end() ) {
        if( tail->second->prev != NULL ) {
          tail->second->prev->next = NULL;
          tailKey_ = tail->second->prev->key;
        }
        cache_.erase(tail);
      }
    }
    if( cache_.size() == 0 ) {
      tailKey_ = key;
    }
    // Insert the new key-value
    cache_.insert({key, nodeToInsert});
    // Update the head key
    headKey_ = key;
  }

  int *getValueFromKey(string key) {
    auto it = cache_.find(key);
    if( it == cache_.end() )
      return NULL;
    
    if( tailKey_ == key ) {
      // Update the tail key if we are moving the old tail
      // to the head.
      if( it->second->prev != NULL )
        tailKey_ = it->second->prev->key;
    }
    
    if( it->second->prev != NULL )
      it->second->prev->next = it->second->next;
    if( it->second->next != NULL )
      it->second->next->prev = it->second->prev;
    
    it->second->prev = NULL;
    // Grab current head node
    auto head = cache_.find(headKey_);
    if( head != cache_.end() ) {
      // Place the new node at the head by setting
      // it as the old head's prev ptr.
      head->second->prev = it->second;
      it->second->next = head->second;
    }
    headKey_ = key;
    
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
  unordered_map<string, Node*> cache_;
  string headKey_;
  string tailKey_;
};
