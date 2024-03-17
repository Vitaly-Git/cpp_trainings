#include <iostream>

int main(){

    int64_t sCount = 0;
    std::string j;
    std::string s;

    std::cin >> j;
    std::cin >> s;

    for(const char c : s)
        sCount += j.find(c)!=std::string::npos;

    std::cout << sCount;

    return 0;
}