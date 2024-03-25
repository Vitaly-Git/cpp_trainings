/*
Ссылка на отчёт в контесте:
https://contest.yandex.ru/contest/22781/run-report/110480723/

-- ПРИНЦИП РАБОТЫ --
1. Очередь реализована на кольцевом буфере.
2. По условию задачи требуется чтобы все операции выполнялись за О(1),
   поэтому в качестве контейнера кольцевого буфера выбран вектор.
3. Вектор обеспеченивает обращение к элементампо индексу за О(1), а
   т.к. мы задаем размер изначально, то перевыделения памяти не будет.
4. Типы значений размеров и указателей кольцевого буфера выбраны как 
   uint16_t (значения от 0 до 65535), т.к. максимальный размер дека не 
   более 50 000.
5. Тип элементов вектора int16_t (значения от -32767 до 32767), т.к.
   по условию задачи хранимое значение не превосходит 1000.
6. Для возможности переключения между различными низкоуровневыми
   контейнерами дека реализован интерфейсный класс IDequeueLowLevelInt16DataStorage.
   В нашем примере реализация интерфейса возложена на RingBuffer.
7. Класс Dequeue обращается к IDequeueLowLevelInt16DataStorage используя стандартный
   интерфейс, поэтому если в будущем мы придумаем более быстродействущую версию контейнара
   очереди, то сможем просто его подменить через интерфейс избежав больших правок кода.
8. Добавлен тип OperationResult для получения результатов операции со стеком, и
   возможности будущего расширения возвращаемых значений. Это крайне необходимо
   для юнит-тестирования и программной диагностики. Так же рассматривались 
   альтернативные варианты: 
   - дополнительный метод интерфейса IDequeueLowLevelInt16DataStorage 
    GetLastOperationResult - аналог стандатной GetLastError;
   - перенаправление потока вывода результата операции;
   Первый вариант исключен, чтобы не перегружать класс нецелевыми методами.
   Второй вариант исключен, т.к. по заданию операции обязаны выводить результат
   в стандартный поток вывода.
9. Для включения режима тестирования необходимо определить макрос UNIT_TESTING,
   или раскомментировать соответствующую строчку ниже. 

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
1. Для обеспечения сложности О(1) выбран контейнер вектор, с фиксированным размером,
   поэтому сложность обращения к элементам всегда будет равна О(1).
       
-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
1. Для обеспечения сложности О(1) выбран контейнер вектор, с фиксированным размером,
   поэтому сложность обращения к элементам всегда будет равна О(1). 
2. Амортизированная сложность также равна О(1), т.к. для каждого элемента сложность О(1).

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
1. Память расходуется на создание кольцевого буфера O(m), где m - количество элементов
   в буфере. В лучшем случае будет О(1) при единичном размере буфера, в худшем O(N), где N - количество элементов,
   и кольцевой буфер равен количеству элементов.
*/

#include <iostream>
#include <vector>
#include <cassert>

//#define UNIT_TESTING

typedef std::string OperationResult;

int deqTest();

class IDequeueLowLevelInt16DataStorage{
    public:
        virtual OperationResult push_back(int16_t value) = 0;
        virtual OperationResult push_front(int16_t value) = 0;
        virtual OperationResult pop_back() = 0;
        virtual OperationResult pop_front() = 0;
};

class RingBuffer : public IDequeueLowLevelInt16DataStorage{
    private:
        std::vector<int16_t> buffer;
        uint16_t maxSize;
        uint16_t size;
        uint16_t head;
        uint16_t tail;
        RingBuffer() = delete;
        RingBuffer(const RingBuffer&) = delete;
        void operator = (const RingBuffer&) = delete;
    public:
        RingBuffer(uint16_t buffSize):maxSize(buffSize), size(0), head(0), tail(0){
            buffer.resize(maxSize);
        };
        bool isEmpty(){
            return size==0;
        }
        bool isFull(){
            return size==maxSize;
        }
        OperationResult push_back(int16_t value){
            OperationResult operationResult = "";
            
            if (isFull()){
                operationResult = "error";
            }else{
                operationResult = "";
                buffer[tail] = value;
                tail = (tail+1) % maxSize;
                ++size;
            }
            
            if (operationResult!="")
                std::cout << operationResult << "\n";

            return operationResult;
        };
        OperationResult push_front(int16_t value){
            OperationResult operationResult = "";

            if (isFull()){
                operationResult = "error";
            }else{
                operationResult = "";
                head = (head==0?maxSize-1:head-1) % maxSize;
                buffer[head] = value;
                ++size;
            }

            if (operationResult!="")
                std::cout << operationResult << "\n";
                
            return operationResult;
        };
        OperationResult pop_back(){
            OperationResult operationResult = "";

            if (isEmpty()){
                operationResult = "error";
            }else{
                tail = (tail==0?maxSize-1:tail-1) % maxSize;
                operationResult = std::to_string(buffer[tail]);
                buffer[tail] = 0;
                --size;
            }

            if (operationResult!="")
                std::cout << operationResult << "\n";
                
            return operationResult;
        };
        OperationResult pop_front(){
            OperationResult operationResult = "";

            if (isEmpty()){
                operationResult = "error";
            }else{
                operationResult = std::to_string(buffer[head]);
                buffer[head] = 0;
                head = (head+1) % maxSize;
                --size;
            }

            if (operationResult!="")
                std::cout << operationResult << "\n";
                
            return operationResult;
        };        
};

