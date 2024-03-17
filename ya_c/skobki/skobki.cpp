#include <iostream>

void makePars(std::string resString, int64_t openParsRemain, int64_t closeParsRemain);

int main(){

    int64_t parsCount;
    std::cin >> parsCount;

    std::string resString;
    makePars(resString, parsCount, parsCount);

    return 0;
}

void makePars(std::string resString, int64_t openParsRemain, int64_t closeParsRemain){

    if (openParsRemain == 0 && closeParsRemain == 0){
        std::cout << resString << std::endl;
        return;
    }

    if (openParsRemain > 0)     
        makePars(resString + "(", openParsRemain - 1, closeParsRemain);

    if (openParsRemain < closeParsRemain) 
        makePars(resString + ")", openParsRemain, closeParsRemain - 1);
}
