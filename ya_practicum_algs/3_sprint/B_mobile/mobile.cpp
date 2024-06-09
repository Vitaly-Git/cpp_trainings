#include <iostream>
//#include <vector>
#include <map>

void printNumCombination(std::string resulString, std::string& telNum, int16_t currentbuttonIndex, 
    const std::map<char,std::string>& buttonSyms);

int main(){

    std::string telNum;
    std::getline(std::cin, telNum);

    // std::vector<std::vector<std::string>> symsButtons = {
    //     {""},
    //     {""},
    //     {"abc"},
    //     {"def"},
    //     {"ghi"},
    //     {"jkl"},
    //     {"mno"},
    //     {"pqrs"},
    //     {"tuv"},
    //     {"wxyz"}
    // };

    std::map<char,std::string> buttonSyms{
        {'2',"abc"},
        {'3',"def"},
        {'4',"ghi"},
        {'5',"jkl"},
        {'6',"mno"},
        {'7',"pqrs"},
        {'8',"tuv"},
        {'9',"wxyz"}    
    };

    int16_t currentbuttonIndex = 0;
    std::string resulString;
    printNumCombination(resulString, telNum, currentbuttonIndex, buttonSyms);

    return 0;
}

void printNumCombination(std::string resulString, std::string& telNum, int16_t currentbuttonIndex, 
    const std::map<char,std::string>& buttonSyms){

        if (currentbuttonIndex > telNum.size()-1){
            resulString = resulString + " ";
            std::cout << resulString;
            return;
        }

        char currentButton = telNum[currentbuttonIndex];

        for(char butSym : buttonSyms.at(currentButton)){
            std::string resulStringPrev = resulString;
            resulString = resulString + butSym;
            printNumCombination(resulString, telNum, currentbuttonIndex+1, buttonSyms);
            resulString = resulStringPrev;
        }
    }