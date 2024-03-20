#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

std::vector<int16_t>& findHeibhor(const std::vector<int16_t>& nums, std::vector<int16_t>& resNums, 
    int16_t n, int16_t m, int16_t y, int16_t x);
void findHeibhorTest();

int main(){

    //findHeibhorTest();

    std::vector<int16_t> resNums;

    int16_t n = 0;
    int16_t m = 0;
    int16_t x = 0;
    int16_t y = 0;
    std::cin >> n >> m;

    std::vector<int16_t> nums(n*m);
    for(int16_t in=0; in<n; ++in)
        for(int16_t im=0; im<m; ++im)
            std::cin >> nums[im*n+in];

    std::cin >> y >> x;

    findHeibhor(nums,resNums,n,m,y,x);

    for(auto it=resNums.begin(); it!=resNums.end(); ++it){
        if (it!=resNums.begin())
            std::cout << " ";
        std::cout << *it;
    }

    return 0;
}

void findHeibhorTest(){

    std::vector<int16_t> nums;
    std::vector<int16_t> resNums;
    std::vector<int16_t> resPlan;
    nums = {123, 456, 567,
            23,  4,   5,
            159, 256, 31,
            12,  56,  32,
            1,   3,   2};
    nums = {123, 23, 159, 12, 1,
            456, 4, 256, 56, 3,
            567, 5, 31, 32, 2};

    findHeibhor(nums,resNums,5,3,0,0); resPlan = {23, 456};
    assert(std::equal(resNums.begin(), resNums.end(), resPlan.begin(), resPlan.end()));

    findHeibhor(nums,resNums,5,3,0,1); resPlan = {4, 123, 567};
    assert(std::equal(resNums.begin(), resNums.end(), resPlan.begin(), resPlan.end()));

    findHeibhor(nums,resNums,5,3,0,2); resPlan = {5, 456};
    assert(std::equal(resNums.begin(), resNums.end(), resPlan.begin(), resPlan.end()));

    findHeibhor(nums,resNums,5,3,1,2); resPlan = {4, 31, 567};
    assert(std::equal(resNums.begin(), resNums.end(), resPlan.begin(), resPlan.end()));

    findHeibhor(nums,resNums,5,3,4,2); resPlan = {3, 32};
    assert(std::equal(resNums.begin(), resNums.end(), resPlan.begin(), resPlan.end()));

    findHeibhor(nums,resNums,5,3,4,1); resPlan = {1, 2, 56};
    assert(std::equal(resNums.begin(), resNums.end(), resPlan.begin(), resPlan.end()));

    findHeibhor(nums,resNums,5,3,4,0); resPlan = {3, 12};
    assert(std::equal(resNums.begin(), resNums.end(), resPlan.begin(), resPlan.end()));

    findHeibhor(nums,resNums,5,3,2,0); resPlan = {12, 23, 256};
    assert(std::equal(resNums.begin(), resNums.end(), resPlan.begin(), resPlan.end()));

    findHeibhor(nums,resNums,5,3,1,1); resPlan = {5, 23, 256, 456};
    assert(std::equal(resNums.begin(), resNums.end(), resPlan.begin(), resPlan.end()));

    std::cout << "OK findHeibhorTest" << std::endl;
}

std::vector<int16_t>& findHeibhor(const std::vector<int16_t>& nums, std::vector<int16_t>& resNums, 
    int16_t n, int16_t m, int16_t y, int16_t x){

    resNums.clear();

    int32_t numsCnt = n*m;
    int32_t baseNum = x*n+y;
    int32_t tempCalcIdx = 0;

    if (tempCalcIdx = baseNum+n; tempCalcIdx < numsCnt) // right
        resNums.push_back(nums[tempCalcIdx]);

    if (tempCalcIdx = baseNum-1; tempCalcIdx >= 0 && baseNum%n!=0) // top
        resNums.push_back(nums[tempCalcIdx]);

    if (tempCalcIdx = baseNum-n; tempCalcIdx >= 0) // left
        resNums.push_back(nums[tempCalcIdx]);

    if (tempCalcIdx = baseNum+1; tempCalcIdx < numsCnt && tempCalcIdx%n!=0) // down
        resNums.push_back(nums[tempCalcIdx]);

    std::sort(resNums.begin(), resNums.end());

    return resNums;
}