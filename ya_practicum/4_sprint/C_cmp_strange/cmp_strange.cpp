#include <iostream>
#include <map>

struct CharDims{
    int lastPos;
    int totalCnt;

    bool operator == (const CharDims& rhs){
        return this->lastPos == rhs.lastPos && this->totalCnt == rhs.totalCnt;
    }

    bool operator != (const CharDims& rhs){
        return this->lastPos != rhs.lastPos || this->totalCnt != rhs.totalCnt;
    }
} ;

bool strCmpStrange(const std::string& str1, const std::string& str2);

int main(){

    std::string str1;
    std::string str2;

    std::getline(std::cin, str1);
    std::getline(std::cin, str2);

    std::cout << (strCmpStrange(str1, str2) ? "YES" : "NO");

    return 0;
}

bool strCmpStrange(const std::string& str1, const std::string& str2){

    if (str1.size() != str2.size())
        return false;

    std::map<char, CharDims> charsStr1;
    std::map<char, CharDims> charsStr2;

    for (int i=0; i<str1.size(); ++i){
        
        int lastPosStr1 = charsStr1[str1[i]].lastPos;
        int lastPosStr2 = charsStr2[str2[i]].lastPos;
        if (lastPosStr1 != lastPosStr2)
            return false;

        charsStr1[str1[i]] = {i, ++charsStr1[str1[i]].totalCnt};
        charsStr2[str2[i]] = {i, ++charsStr2[str2[i]].totalCnt};
        //if (charsStr1[str1[i]] != charsStr2[str2[i]])
        if (charsStr1[str1[i]].totalCnt != charsStr2[str2[i]].totalCnt)
            return false;
    }

    return true;
}