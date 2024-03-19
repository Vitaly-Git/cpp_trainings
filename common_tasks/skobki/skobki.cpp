#include <iostream>

void bracketOut(std::string dstStr, int64_t leftSkokaCnt, int64_t rightSkobkaCnt);

int main(){

    int64_t brCnt;
    std::cin >> brCnt;

    std::string dstStr = "";
    bracketOut(dstStr, brCnt, brCnt);

    return 0;
}

void bracketOut(std::string dstStr, int64_t leftBrCnt, int64_t rightBrCnt){

    if(leftBrCnt==0 && rightBrCnt==0){
        std::cout << dstStr << std::endl;    
        return;
    }

    if(leftBrCnt>0)
        bracketOut(dstStr+"(", leftBrCnt-1, rightBrCnt);

    if(leftBrCnt < rightBrCnt)
    //if(rightBrCnt>0)
        bracketOut(dstStr+")", leftBrCnt, rightBrCnt-1);
}