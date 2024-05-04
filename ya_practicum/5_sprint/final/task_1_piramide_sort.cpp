#include <iostream>
#include <vector>

struct Player{
    std::string Name = "";
    int taskCount = 0;
    int penalty = 0;

    bool operator == (const Player& rightValue){
        return ((taskCount == rightValue.taskCount) &&
            (penalty == rightValue.penalty) &&
            (Name == rightValue.Name));
    }

    bool operator < (const Player& rightValue){

        if (taskCount < rightValue.taskCount)
            return true;

        if (penalty > rightValue.penalty)
            return true;

        return Name < rightValue.Name;
    }

    bool operator > (const Player& rightValue){
        return !(*this < rightValue) && !(*this == rightValue);
    }
};

typedef std::vector<Player> HeapPlayers;

void heapAdd(HeapPlayers& heap, const Player& key);
void siftUp(HeapPlayers& heap, int index);
Player popMax(HeapPlayers& heap);
void siftDown(HeapPlayers& heap, int index);

int main(){

    int playerCount = 0;
    std::cin >> playerCount;

    HeapPlayers heapPlayers(playerCount);
    Player player;

    std::cin.ignore();
    for (int i=0; i<playerCount; ++i){
        std::cin >> player.Name >> player.taskCount >> player.penalty;
        heapAdd(heapPlayers, player);
    }

    return 0;
}

void siftUp(HeapPlayers& heap, int index) {
    if (index == 1) {
        return;
    }

    int parent_index = index / 2;
    if (heap[parent_index] < heap[index]) {
        std::swap(heap[parent_index], heap[index]);
        siftUp(heap, parent_index);
    }
}

void heapAdd(HeapPlayers& heap, const Player& key) {
    heap.push_back(key);
    int index = heap.size() - 1;
    siftUp(heap, index);
}

Player popMax(HeapPlayers& heap) {
    Player result = heap[1];
    heap[1] = heap[heap.size() - 1];
    heap.pop_back();
    siftDown(heap, 1);
    return result;
}

void siftDown(HeapPlayers& heap, int index) {
    int left = 2 * index;
    int right = 2 * index + 1;

    // Нет дочерних узлов
    if (left >= heap.size()) {
        return;
    }

    // проверяем, что есть оба дочерних узла
    int index_largest = left;
    if (right < heap.size() && heap[right] > heap[left]) {
        index_largest = right; 
    }

    if (heap[index_largest] > heap[index]) {
        std::swap(heap[index], heap[index_largest]);
        siftDown(heap, index_largest);
    }
}