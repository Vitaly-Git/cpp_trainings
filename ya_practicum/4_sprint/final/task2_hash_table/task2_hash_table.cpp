/*
Я.П. Хэш-таблица

Теория

Дано:

 1. Нам необходимо реализовать хэш-таблицу для хранения данных.
 2. Нам предоставлен список обязательных операций, которые должна реализовывать хэш-таблица: put(key, value), get(key)->value/«None», delete(key).
 3. В таблице хранятся уникальные ключи.
 4. Требования к реализации: 
 • Нельзя использовать имеющиеся в языках программирования реализации хеш-таблиц (std::unordered_map в С++, dict в Python, HashMap в Java, и т. д.)
 • Разрешать коллизии следует с помощью метода цепочек или с помощью открытой адресации.
 • Все операции должны выполняться за O(1) в среднем.
 • Поддерживать рехеширование и масштабирование хеш-таблицы не требуется.
 • Ключи и значения, id сотрудников и их зарплата, —– целые числа. Поддерживать произвольные хешируемые типы не требуется.

Алгоритм решения задачи.
 1. Нам необходимо реализовать конкретную сущность с конкретными действиями. 
 2. Исходя из опыта и шаблонов разработки, мы предполагаем, что в будущем возможно расширение функционала, и реализация функционала может меняться. Например, мы найдем второй способ реализации с меньшей сложностью или захотим сравнить наш вариант с реализацией хэш-таблицы из стандартной библиотеки.
 3. Поэтому, создадим абстрактный интерфейс «Хэш-таблица».
 4. Реализацию интерфейса возложим на более низкий уровень, в котором будем применять конкретные механики, в соответствии с требованиями задачи.
 5. В качестве метода разрешения коллизий выберем метод цепочек.
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <optional>
#include <variant>

//#define UNIT_TESTING

int hashTableTest();

class IHashTable{
    public:
        virtual void put(int64_t key, int64_t value) = 0;
        virtual std::variant<int64_t, std::string> get(int64_t key) = 0;
        virtual std::optional<int64_t> del(int64_t key) = 0;
        virtual int64_t hashOfKey(int64_t key) = 0;
        virtual int64_t hashOfBusketByHashOfKey(int64_t hashOfKey) = 0;
};

struct KeyValue{
    int64_t key;
    int64_t value;
};

class IConnectedListKeyValue{
    public:
};

class ListItem{
    private:
        int64_t itemValue = 0;
        ListItem* next = nullptr;
    public:
        ListItem(int64_t newItemValue):itemValue(newItemValue){
        }
        ~ListItem(){
        }
        int64_t getItemValue(){
            return itemValue;
        }
        void setItemValue(int64_t newItemValue){
            itemValue = newItemValue;
        }
        ListItem* getNext(){
            return next;
        }
        void setNext(ListItem* newNexItem){
            next = newNexItem;
        }
};

class ConnectedList{
    private:
        ListItem* head = nullptr;
    public:    
        ConnectedList() = default;
        ~ConnectedList(){
            ListItem* next = head;
            while (next!=nullptr){
                ListItem* itemToDelete = next;
                next = next->getNext();
                delete itemToDelete;
            }
        }

        ListItem* getLastItem(){
            ListItem* last = head;
            ListItem* next = head;
            while (next!=nullptr){
                last = next;
                next = next->getNext();
            }
            return last;
        }

        ListItem* getItemByValue(int64_t itemValue){
            ListItem* resulItem = nullptr;
            
            ListItem* next = head;
            while (next!=nullptr){
                if (next->getItemValue()!=itemValue){
                    resulItem = next;
                    break;
                }
                next = next->getNext();
            }

            return resulItem;
        }

        void addItem(int64_t newItemValue){
            ListItem* newListItem = new ListItem(newItemValue);
            if (head == nullptr)
                head = newListItem;
            else    
                getLastItem()->setNext(newListItem);
        }

        void deleteItem(int64_t itemValue){
            ListItem* itemToDelete = nullptr;
            
            ListItem* prev = nullptr;
            ListItem* next = head;

            while (next!=nullptr){
                if (next->getItemValue()==itemValue){
                    itemToDelete = next;
                    break;
                }
                prev = next;
                next = next->getNext();
            }           

            if (prev == nullptr)
                head = itemToDelete->getNext();
            else
                prev->setNext(itemToDelete->getNext());

            delete itemToDelete;
        }

        void reverse(){
            if (head == nullptr)
                return;

            ListItem* prevItem = nullptr;
            ListItem* curItem = head;
            ListItem* nextItem = head->getNext();
            while(nextItem!=nullptr){
                ListItem* nextNextItem = nextItem->getNext();
                nextItem->setNext(curItem);
                curItem->setNext(prevItem);
                prevItem = curItem;
                curItem = nextItem;
                nextItem = nextNextItem;
            }

            head = curItem;
        }

        // std::string to_string(){
        operator std::string() const{
            
            std::string resultString = "";

            ListItem* next = head;
            while (next!=nullptr){
                
                if (next != head)
                    resultString.append(" ");
                
                resultString.append(std::to_string(next->getItemValue()));
                
                next = next->getNext();
            }

            return resultString;
        }
};

class HashTable:IHashTable{
    public:
        HashTable(){
            hashTableSize = 100000;
            hashTable = new std::vector<ConnectedList>(hashTableSize);
        }
        ~HashTable(){
            delete hashTable;
        }

        void put(int64_t key, int64_t value) override {

        };

        std::variant<int64_t, std::string> get(int64_t key) override{

        };

        std::optional<int64_t> del(int64_t key) override {

        };

        int64_t hashOfKey(int64_t key) override {

        };

        int64_t hashOfBusketByHashOfKey(int64_t hashOfKey) override {
            
        };       
    private:
        int hashTableSize;
        std::vector<ConnectedList>* hashTable;
}; 

int main(){




    return 0;
}