#include <iostream>
#include <cmath>
#include <cassert>

void intervalLenTest();
int intervalLen(int32_t intr1Centr,int32_t intr1Len, int32_t intr2Centr,int32_t intr2Len);
int intervalLenV1(int32_t intr1Centr,int32_t intr1Len, int32_t intr2Centr,int32_t intr2Len);

int main(){
    // intervalLenTest();
    int32_t intr1Centr, intr1Len;
    int32_t intr2Centr, intr2Len;

    std::cin >> intr1Centr >> intr1Len >> intr2Centr >> intr2Len;
    std::cout << intervalLen(intr1Centr, intr1Len, intr2Centr, intr2Len);

    return 0;
}

void intervalLenTest(){
    assert(intervalLen(0,7,12,5) == 25);
    assert(intervalLen(-3,3,5,5) == 17);
    assert(intervalLen(2,1,4,1) == 5);
    assert(intervalLen(2,1,5,1) == 6);
    assert(intervalLen(2,1,6,1) == 6);
    assert(intervalLen(3,1,2,1) == 4);
    assert(intervalLen(2,1,2,1) == 3);
    assert(intervalLen(5,4,6,1) == 9);
    assert(intervalLen(-7,3,-3,2) == 10);
    assert(intervalLen(-7,3,-7,2) == 7);
    assert(intervalLen(2,3,2,3) == 7);

    std::cout << "OK intervalLenTest" << std::endl;
}

int intervalLen(const int32_t intr1Centr,const int32_t intr1Len,const int32_t intr2Centr,const int32_t intr2Len){

    int32_t overlay = intr1Len + intr2Len - (std::max(intr1Centr, intr2Centr) - std::min(intr1Centr, intr2Centr) - 1);

    int32_t totalInterval = std::max(intr1Len + intr1Len + 1,overlay) + 
        std::max(intr2Len + intr2Len + 1,overlay) -
        std::max(overlay,0);

    return totalInterval;    
}

int intervalLenV1(int32_t intr1Centr,int32_t intr1Len, int32_t intr2Centr,int32_t intr2Len){

    int32_t vec1Len = intr1Len;
    int32_t vec2Len = intr2Len;
    int32_t sumVecLen = vec1Len + vec2Len;
    
    int32_t maxCenter = std::max(intr1Centr, intr2Centr);
    int32_t minCenter = std::min(intr1Centr, intr2Centr);

    int32_t centerDist = maxCenter - minCenter - 1;
    int32_t overlay = sumVecLen - centerDist;

    int32_t interval1Len = vec1Len + vec1Len + 1;
    int32_t interval2Len = vec2Len + vec2Len + 1;

    int32_t totalInterval = std::max(interval1Len,overlay) + 
        std::max(interval2Len,overlay) -
        std::max(overlay,0);

    return totalInterval;    
}