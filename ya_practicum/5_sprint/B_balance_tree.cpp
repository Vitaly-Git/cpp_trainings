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

void getMaxDepthOfTree(const Node* nood, int &maxDepth, int &minDepth, int &curDepth){

    ++curDepth;

    maxDepth = std::max(curDepth, maxDepth);

    if (nood->left != nullptr)
        getMaxDepthOfTree(nood->left, maxDepth, minDepth, curDepth);

    if (nood->right != nullptr)
        getMaxDepthOfTree(nood->right, maxDepth, minDepth, curDepth);

    if (nood->left == nullptr && nood->right == nullptr)
        minDepth = std::min(minDepth, curDepth);

    --curDepth;
};

void getMaxMinDepth(const Node* root, int &maxDepth, int &minDepth){

    int curDepth = 0;
    getMaxDepthOfTree(root, maxDepth, minDepth, curDepth);

};

bool Solution(const Node* root) {
    int maxDepth = 0;
    int minDepth = std::numeric_limits<int>::max();
    getMaxMinDepth(root, maxDepth, minDepth);
    return maxDepth - minDepth < 2;
} 


#ifndef REMOTE_JUDGE
void test() {
    Node node1({1, nullptr, nullptr});
    Node node2({-5, nullptr, nullptr});
    Node node3({3, &node1, &node2});
    Node node4({10, nullptr, nullptr});
    Node node5({2, &node3, &node4});
    assert(Solution(&node5));
}

int main() {
  test();
}
#endif