#ifndef REMOTE_JUDGE
struct Node {  
  int value;  
  const Node* left = nullptr;  
  const Node* right = nullptr;
  Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}
};  
#endif

#ifdef REMOTE_JUDGE
#include "solution_tree.h"
#endif
#include <cmath>
#include <iostream>
#include <cassert>
#include <limits>

using namespace std;

bool isSearchTree(const Node* node);
bool isSearchTreeCheckLeft(const Node* node, int parentValue, int minLeftValue, int maxRightValue);
bool isSearchTreeCheckRight(const Node* node, int parentValue, int minLeftValue, int maxRightValu);

bool Solution(const Node* root) {    
    return isSearchTree(root);
}

bool isSearchTree(const Node* node) {
    
    int rootValue = node->value;

    if (!isSearchTreeCheckLeft(node->left, rootValue, rootValue, std::numeric_limits<int>::min()))
        return false;

    if (!isSearchTreeCheckRight(node->right, rootValue, std::numeric_limits<int>::max(), rootValue))
        return false; 

    return true;    

}

bool isSearchTreeCheckLeft(const Node* node, int parentValue, int minLeftValue, int maxRightValue) {
    
    if (node == nullptr)
        return true;

    int currentValue = node->value;

    if (!(currentValue < parentValue &&
        currentValue < minLeftValue &&
        currentValue > maxRightValue))
        return false; 

    if (!isSearchTreeCheckLeft(node->left, currentValue, std::min(minLeftValue, parentValue), maxRightValue))
        return false;

    if (!isSearchTreeCheckRight(node->right, currentValue, std::min(minLeftValue, parentValue), maxRightValue))
        return false; 

    return true;           
}

bool isSearchTreeCheckRight(const Node* node, int parentValue, int minLeftValue, int maxRightValue) {
    
    if (node == nullptr)
        return true;

    int currentValue = node->value;

    if (!(currentValue > parentValue &&
        currentValue < minLeftValue &&
        currentValue > maxRightValue))
        return false; 
  
    if (!isSearchTreeCheckLeft(node->left, currentValue, minLeftValue, std::max(maxRightValue, parentValue)))
        return false;

    if (!isSearchTreeCheckRight(node->right, currentValue, minLeftValue, std::max(maxRightValue, parentValue)))
        return false; 

    return true;           
}

#ifndef REMOTE_JUDGE
void test() {
    {
      Node node1({1, nullptr, nullptr});
      Node node2({4, nullptr, nullptr});
      Node node3({3, &node1, &node2});
      Node node4({8, nullptr, nullptr});
      Node node5({5, &node3, &node4});
      assert(Solution(&node5));
    }
    {
      Node node1({1, nullptr, nullptr});
      Node node2({5, nullptr, nullptr});
      Node node3({3, &node1, &node2});
      Node node4({8, nullptr, nullptr});
      Node node5({5, &node3, &node4});
      assert(!Solution(&node5));
    }
}


int main() {
  test();
}
#endif