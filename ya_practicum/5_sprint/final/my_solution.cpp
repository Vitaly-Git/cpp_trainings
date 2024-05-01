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

Node* remove(Node* root, int key) {
  struct NodeWithParent{
    Node* node = nullptr;
    Node* parent = nullptr;
    bool isLeftNode = false;
  };

    Node* newRoot = root;
    NodeWithParent nwpToDel;
    //findNodeFromRoot(root, key, nwpToDel);

    Node* currentNode = root;
    Node* parentNode = nullptr;
    bool isLeftNode = false;

    while(currentNode!=nullptr){

      if (currentNode->value == key){
        break;
      }else if (currentNode->value > key){
        parentNode = currentNode;
        currentNode = currentNode->left;
        isLeftNode = true;
      }else{
        parentNode = currentNode;
        currentNode = currentNode->right;
        isLeftNode = false;
      }

    }

    nwpToDel.node = currentNode;
    nwpToDel.parent = parentNode;
    nwpToDel.isLeftNode = isLeftNode;


    if (nwpToDel.node == nullptr)
      return root;

    if (nwpToDel.node->left == nullptr && nwpToDel.node->right == nullptr){

      newRoot = root;

      if (nwpToDel.parent == nullptr){
        newRoot = nullptr;
      }else{
        if (nwpToDel.isLeftNode)
          nwpToDel.parent->left = nullptr;
        else
          nwpToDel.parent->right = nullptr;
      }

    }
    else if ((nwpToDel.node->left == nullptr && nwpToDel.node->right != nullptr) || (nwpToDel.node->left != nullptr && nwpToDel.node->right == nullptr)){
      //newRoot = removeOneChildNode(root, nwpToDel);
      
      newRoot = root;
      Node* child = (nwpToDel.node->left == nullptr ? nwpToDel.node->right : nwpToDel.node->left);

      if ((nwpToDel.parent == nullptr)){
        newRoot = child;
      }else{
        if (nwpToDel.isLeftNode)
          nwpToDel.parent->left = child;
        else
          nwpToDel.parent->right = child;
      }

      }
    else{
      //newRoot = removeTwoChildNode(root, nwpToDel);

      Node* newRoot = root;
      NodeWithParent nwpMinNode;

      nwpMinNode = {nwpToDel.node->right, nwpToDel.node, false};

      Node* nextGreaterNode = nwpToDel.node->right;
      while (nextGreaterNode->left != nullptr){
        nwpMinNode.node = nextGreaterNode->left;
        nwpMinNode.parent = nextGreaterNode;
        nwpMinNode.isLeftNode = true;
        nextGreaterNode = nextGreaterNode->left;
      }

      if (nwpToDel.parent != nullptr){
        if (nwpToDel.isLeftNode)
          nwpToDel.parent->left = nwpMinNode.node;
        else
          nwpToDel.parent->right = nwpMinNode.node;
      }

      if ((nwpMinNode.node->left == nullptr && nwpMinNode.node->right != nullptr) || (nwpMinNode.node->left != nullptr && nwpMinNode.node->right == nullptr)){
        //removeOneChildNode(root, nwpMinNode);

        newRoot = root;
        Node* child = (nwpMinNode.node->left == nullptr ? nwpMinNode.node->right : nwpMinNode.node->left);

        if ((nwpMinNode.parent == nullptr)){
          newRoot = child;
        }else{
          if (nwpMinNode.isLeftNode)
            nwpMinNode.parent->left = child;
          else
            nwpMinNode.parent->right = child;
        }

      }

      nwpMinNode.node->left = nwpToDel.node->left;
      nwpMinNode.node->right = nwpToDel.node->right;

      if (root == nwpToDel.node)
        newRoot = nwpMinNode.node;
      else
        newRoot = root;

    }
      

    return newRoot;
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