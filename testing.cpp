#include "testing.hpp"
#include "longest_substr_ya.hpp"
#include "twoSum.hpp"
#include "romanToInt.hpp"

void test_longestSubstr(){
    assert(longestSubstr("dabcbaddc") == "dabc");
    assert(longestSubstr("abcabcdd") == "abcd");
    assert(longestSubstr("abcabcdd") != "abc");
    std::cout << "All test is OK longestSubstr" << std::endl;
}

void test_twoSum(){

   Solution sl;

    {
        std::vector<int> scrVec = {3,2,4};
        auto res = sl.twoSum(scrVec, 6);
        std::vector<int> OkRes = {1,2};
        assert(res == OkRes);
    } 

    {
        std::vector<int> scrVec = {2,7,11,15};
        auto res = sl.twoSum(scrVec, 9);
        std::vector<int> OkRes = {0,1};
        assert(res == OkRes);
    }     

    {
        std::vector<int> scrVec = {3,3};
        auto res = sl.twoSum(scrVec, 6);
        std::vector<int> OkRes = {0,1};
        assert(res == OkRes);
    }    

    std::cout << "Ok test_twoSum" << std::endl;
}

void test_romanToInt(){

    Solution_romanToInt sl;

    assert(sl.romanToInt("III") == 3);
    assert(sl.romanToInt("LVIII") == 58);
    assert(sl.romanToInt("MCMXCIV") == 1994);
    assert(sl.romanToInt("DCXXI") == 621);

    // std::string str;
    // std::getline(std::cin, str);
}