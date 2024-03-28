#include <iostream>
#include <cassert>
#include <thread>
#include <vector>

#define UNIT_TESTING

void reversWordsInString(std::string& srcStr);
void reversWord(std::string& srcStr, int64_t lhp, int64_t rhp);
int reversWordsInStringTest();

std::vector<std::thread*> revWordsTread;

int main(){

    #ifdef UNIT_TESTING
        return reversWordsInStringTest();
    #endif

    return 0;
}

int reversWordsInStringTest(){

    std::string srcString;

    srcString = "1234"; reversWordsInString(srcString);
    assert(srcString == "4321");

    srcString = "1234 123 321 45"; reversWordsInString(srcString);
    assert(srcString == "4321 321 123 54");

    srcString = "789 2"; reversWordsInString(srcString);
    assert(srcString == "987 2");

    std::cout << "OK reversWordsInStringTest" << "\n";

    return 0;
}

void reversWordsInString(std::string& srcStr){

    int64_t lsp = 0;
    bool wordFound = true;

    for(int64_t rsp=0; rsp<srcStr.size(); ++rsp){

        char curSymbol = srcStr[rsp];

        if (curSymbol == ' '){
           // revWordsTread.push_back(new std::thread(std::ref(reversWord), srcStr, lsp, rsp-1));
           reversWord(srcStr, lsp, rsp-1);
            wordFound = true;
        }else if (wordFound) {
            lsp=rsp;
            wordFound = false;
        }
    }

    if (!wordFound)
            // revWordsTread.push_back(new std::thread(std::ref(reversWord), srcStr, lsp, srcStr.size()-1));
            reversWord(srcStr, lsp, srcStr.size()-1);

    // for (auto thr : revWordsTread)
    //     thr->join(); 
}

void reversWord(std::string& srcStr, int64_t lhp, int64_t rhp){
    while (lhp<rhp){
        std::swap(srcStr[lhp], srcStr[rhp]);
        ++lhp;
        --rhp;
    }
}