#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include "print_array.hpp"
#include "var_array.hpp"
#include "vector_hello.hpp"
#include "merge_interval_ya.hpp"
#include "longest_substr_ya.hpp"
#include "testing.hpp"

#include <iostream>
#include <cmath>
#include <cassert>

void intervalLenTest();
int intervalLen(int32_t intr1Centr,int32_t intr1Len, int32_t intr2Centr,int32_t intr2Len);

int main(){
    intervalLenTest();
    // test_isPalindrome();
    // test_romanToInt();
    // test_twoSum();
    // test_longestSubstr();
    //longestSubstrExecute();
    //merger_vector_intervals_start();
    //std::cout << "2";
    //vector_hello();
    //var_array();
    //printArray();
    //printNumbersAsText();
    return 0;
}

void intervalLenTest(){
    assert(intervalLen(0,7,12,5) == 25);
    std::cout << "OK intervalLenTest" << std::endl;
}

int intervalLen(int32_t intr1Centr,int32_t intr1Len, int32_t intr2Centr,int32_t intr2Len){

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