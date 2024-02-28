#include "romanToInt.hpp"

int Solution_romanToInt::romanToInt(std::string s){

    //int resultSum = 0;

    // std::map<std::string, int> hashRomanInt {
    //     {"IV", 4},
    //     {"IX", 9}, 
    //     {"XL", 40},
    //     {"XC", 90},
    //     {"CD", 400},
    //     {"CM", 900},
    //     {"I", 1},
    //     {"V", 5},
    //     {"X", 10},
    //     {"L", 50},
    //     {"C", 100},
    //     {"D", 500},
    //     {"M", 1000},     
    // }; 

    // assert(sl.romanToInt("III") == 3);
    // assert(sl.romanToInt("LVIII") == 58);
    // assert(sl.romanToInt("MCMXCIV") == 1994);    

    // v.1 31mc
    // for(uint8_t i=0; i<s.length(); ++i){
    // 
    //     if (i<s.length()-1)
    //         if (auto it = hashRomanInt.find(s.substr(i,2)); it != hashRomanInt.end()){
    //             resultSum += it->second;
    //             ++i;
    //             continue;
    //         }
    //
    //     resultSum += hashRomanInt[s.substr(i,1)];
    // }

    // v.2
    // int strLen = s.length();
    // char symbCheck1;
    // char symbCheck2;
    // std::string strToConvert;
    // for(uint8_t i=0; i<strLen; ++i){
    // 
    //     symbCheck1 = s[i];
    //     strToConvert.clear();
    //     strToConvert.push_back(symbCheck1);
    //
    //     if ((i<strLen-1) && (symbCheck1 == 'I' || symbCheck1 == 'X' || symbCheck1 == 'C'))
    //     {
    //         char symbCheck2 = s[i+1];
    //         if ((symbCheck1 == 'I' && (symbCheck2 == 'V' || symbCheck2 == 'X')) || 
    //             (symbCheck1 == 'X' && (symbCheck2 == 'L' || symbCheck2 == 'C')) || 
    //             (symbCheck1 == 'C' && (symbCheck2 == 'D' || symbCheck2 == 'M'))){
    //             strToConvert.push_back(symbCheck2);
    //             ++i;
    //         }
    //     }
    // 
    //     resultSum += hashRomanInt[strToConvert];
    // }

    int resultSum = 0;

    std::map< std::pair<char, char>, int> hashRomanInt {
        {{'I','V'}, 4},
        {{'I','X'}, 9}, 
        {{'X','L'}, 40},
        {{'X','C'}, 90},
        {{'C','D'}, 400},
        {{'C','M'}, 900},
        {{'I',0}, 1},
        {{'V',0}, 5},
        {{'X',0}, 10},
        {{'L',0}, 50},
        {{'C',0}, 100},
        {{'D',0}, 500},
        {{'M',0}, 1000}     
    }; 

    int strLen = s.length();
    char symbCheck1;
    char symbCheck2;
    for(uint8_t i=0; i<strLen; ++i){
        
        symbCheck1 = s[i];
        symbCheck2 = 0;

        if ((i<strLen-1) && (symbCheck1 == 'I' || symbCheck1 == 'X' || symbCheck1 == 'C'))
        {
            symbCheck2 = s[i+1];
            if ((symbCheck1 == 'I' && (symbCheck2 == 'V' || symbCheck2 == 'X')) || 
                (symbCheck1 == 'X' && (symbCheck2 == 'L' || symbCheck2 == 'C')) || 
                (symbCheck1 == 'C' && (symbCheck2 == 'D' || symbCheck2 == 'M')))
                ++i;
            else
               symbCheck2 = 0;     
        }

        resultSum += hashRomanInt[std::make_pair(symbCheck1, symbCheck2)];
    }

    return resultSum;
}