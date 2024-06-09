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

void getTreeSumLeft(const Node* node, int64_t &sumTree, int64_t &curLevel, int64_t dirValue){

    ++curLevel;

    sumTree += curLevel*dirValue*(node->value+777);

    if (node->left != nullptr)
        getTreeSumLeft(node->left, sumTree, curLevel, 22);

    if (node->right != nullptr)
        getTreeSumLeft(node->right, sumTree, curLevel, 77);

    --curLevel;    
}

void getTreeSumRight(const Node* node, int64_t &sumTree, int64_t &curLevel, int64_t dirValue){

    ++curLevel;

    sumTree += curLevel*dirValue*(node->value+777);

    if (node->left != nullptr)
        getTreeSumRight(node->left, sumTree, curLevel, 77);

    if (node->right != nullptr)
        getTreeSumRight(node->right, sumTree, curLevel, 22);

    --curLevel;    
}

bool Solution(const Node* root) {

    int64_t sumTree1 = 0;
    int64_t sumTree2 = 0;

    int64_t curLevel = 1; 
    int64_t dirValue = 1;
    if (root->left != nullptr)
        getTreeSumLeft(root->left, sumTree1, curLevel, dirValue);

    curLevel = 1; 
    dirValue = 1;

    if (root->right != nullptr)
        getTreeSumRight(root->right, sumTree2, curLevel, dirValue);

    return sumTree1 == sumTree2;
} 

#ifndef REMOTE_JUDGE
void test() {
    Node node1({3, nullptr, nullptr});
    Node node2({4, nullptr, nullptr});
    Node node3({4, nullptr, nullptr});
    Node node4({3, nullptr, nullptr});
    Node node5({2, &node1, &node2});
    Node node6({2, &node3, &node4});
    Node node7({1, &node5, &node6});
    assert(Solution(&node7));
}


int main() {
  test();
}
#endif