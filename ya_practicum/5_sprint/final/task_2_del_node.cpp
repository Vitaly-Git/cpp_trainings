/*
Ссылка на отчёт в контесте:
https://contest.yandex.ru/contest/24810/run-report/113511793/

-- ПРИНЦИП РАБОТЫ --
1. Принцип работы основан на подсчете частоты слов в исходных документов.
2. Для быстрого доступа к частотам используем хэш-таблицу (наш поисковый индекс).
3. Можно было бы использовать двоичное дерево, но тогда временная сложность выросла 
   бы до O(log n) вместо O(1), поэтому остановились на хэш таблице.
4. Первым шагом разбираем слова в каждом документе и добавляем в хэш-таблицу (поисковый индекс)
   значение идентификатора документа и частоты слова. Таким образом в хэн-таблице
   под каждым ключом "слово", хранятся все документы с количеством вхождений слов в них.
5. Вторым шагом выполняем разбор запроса на слова, выборку и суммирование частот по ним в
   хэш таблице.
6. Третий финальный шаг - вывод пяти документов в требуемом порядке.
7. К интересным особенностям решения можно отнести: использование предиката, переопределение
   операций для структуры.  
-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
1. Мы использовали полноценный уникальный индекс по словам реализованный на unordered_map,
   обеспечив количественные требования решения задачи.
-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
1. Скорость вставки в хэш-таблицу О(1), но для извления слов мы используем поиск слов в цикле, 
   поэтому временная сложность O(N), где N - количество слов. 
2. Скорость поиска складывается из нескольких компонентов. Скорость поиска равна O(N) только 
   из-за обработки каждого слова. Если мы будем выполнять поиск подготовленных слов, 
   то скорость поиска в хэш-таблице O(1).
   Так же обязательным компонентом является частичная сортировка, сложность которой N*log(M),
   где M = middle - first, N = last - first (https://en.cppreference.com/w/cpp/algorithm/partial_sort).
   В результате максимальная сложность равна O(N)+N*log(M).
-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
1. Пространственная сложность равна O(N), где N - количество уникальных слов в документах, 
   т.к. мы храним частоты для каждого слова.
*/

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

struct NodeWithParent{
  Node* node;
  Node* parent;
  bool isLeftNode;
};

void getNextMinNode(Node* startNode, int& key, NodeWithParent& nwpMinNode);
bool isRootNode(NodeWithParent& nwp);
bool isLeafNode(Node* node);
bool isOneChildNode(Node* node);
Node* removeOneChildNode(Node* root, NodeWithParent& nwpToRemove);
Node* removeLeafNode(Node* root, NodeWithParent& nwpToRemove);
Node* removeTwoChildNode(Node* root, NodeWithParent& nwpToRemove);
void findNodeFromRoot(Node* root, int& key, NodeWithParent& nwpResult);
Node* removeNodeFromTree(Node* root, int& keyToDel);

void getNextMinNode(Node* startNode, int& key, NodeWithParent& nwpMinNode){
  
  nwpMinNode = {startNode->right, startNode, false};

  Node* nextGreaterNode = startNode->right;
  while (nextGreaterNode->left != nullptr){
    nwpMinNode.node = nextGreaterNode->left;
    nwpMinNode.parent = nextGreaterNode;
    nwpMinNode.isLeftNode = true;
    nextGreaterNode = nextGreaterNode->left;
  }
} 

bool isRootNode(NodeWithParent& nwp){
  return (nwp.parent == nullptr);
}

bool isLeafNode(Node* node){
  return (node->left == nullptr && node->right == nullptr);
}

bool isOneChildNode(Node* node){
  return (
          (node->left == nullptr && node->right != nullptr) ||
          (node->left != nullptr && node->right == nullptr)
        );
}

Node* removeOneChildNode(Node* root, NodeWithParent& nwpToRemove){
  
  Node* newRoot = root;
  Node* child = (nwpToRemove.node->left == nullptr ? nwpToRemove.node->right : nwpToRemove.node->left);

  if (isRootNode(nwpToRemove)){
    newRoot = child;
  }else{
    if (nwpToRemove.isLeftNode)
      nwpToRemove.parent->left = child;
    else
      nwpToRemove.parent->right = child;
  }

  return newRoot;
}

Node* removeLeafNode(Node* root, NodeWithParent& nwpToRemove){
  
  Node* newRoot = root;

  if (isRootNode(nwpToRemove)){
    newRoot = nullptr;
  }else{
    if (nwpToRemove.isLeftNode)
      nwpToRemove.parent->left = nullptr;
    else
      nwpToRemove.parent->right = nullptr;
  }

  return newRoot;
}

