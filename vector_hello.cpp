#include "vector_hello.hpp"

void vector_hello(){

    long unsigned int vectorSize;

    std::cout << "input vector Size: ";
    std::cin >> vectorSize;
    std::vector<std::string> vectorTest(vectorSize);

    std::cout << "input vector elemets: ";
    for(long unsigned int i=0; i<vectorSize; ++i){
        std::cin >> vectorTest[i];
    }

    std::cout << "scr vector: " << vector2string(vectorTest, " ") << endl;

    vectorTest.pop_back();

    std::cout << "pop back vector: " << vector2string(vectorTest, " ");

}

std::string vector2string(const std::vector<std::string> vector, const std::string splitter){

    std::string resultStr;

    for (auto it = vector.begin(); it != vector.end(); it++){
        if (it != vector.begin())
            resultStr = resultStr + splitter;
        resultStr = resultStr + *it;
    }

    return resultStr;
}