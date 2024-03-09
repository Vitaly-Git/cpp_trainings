#include <iostream>
#include <vector>
#include <cassert>
#include <iterator>

int32_t rope(int32_t n, std::vector<int32_t> ropesLengths);
void ropeTest();

int main(){
    ropeTest();
    return 0;
}

void ropeTest(){
    assert(rope(4, {1,5,2,1}) == 1);
    assert(rope(4, {5,12,4,3}) == 24);
}

int32_t rope(int32_t n, std::vector<int32_t> ropesLengths){

    int32_t minRopeLen = 0;

    int32_t maxRope = 0;
    int32_t sumRope = 0;
    for(auto it=ropesLengths.begin(); it!=ropesLengths.end(); ++it){
        maxRope = std::max(maxRope, *it);
        sumRope += *it;
    }

    

    return minRopeLen;
}