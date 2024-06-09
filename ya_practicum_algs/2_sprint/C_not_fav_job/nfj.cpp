#ifdef REMOTE_JUDGE
#include "solution.h"
#endif

#ifndef REMOTE_JUDGE
#include <cassert>
#include <string>

struct Node {  
    std::string value;  
    Node* next;  
    Node(const std::string &value, Node* next) : value(value), next(next) {
        
    }
};
#endif

int16_t getNodeCount(Node* head){
    
    int16_t nodeCount = 0;
    
    Node* nodeByIndex = head;
    while(nodeByIndex!=nullptr){
        nodeByIndex = nodeByIndex->next;
        ++nodeCount;
    }

    return nodeCount;
}

Node* getNodeByIndex(Node* head, int idx){
    Node* nodeByIndex = head;
    while(idx>0){
        nodeByIndex = nodeByIndex->next;
        --idx;
    }
    return nodeByIndex;
}

Node* solution(Node* head, int idx) {

    Node* prevNode = nullptr;    
    Node* nodeToDel = nullptr;
    Node* newHead = head;

    if (idx==0){
        prevNode = nullptr;
        nodeToDel = head;
        newHead = head->next;
    }else{
        prevNode = getNodeByIndex(head, idx-1);
        nodeToDel = prevNode->next;
        prevNode->next = nodeToDel->next;
        newHead = head;
    }
    
    nodeToDel->next = nullptr;
    // delete nodeToDel;

    return newHead;
}

#ifndef REMOTE_JUDGE
void test() {
    Node node3("node3", nullptr);
    Node node2("node2", &node3);
    Node node1("node1", &node2);
    Node node0("node0", &node1);
    Node* new_head = solution(&node0, 1);
    assert(new_head == &node0);
    assert(new_head->next == &node2);
    assert(new_head->next->next == &node3);
    assert(new_head->next->next->next == nullptr);
    // result is : node0 -> node2 -> node3
}

int main() {
    test();
}
#endif