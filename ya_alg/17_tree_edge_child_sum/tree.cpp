#include <iostream>

class Node{
    
    public:
        Node(int64_t newValue):value(newValue){
            std::cout << "child created " << value << std::endl;
        };
        int64_t sumValueWithChild();
        int64_t sumValueEdgeChild();
        void setLeftChild(Node* child);
        void setRightChild(Node* child);
        Node* getLeftChild();
        Node* getRightChild();
        int64_t getValue();

        ~Node(){
            std::cout << "child deleted " << value << std::endl;
            delete leftChild;
            delete rightChild;
        };
    private:
        Node* leftChild = nullptr;
        Node* rightChild = nullptr;
        int64_t value = 0;
};

int64_t Node::sumValueWithChild(){
    int64_t sumWithChild = value;
    
    if (leftChild!=nullptr)
        sumWithChild += leftChild->sumValueWithChild();

    if (rightChild!=nullptr)
        sumWithChild += rightChild->sumValueWithChild();

    return sumWithChild;
}

int64_t Node::sumValueEdgeChild(){
    int64_t sum = 0;

    if (leftChild == nullptr && rightChild == nullptr){
        sum = value;
    }else{
        if (leftChild!=nullptr)
            sum += leftChild->sumValueEdgeChild();

        if (rightChild!=nullptr)    
            sum += rightChild->sumValueEdgeChild();
    }
        
    return sum;
}

void Node::setLeftChild(Node* child){
    leftChild = child;
}
void Node::setRightChild(Node* child){
    rightChild = child;
}
Node* Node::getLeftChild(){
    return leftChild;
}
Node* Node::getRightChild(){
    return rightChild;
}

int64_t Node::getValue(){
    return value;
}

class BTree{
    
    public:
        BTree(Node* newRoot):root(newRoot){
            std::cout << "root created " << root->getValue() << std::endl;
        };
        int64_t childSum();
        int64_t sumValueEdgeChild();
        Node* getRoot();
        ~BTree(){
            std::cout << "root deleted " << root->getValue() << std::endl;
            delete root;            
        }

    private:
        Node* root = nullptr;
};

Node* BTree::getRoot(){
    return root;
}

int64_t BTree::childSum(){
    int64_t sum = 0;

    if (root!=nullptr)
        sum = root->sumValueWithChild();

    return sum;    
}

int64_t BTree::sumValueEdgeChild(){
    int64_t sum = 0;

    if (root!=nullptr)
        sum = root->sumValueEdgeChild();

    return sum;  
}

int main(){

    BTree* bTree = new BTree(new Node(0));
    bTree->getRoot()->setLeftChild(new Node(1));
    bTree->getRoot()->setRightChild(new Node(2));

    bTree->getRoot()->getLeftChild()->setLeftChild(new Node(11));
    bTree->getRoot()->getRightChild()->setRightChild(new Node(12));

    bTree->getRoot()->getLeftChild()->getLeftChild()->setLeftChild(new Node(111));
    bTree->getRoot()->getLeftChild()->getLeftChild()->setRightChild(new Node(112));

    bTree->getRoot()->getRightChild()->getRightChild()->setLeftChild(new Node(121));
    bTree->getRoot()->getRightChild()->getRightChild()->setRightChild(new Node(122));

    std::cout << "childSum " << bTree->childSum() << std::endl;
    std::cout << "sumValueEdgeChild " << bTree->sumValueEdgeChild() << std::endl;

    delete bTree;

    return 0;
}