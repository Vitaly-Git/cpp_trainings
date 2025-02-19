#include <iostream>

class WorldObject{
public:    
    std::string name;
    int64_t weight;
    std::string to_string();
};

std::string WorldObject::to_string(){
    return "Name: " + name + "\n" + "Weight: " + std::to_string(weight) + "\n";
}

int main(){
    WorldObject stoneOne;

    stoneOne.name = "FirstStoneAgain"; 
    stoneOne.weight = 0;

    std::cout << "Hello" << "\n";
    std::cout << stoneOne.to_string() << "\n";
}