#include <iostream>
#include <fstream>

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

int FileWork();

int main(){
    std::cout << "Sun " << Sun::GetSun() << "\n"; 

    SimpleObject stoneOne;

    stoneOne.name = "FirstStoneAgain"; 
    stoneOne.weight = 0;

    std::cout << "Hello" << "\n";
    std::cout << stoneOne.to_string() << "\n";

    std::cout << "Sun " << Sun::GetSun() << "\n";     

    FileWork();
}

int FileWork(){
    std::ofstream fileToWrite;
    std::ifstream fileToRead;
    
    std::string fileName = "test_file_2.txt";
    std::string textFromFile;

    fileToWrite.open(fileName);
    fileToWrite << "test string";
    fileToWrite.close();

    fileToRead.open(fileName);
    std::getline(fileToRead, textFromFile);
    

    //fileToRead >> textFromFile;

    std::cout << textFromFile << std::endl;
}