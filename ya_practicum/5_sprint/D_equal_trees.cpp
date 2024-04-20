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

using namespace std;

void getTreeSum(const Node* node, int64_t &sumTree, int64_t &curLevel, int64_t dirValue){

    ++curLevel;

    sumTree += curLevel*dirValue*node->value;

    if (node->left != nullptr)
        getTreeSum(node->left, sumTree, curLevel, 2);

    if (node->right != nullptr)
        getTreeSum(node->right, sumTree, curLevel, 3);

    --curLevel;    
}

bool Solution(const Node* root1, const Node* root2) {

    int64_t sumTree1 = 0;
    int64_t sumTree2 = 0;

    int64_t curLevel = 1; 
    int64_t dirValue = 1;
    getTreeSum(root1, sumTree1, curLevel, dirValue);

    curLevel = 1; 
    dirValue = 1;
    getTreeSum(root2, sumTree2, curLevel, dirValue);

    return sumTree1 == sumTree2;
} 

#ifndef REMOTE_JUDGE
void test() {

    Node node1({1, nullptr, nullptr});
    Node node2({2, nullptr, nullptr});
    Node node3({3, &node1, &node2});

    Node node4({1, nullptr, nullptr});
    Node node5({2, nullptr, nullptr});
    Node node6({3, &node4, &node5});
    assert(Solution(&node3, &node6));
}

int main() {
  test();
}
#endif