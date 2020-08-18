#include <vector>
using namespace std;

// Do not edit the class below except
// for the breadthFirstSearch method.
// Feel free to add new properties
// and methods to the class.
class Node {
public:
  string name;
  vector<Node *> children;

  Node(string str) { name = str; }
  
  vector<string> breadthFirstSearch(vector<string> *array) {
    // Start the queue off with the root node.
    std::queue<Node*> q;
    q.push(this);
    while( !q.empty() ) {
      // Push the name of the node on the front of the queue
      // onto the array of names.
      array->push_back(q.front()->name);
      // Iterate through the children of the front node,
      // pushing each onto the queue.
      for( auto child : q.front()->children ) {
        q.push(child);
      }
      // We have handled everything regarding the front node - pop it
      // and move on to the next one.
      q.pop();
    }
    return *array;
  }

  Node *addChild(string name) {
    Node *child = new Node(name);
    children.push_back(child);
    return this;
  }
};
