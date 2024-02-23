#include <iostream>
#include "var_array.hpp"

void var_array(){

    int arraysCnt = 0;
    int querysCnt = 0;

    std::cout << "input arrays count and queries count (split space): ";
    std::cin >> arraysCnt;
    std::cin >> querysCnt;

    int* arrayPtrs[arraysCnt];
    int arraysElementCnt[arraysCnt];
    int results[querysCnt];

    for (int i=0; i<arraysCnt; ++i){

        std::cout << "input (split by space) values_cnt values: ";
        std::cin >> arraysElementCnt[i];
        arrayPtrs[i] = new int[arraysElementCnt[i]];

        for (int iElemet = 0; iElemet < arraysElementCnt[i]; ++iElemet){
            std::cin >> arrayPtrs[i][iElemet];
        }
    }

    for (int i=0; i<querysCnt; ++i){
        int x;
        int y;
        std::cout << "input coordinates (split space): ";
        std::cin >> x;
        std::cin >> y;
        results[i] = arrayPtrs[x][y];
    }

    for (int i=0; i<querysCnt; ++i){
        std::cout << results[i] << std::endl;
    }
}