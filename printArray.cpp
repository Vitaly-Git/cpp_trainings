#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include "printArray.hpp"

void printArray(){

    int arraySize = 0;

    std::cout << "input array size: ";
    std::cin >> arraySize;
    int array[arraySize];

    std::cout << "input array elements separate by space: ";
    for (int i=0; i<arraySize; ++i)
        std::cin >> array[i];

    for (int i=arraySize-1; i>=0; --i){
        std::cout << array[i]; 
        if (i>0)
            std::cout << " ";
    }
}

void printNumbersAsText(){
    
    std::string numSrtA;
    std::string numSrtB;
    int numA = 0;
    int numB = 0;

    std::cin >> numSrtA;
    std::cin >> numSrtB;

    numA = std::stoi(numSrtA);
    numB = std::stoi(numSrtB);

    for(int i=numA; i <= numB; i++)
        std::cout << int2text(i) << std::endl;

}

std::string int2text(int num){

    std::string retStr = "";

    switch (num){
        case 0:
            retStr = "zero";
            break;
        case 1:
            retStr = "one";
            break;
        case 2:
            retStr = "two";
            break;
        case 3:
            retStr = "three";
            break;
        case 4:
            retStr = "four";
            break;
        case 5:
            retStr = "five";
            break;
        case 6:
            retStr = "six";
            break;
        case 7:
            retStr = "seven";
            break;
        case 8:
            retStr = "eight";
            break;
        case 9:
            retStr = "nine";
            break;
        default:
            retStr = num%2 == 0 ? "even" : "odd";
            break;
    }

    return retStr;
}