#include <iostream>


class Sun{

private:
    Sun(){};
    static Sun* sun_;

public:
    Sun(Sun &other) = delete;
    void operator=(const Sun) = delete;
    
    static Sun* GetSun(){
        if (sun_ == nullptr)
            sun_ = new Sun();
        return sun_;    
    };
};

Sun* Sun::sun_ = nullptr;

class SimpleObject{
public:    
    std::string name;
    int64_t weight;
    std::string to_string();
};

std::string SimpleObject::to_string(){
    return "Name: " + name + "\n" + "Weight: " + std::to_string(weight) + "\n";
}

int main(){
    std::cout << "Sun " << Sun::GetSun() << "\n"; 

    SimpleObject stoneOne;

    stoneOne.name = "FirstStoneAgain"; 
    stoneOne.weight = 0;

    std::cout << "Hello" << "\n";
    std::cout << stoneOne.to_string() << "\n";

    std::cout << "Sun " << Sun::GetSun() << "\n";     
}