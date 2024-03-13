#include <iostream>
#include <stack>
#include <string>
#include <typeinfo>
#include <vector>
#include <array>
#include <list>
#include <map>

template <typename T>
void containerCout(T container);

int main(){

    std::stack<int> stackTest;
    stackTest.push(1);
    stackTest.push(2);
    
    std::vector<int> vectorTest;
    vectorTest.push_back(1);
    vectorTest.push_back(2);
    containerCout(vectorTest);

    std::list<int> listTest;
    listTest.push_back(1);
    listTest.push_back(2);
    containerCout(listTest);

    std::map<std::string,int> mapTest;
    mapTest["key1"] = 1;
    mapTest["key2"] = 1;
    // containerCout(mapTest);

    return 0;
}

template <typename T>
void containerCout(T container){
    // std::cout<<std::typeid(container).name();
    std::cout<<" [";

    for(auto it=container.begin(); it!=container.end(); ++it){
        if (it!=container.begin())
            std::cout<<" ";
        std::cout<<*it;
    }

    std::cout<<"]"<<std::endl;
}