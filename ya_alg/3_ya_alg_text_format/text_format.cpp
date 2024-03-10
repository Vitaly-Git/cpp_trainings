#include <iostream>
#include <cassert>
#include <map>
#include <cstdarg>
#include <cmath>
#include <vector>

void textFormatTest();
int64_t textFormat(int64_t strCount, const std::vector<int64_t>& charsInStrings);
int64_t textFormatV1(int64_t strCount, ...);
int64_t buttonsToString(const int64_t strLen);
void initButtonsMap();

namespace commonVars
{
    std::map<int8_t, int8_t> buttonsMap; // количество символов, сколько кнопок надо нажать
    int8_t buttonsMapSize;
}

int main(){
    
    // textFormatTest();

    int64_t stringsCount;
    std::vector<int64_t> charsCountInStrings;

    std::cin >> stringsCount;
    
    int64_t charsInStr;
    for(int64_t i=0;i<stringsCount;i++){
        std::cin>>charsInStr;    
        charsCountInStrings.push_back(charsInStr);
    }

    std::cout << textFormat(stringsCount, charsCountInStrings);

    return 0;
}

void textFormatTest(){
    assert(textFormat(5,{1,4,12,9,0}) == 8);
    assert(textFormat(1,{1}) == 1);
    assert(textFormat(1,{2}) == 2);
    assert(textFormat(1,{3}) == 2);
    assert(textFormat(1,{4}) == 1);
    assert(textFormat(1,{5}) == 2);
    assert(textFormat(1,{6}) == 3);
    assert(textFormat(1,{7}) == 3);
    assert(textFormat(1,{8}) == 2);
    assert(textFormat(1,{9}) == 3);
    assert(textFormat(1,{10}) == 4);
    assert(textFormat(1,{11}) == 4);
    assert(textFormat(1,{12}) == 3);
    assert(textFormat(2,{0,40}) == 10);
    assert(textFormat(2,{0,43}) == 12);

    assert(textFormatV1(5,1,4,12,9,0) == 8);
    assert(textFormatV1(1,1) == 1);
    assert(textFormatV1(1,2) == 2);
    assert(textFormatV1(1,3) == 2);
    assert(textFormatV1(1,4) == 1);
    assert(textFormatV1(1,5) == 2);
    assert(textFormatV1(1,6) == 3);
    assert(textFormatV1(1,7) == 3);
    assert(textFormatV1(1,8) == 2);
    assert(textFormatV1(1,9) == 3);
    assert(textFormatV1(1,10) == 4);
    assert(textFormatV1(1,11) == 4);
    assert(textFormatV1(1,12) == 3);
    assert(textFormatV1(2,0,40) == 10);
    assert(textFormatV1(2,0,43) == 12);

    std::cout << "OK textFormatTest" << std::endl;
}

int64_t textFormat(int64_t strCount, const std::vector<int64_t>& charsInStrings){
    int64_t buttonsCount = 0;

    initButtonsMap(); 

    while (strCount--){
        buttonsCount += buttonsToString(charsInStrings[strCount]);
    }

    return buttonsCount;    
}

int64_t textFormatV1(int64_t strCount, ...){

    int64_t buttonsCount = 0;

    initButtonsMap(); 

    va_list argList;
    va_start(argList, strCount);
    while (strCount--){
        buttonsCount += buttonsToString(va_arg(argList,int64_t));
    }
    va_end(argList);

    return buttonsCount;
}

void initButtonsMap(){
    commonVars::buttonsMap[1] = 1; // space
    commonVars::buttonsMap[2] = 2; // space + space
    commonVars::buttonsMap[3] = 2; // tab + backspace
    commonVars::buttonsMap[4] = 1; // tab

    commonVars::buttonsMapSize = commonVars::buttonsMap.size();
}

int64_t buttonsToString(const int64_t strLen){

    int64_t buttonsInStr = 0;
    int64_t totalChars = strLen;
    int64_t buttonsMapSizeToAnalize;

    while(totalChars > 0){
        buttonsMapSizeToAnalize = std::min((int64_t)commonVars::buttonsMapSize, totalChars);
        int64_t charsToPrint = buttonsMapSizeToAnalize;

        buttonsInStr = buttonsInStr + (totalChars / charsToPrint) * commonVars::buttonsMap[charsToPrint];
        totalChars = totalChars % charsToPrint;
    }

    return buttonsInStr;
}