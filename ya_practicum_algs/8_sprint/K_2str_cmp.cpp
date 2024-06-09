#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main(){

    std::string str1;
    std::string str2;

    std::getline(std::cin, str1);
    std::getline(std::cin, str2);

    // std::vector<char> = {'abcdefghijklmnopqrstuvwxyz'};
    //std::vector<char> abc = {'b','d','f','h','j','l','n','p','r','t','v','x','z'};
    std::vector<char> abc = {'a','c','e','g','i','k','m','o','q','s','u','w','y'};

    for (const char let : abc ){
        // std::replace(str1.begin(), str1.end(), let, 'b');
        // std::replace(str2.begin(), str2.end(), let, 'b');
        str1.erase(std::remove(str1.begin(), str1.end(), let), str1.end());
        str2.erase(std::remove(str2.begin(), str2.end(), let), str2.end());
    }

    if (str1 == str2)
        std::cout << 0;
    else if (str1 < str2)
        std::cout << -1;
    else if (str1 > str2)
        std::cout << 1;
        
    return 0;
}