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

void getMaxDepthOfTree(const Node* nood, int &maxDepth, int &minDepth, int &curDepth, int &totalDiff,
    int &leftChildCount, int &rightChildCount, bool &result){

    if (!result)
        return;

    ++curDepth;

    maxDepth = std::max(curDepth, maxDepth);

    int leftChildCountWas = leftChildCount;
    int rightChildCountWas = rightChildCount;

    if (nood->left != nullptr){
        ++leftChildCount;
        getMaxDepthOfTree(nood->left, maxDepth, minDepth, curDepth, totalDiff, leftChildCount, rightChildCount, result);
        ++totalDiff;
    }

    if (nood->right != nullptr){
        ++rightChildCount;
        getMaxDepthOfTree(nood->right, maxDepth, minDepth, curDepth, totalDiff, leftChildCount, rightChildCount, result);
        --totalDiff;
    }

    if (nood->left == nullptr && nood->right == nullptr)
        minDepth = std::min(minDepth, curDepth);

    // if (abs(totalDiff) > 1)
    //     result = false;
    if (abs(leftChildCount-rightChildCount) > 2)
        result = false;

    leftChildCount = leftChildCountWas;
    rightChildCount = rightChildCountWas;

    --curDepth;
};

bool getMaxMinDepth(const Node* root, int &maxDepth, int &minDepth, int &totalDiff){

    int curDepth = 0;

    int leftChildCount=0;
    int rightChildCount=0;
    bool result = true;


    if (root->left == nullptr)
        totalDiff =1;

    if (root->right == nullptr)
        totalDiff =-1;


    getMaxDepthOfTree(root, maxDepth, minDepth, curDepth, totalDiff, 
        leftChildCount, rightChildCount, result);
    
    return result;
};

bool Solution(const Node* root) {
    
    int maxDepth = 0;
    int minDepth = std::numeric_limits<int>::max();
    int totalDiff = 0;
    // getMaxMinDepth(root, maxDepth, minDepth, totalDiff);
    //return maxDepth - minDepth < 2;

    //bool res = abs(totalDiff) < 2 && maxDepth - minDepth < 2;
    bool res = getMaxMinDepth(root, maxDepth, minDepth, totalDiff);// && abs(totalDiff) < 2;

    return res;
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