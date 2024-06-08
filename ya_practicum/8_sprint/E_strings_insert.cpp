#include <iostream>
#include <vector>
#include <algorithm>

struct String{
    std::string str;
    int pos;
};

int main(){

    std::string srcStr;
    int n;

    std::getline(std::cin, srcStr);
    std::cin >> n;

    std::vector<String> words(n);
    for(int i=0; i<n; ++i)
        std::cin >> words[i].str >> words[i].pos;
    std::sort(words.begin(), words.end(), [](String& lhs, String &rhs){return lhs.pos < rhs.pos;});

    std::string dstStr;
    int lastPos = 0;
    for (const String& word : words){
        dstStr += srcStr.substr(lastPos, word.pos - lastPos);
        dstStr += word.str;
        lastPos = word.pos;
    }
    dstStr += srcStr.substr(lastPos, srcStr.size() - lastPos);

    std::cout << dstStr;

    return 0;
}