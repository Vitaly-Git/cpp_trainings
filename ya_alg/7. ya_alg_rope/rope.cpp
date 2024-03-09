#include <iostream>
#include <vector>
#include <cassert>
#include <iterator>

int32_t rope(const std::vector<int32_t>& ropesLengths);
void ropeTest();

int main(){
    // ropeTest();

    int32_t n;
    std::cin >> n;
    std::vector<int32_t> ropeLengths(n); 

    for(int32_t i=0; i<n; ++i)
        std::cin >> ropeLengths[i];

    std::cout << rope(ropeLengths);

    return 0;
}

void ropeTest(){
    assert(rope({1,5,2,1}) == 1);
    assert(rope({5,12,4,3}) == 24);
    assert(rope({3,4,5}) == 12);

    std::cout << "OK ropeTest";
}

int32_t rope(const std::vector<int32_t>& ropesLengths){

    int32_t minRopeLen = 0;

    int32_t maxRope = 0;
    int32_t sumRope = 0;
    for(auto it=ropesLengths.begin(); it!=ropesLengths.end(); ++it){
        maxRope = std::max(maxRope, *it);
        sumRope += *it;
    }
    sumRope -= maxRope;

    if (sumRope < maxRope)
        minRopeLen = maxRope - sumRope;
    else if (sumRope > maxRope)
        minRopeLen = maxRope + sumRope;
    else    
        minRopeLen = maxRope*2;

    return minRopeLen;
}