class Dequeue{
    private:
        IDequeueLowLevelInt16DataStorage* dataStorageInt16;
        Dequeue() = delete;
        Dequeue(const Dequeue&) = delete;
        void operator = (const Dequeue&) = delete;
    public:
        Dequeue(uint16_t buffSize){
            dataStorageInt16 = new RingBuffer(buffSize);
        };
        virtual ~Dequeue(){
            delete dataStorageInt16;
        }
        OperationResult push_back(int16_t value){
            return dataStorageInt16->push_back(value);
        };
        OperationResult push_front(int16_t value){
            return dataStorageInt16->push_front(value);
        };
        OperationResult pop_back(){
            return dataStorageInt16->pop_back();
        };
        OperationResult pop_front(){
            return dataStorageInt16->pop_front();
        };
};

int main(){

    #ifdef UNIT_TESTING
        return deqTest();
    #endif    

    int32_t n;
    uint16_t m;
    std::cin >> n >> m;

    Dequeue dq(m);

    std::string command;
    int16_t commandArg;

    for (int32_t cmdIdx=0; cmdIdx<n; ++cmdIdx){

        std::cin >> command;

        if (command == "pop_back")
            dq.pop_back();
        else if (command == "pop_front")
            dq.pop_front();
        else if (command == "push_back"){
            std::cin >> commandArg;
            dq.push_back(commandArg);
        }else if (command == "push_front"){
            std::cin >> commandArg;
            dq.push_front(commandArg);
        }
    }

    return 0;
}

int deqTest(){

    Dequeue* dqTest;

    dqTest = new Dequeue(4);
    assert(dqTest->push_front(861) == "");
    assert(dqTest->push_front(-819) == "");
    assert(dqTest->pop_back() == "861");
    assert(dqTest->pop_back() == "-819");
    delete dqTest;

    dqTest = new Dequeue(10);
    assert(dqTest->push_front(-855) == "");
    assert(dqTest->push_front(0) == "");
    assert(dqTest->pop_back() == "-855");
    assert(dqTest->pop_back() == "0");
    assert(dqTest->push_back(844) == "");
    assert(dqTest->pop_back() == "844");
    assert(dqTest->push_back(823) == "");
    delete dqTest;    

    dqTest = new Dequeue(6);
    assert(dqTest->push_front(-201) == "");
    assert(dqTest->push_back(959) == "");
    assert(dqTest->push_back(102) == "");
    assert(dqTest->push_front(20) == "");
    assert(dqTest->pop_front() == "20");
    assert(dqTest->pop_back() == "102");
    delete dqTest; 

    dqTest = new Dequeue(0);
    assert(dqTest->push_front(1) == "error");
    assert(dqTest->push_back(2) == "error");
    assert(dqTest->pop_front() == "error");
    assert(dqTest->pop_back() == "error");
    delete dqTest;

    dqTest = new Dequeue(1);
    assert(dqTest->push_front(1) == "");
    assert(dqTest->push_back(2) == "error");
    assert(dqTest->pop_front() == "1");
    assert(dqTest->pop_back() == "error");
    delete dqTest;

    dqTest = new Dequeue(1);
    assert(dqTest->push_back(1) == "");
    assert(dqTest->push_front(2) == "error");
    assert(dqTest->pop_front() == "1");
    assert(dqTest->pop_back() == "error");
    delete dqTest;

    dqTest = new Dequeue(1);
    assert(dqTest->push_front(1) == "");
    assert(dqTest->push_back(2) == "error");
    assert(dqTest->pop_back() == "1");
    assert(dqTest->pop_front() == "error");
    assert(dqTest->push_back(2) == "");
    assert(dqTest->pop_back() == "2");
    delete dqTest;

    std::cout << "OK deqTest" << "\n";

    return 0;
};