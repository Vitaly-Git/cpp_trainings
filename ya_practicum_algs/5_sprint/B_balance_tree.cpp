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


int getMaxDepth2(const Node* node){

    if (node == nullptr)
        return 0;

    int leftDepth = getMaxDepth2(node->left);
    int rightDepth = getMaxDepth2(node->right);

    int maxDepth = max(leftDepth, rightDepth);
    maxDepth = maxDepth + 1;
    
    return maxDepth;
}

bool isBalancedNode(const Node* node){

    if (node == nullptr)
        return true;

    if (!isBalancedNode(node->left))
        return false;

    if (!isBalancedNode(node->right))
        return false;        

    int maxDepthLeft = getMaxDepth2(node->left);
    int maxDepthRight = getMaxDepth2(node->right);

    if (abs(maxDepthLeft-maxDepthRight) > 1)
        return false;

    return true;
}

bool getChildCount(const Node* node, int &countLeftNodes, int &countRightNodes) {
    
    int countLeftNodesWas = countLeftNodes;
    int countRightNodesWas = countRightNodes;

    bool result = true;

    if (node->left != nullptr){
        ++countLeftNodes;
        result = getChildCount(node->left, countLeftNodes, countRightNodes);
    }

    // if (result == false)
    //     return false;

    if (node->right != nullptr){
        ++countRightNodes;
        result = getChildCount(node->right, countLeftNodes, countRightNodes);
    }

    // if (result == false)
    //     return false;

    if (abs(countLeftNodes-countRightNodes) > 1)
        return false;

    countLeftNodes = countLeftNodesWas;
    countRightNodes = countRightNodesWas;

    return true;
} 

bool Solution(const Node* root) {
    

    // if (root->left != nullptr)
    //     getMaxDepthOfTree(root->left)


    // bool result = true;
    // int countLeftNodes = 0;
    // int countRightNodes = 0;
    
    //  if (root->left != nullptr)
     
     
    //  {
    //     ++countLeftNodes;


    //     result = getChildCount(root->left, countLeftNodes, countRightNodes);
    //  }

    // // if (result == false)
    // //     return false;

    // if (root->right != nullptr){
    //     ++countRightNodes;
    //     result = getChildCount(root->right, countLeftNodes, countRightNodes);
    // }

    // // if (result == false)
    // //     return false;

    // if (abs(countLeftNodes-countRightNodes) > 1)
    //     result = false;

    // return result;

    return isBalancedNode(root);
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