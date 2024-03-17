#include <iostream>
#include <fstream>
#include <set>

int main(){

    int sCount = 0;

    std::ifstream fileToRead("input.txt");
    std::ofstream fileToWrite("output.txt");

    std::string j;
    std::string s;
    
    fileToRead >> j;
    fileToRead >> s;

    std::set<char> unicSyms;
    for(auto i=0;i<j.size();++i)
        unicSyms.insert(j[i]);

    for(auto i=0; i<s.size(); ++i)
        if (unicSyms.find(s[i]) != unicSyms.end())
            ++sCount;

    fileToWrite << sCount;

    return 0;
}