Node* removeTwoChildNode(Node* root, NodeWithParent& nwpToRemove){

  Node* newRoot = root;
  NodeWithParent nwpMinNode;
  getNextMinNode(nwpToRemove.node, nwpToRemove.node->value, nwpMinNode);

  if (nwpToRemove.parent != nullptr){
    if (nwpToRemove.isLeftNode)
      nwpToRemove.parent->left = nwpMinNode.node;
    else
      nwpToRemove.parent->right = nwpMinNode.node;
  }

  newRoot = removeOneChildNode(root, nwpMinNode);

  nwpMinNode.node->left = nwpToRemove.node->left;
  nwpMinNode.node->right = nwpToRemove.node->right;

  if (root == nwpToRemove.node)
    newRoot = nwpMinNode.node;
  else
    newRoot = root;

  return newRoot;
}

void findNodeFromRoot(Node* root, int& key, NodeWithParent& nwpResult){

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

    if (currentNode!=nullptr && currentNode->value == key)
      break;
  }

  nwpResult.node = currentNode;
  nwpResult.parent = parentNode;
  nwpResult.isLeftNode = isLeftNode;
} 

Node* removeNodeFromTree(Node* root, int& keyToDel){

  Node* newRoot = root;
  NodeWithParent nwpToDel;
  findNodeFromRoot(root, keyToDel, nwpToDel);

  if (nwpToDel.node == nullptr)
    return root;

  if (isLeafNode(nwpToDel.node))
    newRoot = removeLeafNode(root, nwpToDel);
  else if (isOneChildNode(nwpToDel.node)) 
    newRoot = removeOneChildNode(root, nwpToDel);
  else
    newRoot = removeTwoChildNode(root, nwpToDel);

  return newRoot;

};

Node* remove(Node* root, int key) {
    Node* resultNode = removeNodeFromTree(root, key);
    return resultNode;
}

#ifndef REMOTE_JUDGE

#define UNIT_TESTING
#ifdef UNIT_TESTING
  #include <iostream>
  #include <map>
  int test_DelFromBST();
  void createTreeByNodes(int nodesCount, int nodesData[][4], std::map<int, Node*>& mapNodesById);
#endif

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
  
  test();

  #ifndef REMOTE_JUDGE
    #ifdef UNIT_TESTING
      return test_DelFromBST();
    #endif
  #endif  

}

#endif

#ifndef REMOTE_JUDGE

#ifdef UNIT_TESTING

int test_DelFromBST(){

  {
    std::map<int, Node*> mapNodesById ={};
    int nodesData[][4] = {
      {1,4,2,3},
      {2,2,4,5},
      {3,6,6,7},
      {4,1,-1,-1},
      {5,3,-1,-1},
      {6,5,-1,-1},
      {7,7,-1,-1}
    };
    createTreeByNodes(7, nodesData, mapNodesById); 
    Node* newHead = remove(mapNodesById[1], 2);
    assert(newHead->value == 4);
    assert(newHead->right == mapNodesById[3]);
    assert(newHead->right->value == 6);
  }

  {
    std::map<int, Node*> mapNodesById ={};
    int nodesData[][4] = {
      {1,2,-1,-1},
      {2,3,1,-1},
      {3,1,-1,2},
      {4,6,-1,-1},
      {5,8,4,-1},
      {6,10,5,-1},
      {7,5,3,6}
    };
    createTreeByNodes(7, nodesData, mapNodesById); 
    Node* newHead = remove(mapNodesById[7], 10);
    assert(newHead->value == 5);
    assert(newHead->right == mapNodesById[5]);
    assert(newHead->right->value == 8);
  }

  {
    std::map<int, Node*> mapNodesById ={};
    int nodesData[][4] = {
      {1,5,2,5},
      {2,1,-1,3},
      {3,3,4,-1},
      {4,2,-1,-1},
      {5,10,6,-1},
      {6,8,7,-1},
      {7,6,-1,-1}
    };
    createTreeByNodes(7, nodesData, mapNodesById); 
    Node* newHead = remove(mapNodesById[1], 10);
    assert(newHead->value == 5);
    assert(newHead->right == mapNodesById[6]);
    assert(newHead->left->value == 1);    
  }

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
    assert(newHead->right->value == 65);
    assert(newHead->left->value == 20);    
  }

  {
    std::map<int, Node*> mapNodesById ={};
    int nodesData[][4] = {
      {1,5,-1,-1}
    };
    createTreeByNodes(1, nodesData, mapNodesById); 
    Node* newHead = remove(mapNodesById[1], 5);
    assert(newHead == nullptr); 
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

#endif