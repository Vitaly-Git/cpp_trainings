#include <iostream>
#include <string>
#include <vector>

std::string revers_words(std::string srcStr);
void revers_letters_in_word(std::string &word);

struct wordsParam{
    int startPos;
    int endPos;
};

typedef std::vector<wordsParam> wordsParamVec;

int main(){

    std::string srcStr;
    std::getline(std::cin, srcStr);

    auto dstStr = revers_words(srcStr);

    std::cout << srcStr << std::endl;
    std::cout << dstStr << std::endl;

    return 0;
}

std::string revers_words(std::string srcStr){

    std::string dstStr;
    wordsParamVec wordsVec;

    int wordStartPos = 0;
    int wordEndPos = wordStartPos;
    for (int pos=0; pos<srcStr.size(); pos++){
        if (srcStr[pos] == ' '){
            wordEndPos = pos-1;
            wordsParam word;
            word.startPos = wordStartPos;
            word.endPos = wordEndPos;
            wordsVec.push_back(word);
            wordStartPos = wordEndPos+1+1;
            wordEndPos = wordStartPos;
        } else {
            ++wordEndPos;
        }
    }

    if  (wordStartPos != wordEndPos){
            wordsParam word;
            word.startPos = wordStartPos;
            word.endPos = wordEndPos;
            wordsVec.push_back(word);
    }

    for (int i=wordsVec.size()-1; i>=0; --i){
        if (dstStr.size() != 0){
            dstStr = dstStr + ' ';
        }
        std::string word = srcStr.substr(wordsVec[i].startPos, wordsVec[i].endPos-wordsVec[i].startPos+1);
        revers_letters_in_word(word);
        dstStr = dstStr + word;
    }

    return dstStr;
}

void revers_letters_in_word(std::string &word){
    for (int i=0; i<word.size()%2; ++i){
        std::swap(word[i], word[word.size()-i-1]);
    }
}