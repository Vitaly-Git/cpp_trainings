/*
Ссылка на отчёт в контесте:
https://contest.yandex.ru/contest/24810/run-report/113511412/

-- ПРИНЦИП РАБОТЫ --
1. Для решения задачи применен типовой механизм работы с кучей.
2. При добавлении элемента просеиваем кучу вверх.
3. При удалении элемента просеиваем кучу вниз.
4. Последовательность шагов:
4.1. Получаем массив входных данных. Изначально на этом этапе вместо вектора использовал кучу,
     но чтобы выделить сортировку именно массива в отдельную функцию, вернулся к вектору.
4.2. Создаем кучу из вектора
4.3. Сортируем наш массив, путем последовательного удаления с вершины кучи максимального элемента,
     и добавления его в результирующую коллекцию.
5. Для включения режима тестирования необходимо определить макрос UNIT_TESTING,
   или раскомментировать соответствующую строчку ниже.      
-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
1. Как сказано в задаче, мы самостоятельно создали кучу с требуемыми операциями.
2. Применены типовые доказанные в лекциях опреации.
3. Тесты пройдены с первого раза.
-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
1. Скорость создания кучи O(1)
2. Скорость вставки в кучу выполняется за O(logN).
3. Скорость удаления из кучи выполняется за O(logN).
4. Обе операции (2 и 3) мы используем для пирамидальной сортировки для N элементов.
5. Таким образом максимальная сложность пирамидальной сортировки: O(NlogN)
-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
1. Куча в памяти представляется как вектор размером N, где N-количество элементов для сортировки. 
2. Другой памяти не используем.
3. Поэтому, пространственная сложность решения равна O(N), где N-количество элементов для сортировки. 
*/

#include <iostream>
#include <vector>
#include <cassert>

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
        else if (taskCount > rightValue.taskCount)    
            return false;

        if (penalty > rightValue.penalty)
            return true;
        else if (penalty < rightValue.penalty)
            return false;

        return Name > rightValue.Name;
    }

    bool operator > (const Player& rightValue){
        return !(*this < rightValue) && !(*this == rightValue);
    }
};

//#define UNIT_TESTING

typedef std::vector<Player> HeapPlayers;
typedef std::vector<Player> VectorPlayers;

int heapSort_Test();
void heapAdd(HeapPlayers& heap, const Player& key);
void siftUp(HeapPlayers& heap, int index);
Player popMax(HeapPlayers& heap);
void siftDown(HeapPlayers& heap, int index);
VectorPlayers heapSort(const VectorPlayers& vectorPlayers);

int main(){

    #ifdef UNIT_TESTING
        return heapSort_Test();
    #endif

    int playerCount = 0;
    std::cin >> playerCount;

    VectorPlayers vectorPlayers(playerCount);

    std::cin.ignore();
    for (int i=0; i<playerCount; ++i)
        std::cin >> vectorPlayers[i].Name >> vectorPlayers[i].taskCount >> vectorPlayers[i].penalty;

    VectorPlayers sortedPlayers = heapSort(vectorPlayers);
    for(int i=0; i<playerCount; ++i)
        std::cout << sortedPlayers[i].Name << '\n';

    return 0;
}

int heapSort_Test(){

    {
        VectorPlayers vectorPlayers = {
            {"alla",4,100},
            {"gena",6,1000},
            {"gosha",2,90},
            {"rita",2,90},
            {"timofey",4,80}
        };
        VectorPlayers resultPlan = {
            {"gena",6,1000},
            {"timofey",4,80},
            {"alla",4,100},
            {"gosha",2,90},
            {"rita",2,90}
        };       
        VectorPlayers result = heapSort(vectorPlayers);
        for(int i=0; i<result.size(); ++i)
            assert(resultPlan[i] == result[i]);
    }

    {
        VectorPlayers vectorPlayers = {
            {"alla",0,0},
            {"gena",0,0},
            {"gosha",0,0},
            {"rita",0,0},
            {"timofey",0,0}
        };
        VectorPlayers resultPlan = {
            {"alla",0,0},
            {"gena",0,0},
            {"gosha",0,0},
            {"rita",0,0},
            {"timofey",0,0}
        };       
        VectorPlayers result = heapSort(vectorPlayers);
        for(int i=0; i<result.size(); ++i)
            assert(resultPlan[i] == result[i]);
    }

    std::cout << "OK " << std::endl;

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

    if (left >= heap.size()) {
        return;
    }

    int index_largest = left;
    if (right < heap.size() && heap[right] > heap[left]) {
        index_largest = right; 
    }

    if (heap[index_largest] > heap[index]) {
        std::swap(heap[index], heap[index_largest]);
        siftDown(heap, index_largest);
    }
}

VectorPlayers heapSort(const VectorPlayers& vectorPlayers) {
    
    HeapPlayers heap = {{}};
    VectorPlayers vectorResult;

    for (const auto& item : vectorPlayers) {
        heapAdd(heap, item);
    }

    std::vector<int> sortedArray;
    while (heap.size() > 1) {
        Player bestPlayer = popMax(heap);
        vectorResult.push_back(bestPlayer);
    }

    return vectorResult;
}