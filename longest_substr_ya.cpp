#include "longest_substr_ya.hpp"

void longestSubstrExecute(){
    std::string srcStr = "dabcbaddc";
    std::cout << longestSubstr("dabcbaddc") << std::endl;
    std::cout << longestSubstr("abcabcdd") << std::endl;
}

std::string longestSubstr(std::string srcStr){

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

    return longestSubStr;
}