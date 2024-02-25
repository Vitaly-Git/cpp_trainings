#include "testing.hpp"
#include "longest_substr_ya.hpp"

void test_longestSubstr(){
    assert(longestSubstr("dabcbaddc") == "dabc");
    assert(longestSubstr("abcabcdd") == "abcd");
    assert(longestSubstr("abcabcdd") != "abc");
    std::cout << "All test is OK longestSubstr" << std::endl;
}