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

      newRoot = root;
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

// #define UNIT_TESTING

#ifdef UNIT_TESTING
  #include <iostream>
  #include <map>
  int test_DelFromBST();
  void createTreeByNodes(int nodesCount, int nodesData[][4], std::map<int, Node*>& mapNodesById);
#endif

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
  
  //test();

  #ifdef UNIT_TESTING
    return test_DelFromBST();
  #endif

}

#endif

#ifdef UNIT_TESTING

int test_DelFromBST(){

  // {
  //   std::map<int, Node*> mapNodesById ={};
  //   int nodesData[][4] = {
  //     {1,2,-1,-1},
  //     {2,3,1,-1},
  //     {3,1,-1,2},
  //     {4,6,-1,-1},
  //     {5,8,4,-1},
  //     {6,10,5,-1},
  //     {7,5,3,6}
  //   };
  //   createTreeByNodes(7, nodesData, mapNodesById); 
  //   Node* newHead = remove(mapNodesById[7], 10);
  //   assert(newHead->value == 5);
  //   assert(newHead->right == mapNodesById[5]);
  //   assert(newHead->right->value == 8);
  // }

  // {
  //   std::map<int, Node*> mapNodesById ={};
  //   int nodesData[][4] = {
  //     {1,5,2,5},
  //     {2,1,-1,3},
  //     {3,3,4,-1},
  //     {4,2,-1,-1},
  //     {5,10,6,-1},
  //     {6,8,7,-1},
  //     {7,6,-1,-1}
  //   };
  //   createTreeByNodes(7, nodesData, mapNodesById); 
  //   Node* newHead = remove(mapNodesById[1], 10);
  //   assert(newHead->value == 5);
  //   assert(newHead->right == mapNodesById[6]);
  //   assert(newHead->left->value == 1);    
  // }

  {
    std::map<int, Node*> mapNodesById ={};
    int nodesData[][4] = {
      {1,41,2,3},
      {2,20,4,5},
      {3,65,7,8},
      {4,11,-1,-1},
      {5,29,-1,6},
      {6,32,-1,-1},
      {7,50,-1,-1},
      {8,91,9,10},
      {9,72,-1,-1},
      {10,99,-1,-1}
    };
    createTreeByNodes(10, nodesData, mapNodesById); 
    Node* newHead = remove(mapNodesById[1], 41);
    assert(newHead->value == 50);
    // assert(newHead->right == mapNodesById[6]);
    // assert(newHead->left->value == 1);    
  }

  {
    std::map<int, Node*> mapNodesById ={};
    int nodesData[][4] = {
      {1,5,-1,-1}
    };
    createTreeByNodes(1, nodesData, mapNodesById); 
    Node* newHead = remove(mapNodesById[1], 5);
    //assert(newHead->value == 50);
    // assert(newHead->right == mapNodesById[6]);
    // assert(newHead->left->value == 1);    
  }

  std::cout << "OK test_DelFromBST" << "\n";

  return 0;
}

void createTreeByNodes(int nodesCount, int nodesData[][4], std::map<int, Node*>& mapNodesById){

  for (int nodeIdx=0; nodeIdx<nodesCount; ++nodeIdx){

    int currNodeId = nodesData[nodeIdx][0];
    int currNodeValue = nodesData[nodeIdx][1];
    int leftNodeId = nodesData[nodeIdx][2];
    int rightNodeId = nodesData[nodeIdx][3];

    if (mapNodesById[currNodeId] == nullptr)
      mapNodesById[currNodeId] = new Node(nullptr, nullptr, 0);

    if (leftNodeId == -1)
      mapNodesById[leftNodeId] = nullptr;
    else if (mapNodesById[leftNodeId] == nullptr)
      mapNodesById[leftNodeId] = new Node(nullptr, nullptr, 0);

    if (rightNodeId == -1)
      mapNodesById[rightNodeId] = nullptr;
    else if (mapNodesById[rightNodeId] == nullptr)
      mapNodesById[rightNodeId] = new Node(nullptr, nullptr, 0);

    mapNodesById[currNodeId]->left = mapNodesById[leftNodeId];
    mapNodesById[currNodeId]->right = mapNodesById[rightNodeId];
    mapNodesById[currNodeId]->value = currNodeValue;
  }
}

#endif