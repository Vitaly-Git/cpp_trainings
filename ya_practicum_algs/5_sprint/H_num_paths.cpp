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
#include <vector>

using namespace std;

std::vector<int> resVecNum(0);

int getNumFromResVector(){

  int resNum = 0;
  int resSize = resVecNum.size();

  for (int iNum=0; iNum < resSize; ++iNum){
    resNum = resNum + resVecNum[iNum] * pow(10, resSize-iNum-1);
  }

  return resNum;
}

void SumNodes(const Node* node, int &sumNodes){

  resVecNum.push_back(node->value);

  if (node->left != nullptr)
      SumNodes(node->left, sumNodes);

  if (node->right != nullptr)
      SumNodes(node->right, sumNodes);

  if (node->left == nullptr && node->right == nullptr)
    sumNodes = sumNodes + getNumFromResVector();

  resVecNum.pop_back();

}

int Solution(const Node* root) {

  int sumNodes = 0;
  SumNodes(root, sumNodes);
  return sumNodes;

} 

#ifndef REMOTE_JUDGE
void test() {
    Node node1({2, nullptr, nullptr});
    Node node2({1, nullptr, nullptr});
    Node node3({3, &node1, &node2});
    Node node4({2, nullptr, nullptr});
    Node node5({1, &node4, &node3});
    assert(Solution(&node5) == 275);
}

int main() {
  test();
}
#endif