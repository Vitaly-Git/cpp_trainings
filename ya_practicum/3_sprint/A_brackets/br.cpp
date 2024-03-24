#include <iostream>
#include <cassert>

//#define UNIT_TESTING

void printBrackets(std::string resultStr, int64_t leftBrCount, int64_t rightBrCount);
int printBracketsTest();

int main(){

    #ifdef UNIT_TESTING
        return printBracketsTest();
    #endif

    int16_t n;
    std::cin >> n;

    std::string resultStr;
    printBrackets(resultStr, n, n);

    return 0;
}

int printBracketsTest(){
    return 0;
}

void printBrackets(std::string resultStr, int64_t leftBrCount, int64_t rightBrCount){

    if (leftBrCount==0 && rightBrCount==0){
        std::cout << resultStr << "\n";
        return;
    }

    if (leftBrCount > 0)
        printBrackets(resultStr + "(", leftBrCount-1, rightBrCount);

    if (leftBrCount < rightBrCount)
        printBrackets(resultStr + ")", leftBrCount, rightBrCount-1);
}
