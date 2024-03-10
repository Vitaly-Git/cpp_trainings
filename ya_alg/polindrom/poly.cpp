#include <iostream>
#include <algorithm>
#include <string>
#include <cassert>

bool isPolyndrome(std::string srcString);
void isPolyndromeTest();

int main(){
    isPolyndromeTest();
    return 0;
}

void isPolyndromeTest(){
    assert(isPolyndrome("111") == true);
    assert(isPolyndrome("1") == true);
    assert(isPolyndrome("") == true);
    assert(isPolyndrome("112") == false);
    assert(isPolyndrome("123454321") == true);
    assert(isPolyndrome("123453421") == false);
    assert(isPolyndrome("DfgFd") == true);
    assert(isPolyndrome("D fgf d") == true);
    assert(isPolyndrome("yDfgf dy") == true);
    assert(isPolyndrome("11122211") == false);

    std::cout << "OK isPolyndrome" << std::endl;
}

bool isPolyndrome(std::string srcString){
    bool isPoly = false;

    std::string processString = srcString; 

    std::transform(processString.begin(), processString.end(), processString.begin(), [](u_char chr){return std::tolower(chr);});
    processString.erase(std::remove(processString.begin(), processString.end(), ' '), processString.end());

    isPoly = (processString == std::string(processString.rbegin(), processString.rend()));
    return isPoly;
}