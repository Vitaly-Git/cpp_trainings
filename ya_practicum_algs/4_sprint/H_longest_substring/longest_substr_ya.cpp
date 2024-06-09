#include <iostream>
#include <map>


int longestSubstr(std::string srcStr);

int main(){

    std::string inputStr;
    std::getline(std::cin, inputStr);

    std::cout << longestSubstr(inputStr) << '\n';

    return 0;
}

int longestSubstr(std::string srcStr){

    if (srcStr.size() == 1)
        return 1;

    std::string longestSubStr = "";
    int longestSubStrLen = 0;

    std::string curSubStr = "";
    int curSubStrLen = 0;
    std::map<std::string, int> curStrSymbols;

    for (int strStart = 0; strStart < srcStr.length(); ++strStart){
        for (int strEnd = strStart; strEnd < srcStr.length(); ++strEnd){

            std::string curSymbol = srcStr.substr(strEnd, 1);

            if (curStrSymbols.find(curSymbol) == curStrSymbols.end()){
                ++curStrSymbols[curSymbol];
                curSubStr += curSymbol;
                ++curSubStrLen;
            }else{
                if (curSubStrLen > longestSubStrLen){
                    longestSubStr = curSubStr;
                    longestSubStrLen = curSubStrLen;
                }
                curStrSymbols.clear();
                curSubStr = "";
                curSubStrLen = 0;
                break;           
            }

        }
    }

    return longestSubStr.size();
}