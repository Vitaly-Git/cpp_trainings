#include <iostream>
#include <fstream>

int main(){

    std::string scrStr;
    std::string dstStr;

    // std::ifstream fileToRead("input.txt");
    // std::ofstream fileToWrite("output.txt");

    // std::getline(fileToRead, scrStr);
    std::getline(std::cin, scrStr);

    int wordLen = 0;
    int wordCount = 0;
    for (int i=scrStr.size()-1; i>=0; --i){
        if (scrStr[i] == ' '){
            //dstStr = dstStr + (wordCount > 0 ? " " : "") + scrStr.substr(i+1, wordLen);
            dstStr = dstStr + scrStr.substr(i+1, wordLen) + " ";
            wordLen = 0;
            ++wordCount;
        } else {
            ++wordLen;
        }
    }

    if (wordLen > 0)
        //dstStr = dstStr + (wordCount > 0 ? " " : "") + scrStr.substr(0, wordLen+1);
        dstStr = dstStr + scrStr.substr(0, wordLen);

    //fileToWrite << dstStr;
    std::cout << dstStr;
    
    return 0;
}
