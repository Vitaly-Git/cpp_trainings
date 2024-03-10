#include <iostream>
#include <cassert>

void connectedListTest();

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

int main(){
    connectedListTest();
    return 0;
}

void connectedListTest(){

    ConnectedList cl;
    assert(std::string(cl) == "");

    cl.addItem(0);
    assert(std::string(cl) == "0");

    cl.addItem(1);
    assert(std::string(cl) == "0 1");

    cl.addItem(2);
    assert(std::string(cl) == "0 1 2");

    cl.addItem(3);
    assert(std::string(cl) == "0 1 2 3");

    cl.deleteItem(2);
    assert(std::string(cl) == "0 1 3");

    cl.addItem(5);
    assert(std::string(cl) == "0 1 3 5");

    cl.deleteItem(5);
    assert(std::string(cl) == "0 1 3");

    cl.deleteItem(0);
    assert(std::string(cl) == "1 3");

    cl.deleteItem(1);
    cl.deleteItem(3);
    assert(std::string(cl) == "");
    
    cl.reverse();
    assert(std::string(cl) == "");

    cl.addItem(1);
    cl.reverse();
    assert(std::string(cl) == "1");

    cl.addItem(2);
    assert(std::string(cl) == "1 2");
    cl.reverse();
    assert(std::string(cl) == "2 1");

    cl.deleteItem(1);
    assert(std::string(cl) == "2");

    cl.deleteItem(2);
    assert(std::string(cl) == "");

    cl.addItem(0);
    cl.addItem(1);
    cl.addItem(2);
    cl.addItem(3);
    cl.addItem(4);
    assert(std::string(cl) == "0 1 2 3 4");

    cl.reverse();
    assert(std::string(cl) == "4 3 2 1 0");

    std::cout << "OK connectedListTest" << std::endl;
}
