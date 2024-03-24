/*
-- ПРИНЦИП РАБОТЫ --
1. Очередь реализована на кольцевом буфере.
2. По условию задачи требуется чтобы все операции выполнялись за О(1),
   поэтому в качестве контейнера кольцевого буфера выбран вектор.
3. Вектор обеспеченивает обращение к элементампо индексу за О(1), а
   т.к. мы задаем размер изначально, то перевыделения памяти не будет.
4. Типы значений размеров и указателей кольцевого буфера выбраны как 
   uint16_t (значения от 0 до 65535), а максимальный размер дека не 
   более 50 000.
5. Тип элементов вектора int16_t (значения от -32767 до 32767), а
   по условию задачи хранимое значение не превосходит 1000.
6. Для обеспечения приемственности свойств, дек является наследником
   кольцевого буфера и вызывает его методы.
*/


#include <iostream>
#include <vector>
#include <cassert>

//#define UNIT_TESTING

int deqTest();

class RingBuffer{
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
        void push_back(int16_t value){
            if (isFull()){
                std::cout << "error" << "\n";
            }else{
                buffer[tail] = value;
                tail = (tail+1) % maxSize;
                ++size;
            }
        };
        void push_front(int16_t value){
            if (isFull()){
                std::cout << "error" << "\n";
            }else{
                head = (head==0?maxSize-1:head-1) % maxSize;
                buffer[head] = value;
                ++size;
            }
        };
        void pop_back(){
            if (isEmpty()){
                std::cout << "error" << "\n";
            }else{
                tail = (tail==0?maxSize-1:tail-1) % maxSize;
                std::cout << buffer[tail] << "\n";
                buffer[tail] = 0;
                --size;
            }
        };
        void pop_front(){
            if (isEmpty()){
                std::cout << "error" << "\n";
            }else{
                std::cout << buffer[head] << "\n";
                buffer[head] = 0;
                head = (head+1) % maxSize;
                --size;
            }
        };        
};

class Dequeue : public RingBuffer{
    private:
        Dequeue() = delete;
        Dequeue(const Dequeue&) = delete;
        void operator = (const Dequeue&) = delete;
    public:
        Dequeue(uint16_t buffSize):RingBuffer(buffSize){};
};

int main(){

    #ifdef UNIT_TESTING
        return deqTest();
    #endif    

    int32_t n;
    uint16_t m;
    std::cin >> n >> m;

    Dequeue dq(m);

    //std::cin.ignore();
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

    std::cout << "OK deqTest" << "\n";

    return 0;
};