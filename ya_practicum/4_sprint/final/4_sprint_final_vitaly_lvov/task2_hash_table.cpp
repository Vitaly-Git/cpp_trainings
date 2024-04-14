/*
Ссылка на отчёт в контесте:
https://contest.yandex.ru/contest/24414/run-report/111728928/

-- ПРИНЦИП РАБОТЫ --
1. Нам необходимо реализовать хэш-таблицу для хранения данных.
2. Нам предоставлен список обязательных операций, которые должна реализовывать хэш-таблица: 
   put(key, value), get(key)->value/«None», delete(key).
3. В таблице хранятся уникальные ключи.
4. Требования к реализации: 
 • Нельзя использовать имеющиеся в языках программирования реализации хеш-таблиц 
   (std::unordered_map в С++, dict в Python, HashMap в Java, и т. д.)
 • Разрешать коллизии следует с помощью метода цепочек или с помощью открытой адресации.
 • Все операции должны выполняться за O(1) в среднем.
 • Поддерживать рехеширование и масштабирование хеш-таблицы не требуется.
 • Ключи и значения, id сотрудников и их зарплата, —– целые числа. Поддерживать 
   произвольные хешируемые типы не требуется.
   Алгоритм решения задачи:
1. Нам необходимо реализовать конкретную сущность с конкретными действиями. 
2. Исходя из опыта и шаблонов разработки, мы предполагаем, что в будущем возможно расширение 
   функционала, и реализация функционала может меняться. 
   Например, мы найдем второй способ реализации с меньшей сложностью или захотим сравнить 
   наш вариант с реализацией хэш-таблицы из стандартной библиотеки.
3. Поэтому, создадим абстрактный интерфейс «Хэш-таблица».
4. Реализацию интерфейса возложим на более низкий уровень, в котором будем применять 
   конкретные механики, в соответствии с требованиями задачи.
5. В качестве метода разрешения коллизий выберем метод цепочек.
6. Цепочки реализуем с помощью связанного списка.
7. Связанный список реализован в классе ConnectedList.
8. Хэш-таблица реализована как вектор состоящий из указателей на головы связанных списоков,
   что позволяет нам проходить по всем ключам в списке.
9. Хэш вычисляется через остаток от деления.   
-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
1. Реализация опиралась на теорию занятий в соответствии с выбранным алгоритмом решения.
2. Выходные параметры решенной задачи соответствуют требованиям к задаче.
-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
1. Скорость работы с хэш-таблицей равняется О(1), но у нас есть связанный список, доступ к элементам
   которого осуществляется за O(N). Поэтому в лучшем случае сложность равна О(1), в худшем случае
   O(N).
-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
1. Для хранения данных используем как вектор так и связанный список. Если вектор постоянен О(1), 
   то объем занимаемых данных связанного списка в худшем случае будет равна O(N).
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <optional>

struct KeyValue{
    int32_t key;
    int32_t value;
};

class IHashTable{
    public:
        virtual void put(int32_t key, int32_t value) = 0;
        virtual std::optional<int32_t> get(int32_t key) = 0;
        virtual std::optional<KeyValue> del(int32_t key) = 0;
        virtual int32_t hashOfKey(int32_t key) = 0;
        virtual int32_t hashOfBusketByKey(int32_t Key) = 0;
        virtual int32_t hashOfBusketByHashOfKey(int32_t hashKey) = 0;
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
                if (next->getItemValue().key==key){
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

        std::optional<KeyValue> deleteItemByKey(int32_t key){
            ListItem* itemToDelete = nullptr;
            
            ListItem* prev = nullptr;
            ListItem* next = head;

            KeyValue delValue;

            while (next!=nullptr){
                if (next->getItemValue().key==key){
                    itemToDelete = next;
                    delValue = {
                        itemToDelete->getItemValue().key,
                        itemToDelete->getItemValue().value
                        };                    
                    break;
                }
                prev = next;
                next = next->getNext();
            }         
            
            if (itemToDelete == nullptr)
                return std::nullopt; 

            if (prev == nullptr)
                head = itemToDelete->getNext();
            else
                prev->setNext(itemToDelete->getNext());

            delete itemToDelete;

            return delValue;
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

            KeyValue dataToSave({key, value});
            ConnectedList* connectedList = getConnectedListPtrFromHashTableByKey(key);

            ListItem* listItem = connectedList->getItemByKey(key);
            if (listItem == nullptr)
                connectedList->addItem({key, value});
            else
                listItem->setItemValue(dataToSave);
        };

        std::optional<int32_t> get(int32_t key) override{
            ConnectedList* connectedList = getConnectedListPtrFromHashTableByKey(key);

            ListItem* listItem = connectedList->getItemByKey(key);
            if (listItem == nullptr)
                return std::nullopt;
            else
                return listItem->getItemValue().value;    

        };

        std::optional<KeyValue> del(int32_t key) override {
            ConnectedList* connectedList = getConnectedListPtrFromHashTableByKey(key);
            std::optional<KeyValue> delResult = connectedList->deleteItemByKey(key);
            return delResult;
        };
    
    private:
        int hashTableSize;
        std::vector<ConnectedList>* hashTable;

        int32_t hashOfKey(int32_t key) override {
            int32_t hashKey     = abs(key) % hashTableSize;
            return hashKey;
        };

        int32_t hashOfBusketByKey(int32_t key) override {
            int32_t hashKey     = hashOfKey(key);
            int32_t hashBuscket = hashKey % hashTableSize;
            return hashBuscket;
        };

        int32_t hashOfBusketByHashOfKey(int32_t hashKey) override {
            int32_t hashBuscket = hashKey % hashTableSize;
            return hashBuscket;
        };  

        ConnectedList* getConnectedListPtrFromHashTableByKey(int32_t key){
            int32_t hashBuscket = hashOfBusketByKey(key);
            ConnectedList* connectedList = &((*hashTable)[hashBuscket]);
            return connectedList;
        }
}; 

int main(){

    HashTable hashTable;

    int32_t n;
    std::cin >> n;

    std::string cmd;
    int32_t key;
    int32_t value;

    for(int32_t cmdCnt=0; cmdCnt<n; ++cmdCnt){

        std::cin >> cmd;

        if (cmd == "get"){

            std::cin >> key;
            std::optional<int32_t> optValue = hashTable.get(key);
            if (optValue == std::nullopt)
                std::cout << "None" << "\n";
            else    
                std::cout << optValue.value() << "\n";

        } else if (cmd == "put"){
            
            std::cin >> key >> value;
            hashTable.put(key, value);

        } else if (cmd == "delete"){
            
            std::cin >> key;
            std::optional<KeyValue> delResult = hashTable.del(key);

             if (delResult == std::nullopt)
                std::cout << "None" << "\n";
            else    
                std::cout << delResult.value().value << "\n";           
        }
    }

    return 0;
}