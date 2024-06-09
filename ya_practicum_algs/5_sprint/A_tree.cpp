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
#include <queue>
#include <limits>

using namespace std;

int Solution(const Node* root) {

    int resultMaxValue = std::numeric_limits<int>::min();

    std:queue<const Node*> childsToProccess;
    childsToProccess.push(root);

    while (!childsToProccess.empty())
    {
        const Node* currenNode = childsToProccess.front();
        childsToProccess.pop();

        resultMaxValue = std::max(resultMaxValue, currenNode->value);
        
        if (currenNode->left != nullptr)
            childsToProccess.push(currenNode->left);
        
        if (currenNode->right != nullptr)
            childsToProccess.push(currenNode->right);
    }
    
    return resultMaxValue;
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({1, nullptr, nullptr});
    Node node2({-5, nullptr, nullptr});
    Node node3({3, &node1, &node2});
    Node node4({2, &node3, nullptr});
    assert(Solution(&node4) == 3);
}

int main() {
  test();
}
#endif