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

void getMaxDepthOfTree(const Node* nood, int &maxDepth, int &curDepth){

    ++curDepth;

    maxDepth = std::max(curDepth, maxDepth);

    if (nood->left != nullptr)
        getMaxDepthOfTree(nood->left, maxDepth, curDepth);

    if (nood->right != nullptr)
        getMaxDepthOfTree(nood->right, maxDepth, curDepth);

    --curDepth;
};

void getMaxDepth(const Node* root, int &maxDepth){

    int curDepth = 0;
    getMaxDepthOfTree(root, maxDepth, curDepth);

};

int Solution(const Node* root) {
    
    int maxDepth = 0;
    getMaxDepth(root, maxDepth);
    return maxDepth;
} 

#ifndef REMOTE_JUDGE
void test() {
    Node node1({1, nullptr, nullptr});
    Node node2({4, nullptr, nullptr});
    Node node3({3, &node1, &node2});
    Node node4({8, nullptr, nullptr});
    Node node5({5, &node3, &node4});
    assert(Solution(&node5) == 3);
}


int main() {
  test();
}
#endif