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
        virtual void put(int32_t key, int32_t value) = 0;
        virtual std::optional<int32_t> get(int32_t key) = 0;
        virtual std::optional<int32_t> del(int32_t key) = 0;
        virtual int32_t hashOfKey(int32_t key) = 0;
        virtual int32_t hashOfBusketOfKey(int32_t Key) = 0;
        virtual int32_t hashOfBusketByHashOfKey(int32_t hashOfKey) = 0;
};

struct KeyValue{
    int32_t key;
    int32_t value;
};

class ListItem{
    private:
        KeyValue item = {};
        ListItem* next = nullptr;
    public:
        ListItem(KeyValue newItem):item(newItem){
        }
        ~ListItem(){
        }
        KeyValue getItemValue(){
            return item;
        }
        void setItemValue(KeyValue newItem){
            item = newItem;
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

        ListItem* getItemByKey(int32_t key){
            ListItem* resulItem = nullptr;
            
            ListItem* next = head;
            while (next!=nullptr){
                if (next->getItemValue().key!=key){
                    resulItem = next;
                    break;
                }
                next = next->getNext();
            }
            return resulItem;
        }

        void addItem(KeyValue newItemKeyValue){
            ListItem* newListItem = new ListItem(newItemKeyValue);
            if (head == nullptr)
                head = newListItem;
            else    
                getLastItem()->setNext(newListItem);
        }

        void deleteItemByKey(int32_t key){
            ListItem* itemToDelete = nullptr;
            
            ListItem* prev = nullptr;
            ListItem* next = head;

            while (next!=nullptr){
                if (next->getItemValue().key==key){
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

        operator std::string() const{
            
            std::string resultString = "";

            ListItem* next = head;
            while (next!=nullptr){
                
                if (next != head)
                    resultString.append(" ");
                
                resultString.append(std::to_string(next->getItemValue().key));
                resultString.append(":");
                resultString.append(std::to_string(next->getItemValue().value));
                
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

        void put(int32_t key, int32_t value) override {

        };

        std::optional<int32_t> get(int32_t key) override{

        };

        std::optional<int32_t> del(int32_t key) override {

        };

        int32_t hashOfKey(int32_t key) override {

        };

        int32_t hashOfBusketOfKey(int32_t key) override {

        };

        int32_t hashOfBusketByHashOfKey(int32_t hashOfKey) override {

        };       
    private:
        int hashTableSize;
        std::vector<ConnectedList>* hashTable;
}; 

int main(){




    return 0;
}