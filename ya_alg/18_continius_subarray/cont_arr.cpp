#include <iostream>
#include <vector>
#include <map>
#include <cassert>
#include <cmath>

int64_t subArrLen(std::vector<int32_t> srcVector);
void subArrLenTest();

int main(){
    subArrLenTest();
    return 0;
}

void subArrLenTest(){
    assert(subArrLen({1,2,3,4,2,7,5,6}) == 6);
    assert(subArrLen({1,2,3,4,2,7,5,6,4,15,16,17,18,19,20}) == 11);
    assert(subArrLen({1,2,3,4,2,7}) == 4);
    assert(subArrLen({1,2,3,4,2,7,1,4,5}) == 5);
    assert(subArrLen({1,2,3,3,4,5,6,7,1}) == 6);
    assert(subArrLen({1,1,2,2,2}) == 2);

    std::cout << "OK subArrLenTest" << std::endl;
}

int64_t subArrLen(std::vector<int32_t> srcVector){

    int64_t maxLen = 0;
    std::map<int64_t, int64_t> prevPosesSym;
    int64_t curSubstrStart = 0;

    for(int i=0; i<srcVector.size(); ++i){
        int64_t curLen = 0;
        int64_t curSym = srcVector[i];
        int64_t prevPosSym = prevPosesSym[curSym];

        curSubstrStart = std::max(curSubstrStart, prevPosSym);
        curLen = i - curSubstrStart + 1;
        maxLen = std::max(maxLen, curLen);
        prevPosesSym[curSym] = i+1;
    }

    return maxLen;
}