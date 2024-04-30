#ifndef REMOTE_JUDGE
struct Node {  
  int value;  
  Node* left = nullptr;  
  Node* right = nullptr;
  Node(Node* left, Node* right, int value) : value(value), left(left), right(right) {}
};  
#endif
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif
#include <cassert>

struct NodeWithParent{
  Node* node;
  Node* parent;
};

NodeWithParent getNextMinNode(Node* startNode, int key){
  
  Node* resultNode = nullptr;

  if (startNode->left == nullptr && startNode->right == nullptr){
    resultNode = nullptr;
  }else if (startNode->right == nullptr){
    resultNode = startNode->left;
  }else{
    Node* nextGreaterNode = startNode->right;
    while (nextGreaterNode->left != nullptr){
      nextGreaterNode = nextGreaterNode->left;
    }
    resultNode = nextGreaterNode;
  }

  return resultNode;
} 

NodeWithParent findNode(Node* startNode, int key){

  //Node* resultNode = nullptr;
  Node* currentNode = startNode;
  Node* parentNode = nullptr;

  while(currentNode!=nullptr){

    if (currentNode->value == key){
      //resultNode = currentNode;
      break;
    }else if (currentNode->value > key){
      currentNode = currentNode->left;
    }else{
      currentNode = currentNode->right;
    }

  }

  return {currentNode, parentNode};
} 

Node* removeNode(Node* root, NodeWithParent& nwpToRemove){

  Node* resultNode = nullptr;

  Node* minNode = getNextMinNode(nwpToRemove.node, nwpToRemove.node->value);

  return resultNode;
}

Node* removeNodeFromTree(Node* root, int key){

  NodeWithParent nwp = findNode(root, key);
  Node* newRoot = nullptr;

  if (nwp.node == nullptr)
    return root;

  newRoot = removeNode(root, nwp);

  return newRoot;

};

Node* remove(Node* root, int key) {
    Node* resultNode = root;
    resultNode = removeNodeFromTree(root, key);
    return resultNode;
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({nullptr, nullptr, 2});
    Node node2({&node1, nullptr, 3});
    Node node3({nullptr, &node2, 1});
    Node node4({nullptr, nullptr, 6});
    Node node5({&node4, nullptr, 8});
    Node node6({&node5, nullptr, 10});
    Node node7({&node3, &node6, 5});
    Node* newHead = remove(&node7, 10);
    assert(newHead->value == 5);
    assert(newHead->right == &node5);
    assert(newHead->right->value == 8);
}

int main() {
  test();
}
#endif