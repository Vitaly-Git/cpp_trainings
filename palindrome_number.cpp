#include <iostream>
#include "vector"
#include "palindrome_number.hpp"

bool SolutioniIsPalindrome::isPalindrome(int x){

    // 121
    // 1. Определяем порядок
    // 2. Делим контрольное число на максимальный порядок 
    // 3. Запоминаем результат в результурющий вектор
    // 4. Запоминаем остаток как контрольное число
    // 5. Уменьшаем максимальный порядок в 10 раз
    // 6. повторям цикл пока максимальный порядок больше 10

    // v.1
    // std::vector<int> resNumVector;

    // if (x<0 || x==10)
    //     return false;
    
    // uint64_t expNum = 1;    
    // while(expNum<x)
    //     expNum *= 10;
    // expNum /= 10;

    // for(uint64_t exp = expNum; exp > 1; exp /= 10){
    //     int lhsNum = x / exp;
    //     x = x - lhsNum*exp;
    //     resNumVector.push_back(lhsNum);
    // }
    // resNumVector.push_back(x);

    // int resVectSize = resNumVector.size();
    // for(int i=0; i<resVectSize/2; i++)
    //     if (resNumVector[i] != resNumVector[resVectSize-i-1])
    //         return false;

    // v.2
    int resNum = 0;

    if (x<0 || x==10)
        return false;
    else if (x>=0 && x<10)
        return true;
    
    uint64_t expNum = 1;
    int numLen = 0;    
    while(expNum<x){
        expNum *= 10;
        ++numLen;
    }
    expNum /= 10;

    int numCenter = numLen%2 == 0 ?  numLen/2 : (numLen/2 + 1);
    int symPos = 0;
    for(uint64_t exp = expNum; exp > 1; exp /= 10){
        int curNum = x / exp;
        x = x - curNum*exp;
        
        ++symPos;
        if ((symPos==numCenter) && (numLen%2 == 1))
            continue;
        else if (symPos > numCenter)
            resNum = resNum - (curNum*(symPos-numCenter+numLen%2));
        else    
            resNum = resNum + (curNum*(numCenter-symPos+1));
    }
    resNum = resNum - (x*((symPos+1)-numCenter+numLen%2));

    return (resNum==0);
};