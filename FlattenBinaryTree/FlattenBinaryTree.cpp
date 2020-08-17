#include <vector>
using namespace std;

// This is the class of the input root. Do not edit it.
class BinaryTree {
public:
  int value;
  BinaryTree *left = NULL;
  BinaryTree *right = NULL;

  BinaryTree(int value);
};

void link(BinaryTree* leftNode, BinaryTree* rightNode) {
  leftNode->right = rightNode;
  rightNode->left = leftNode;
}

vector<BinaryTree*> flattenBinaryTreeImpl(BinaryTree* node) {
  BinaryTree* leftNode;
  BinaryTree* rightNode;
  
  if(node->left == NULL) {
    leftNode = node;
  }
  else {
    // For the left subtree of our current node, we will find both the left-most and
    // right-most node. The right-most node found during this traversal
    // will be the current node's left node.
    vector<BinaryTree*> leftAndRightNodes = flattenBinaryTreeImpl(node->left);
    link(leftAndRightNodes[1], node);
    leftNode = leftAndRightNodes[0];
  }
  
  if(node->right == NULL) {
    rightNode = node;
  }
  else {
    // For the right subtree of our current node, we will find both the left-most and
    // right-most node. The left-most node found during this traversal
    // will be the current node's right node.
    vector<BinaryTree*> leftAndRightNodes = flattenBinaryTreeImpl(node->right);
    link(node, leftAndRightNodes[0]);
    rightNode = leftAndRightNodes[1];
  }
  
  // Continue to pass these up the chain. The leftNode has found its match
  // once it reaches the top of a call chain that started with a right subtree;
  // The rightNode once it reaches a call chain that started with a left subtree.
  return {leftNode, rightNode};
}

BinaryTree *flattenBinaryTree(BinaryTree *root) {
  // Return the left-most node of the root "sub"-tree
  // to be the head pointer of the flattened tree.
  // The right-most node is the tail, and has had its
  // left pointer set during the recursion.
  return flattenBinaryTreeImpl(root)[0];
}
