#include <iostream>
#include <string>

class Duck{
    public:
        bool quack(){
            return true;
        }
};

class Goose{
    public:
        int quack(){
            return 4;
        }
};

template <typename T>
bool doQuack(T duck){
    return duck.quack();
};

int main(){
    Duck duck;
    Goose goose;
    std::cout << doQuack(duck) << "\n";
    std::cout << doQuack(goose) << "\n";
}