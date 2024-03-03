#include <iostream>
#include <array>
#include <bitset>
#include <vector>
#include <cassert>
#include <tuple>
#include <iterator>
#include <algorithm>

void chessTest();
int chess(std::vector<std::string> chessBoard);
void addMaskToResultBits(char signChar, char rowIdx, char colIdx, std::array<std::bitset<8>,8>& resultBits);
void addMaskToResultBitsR(char rowIdx, char colIdx, std::array<std::bitset<8>,8>& resultBits);
void addMaskToResultBitsB(char rowIdx, char colIdx, std::array<std::bitset<8>,8>& resultBits);

int main(){
    chessTest();
    return 0;
}

void chessTest(){
    
    assert(chess({
        "********",
        "********",
        "*R******",
        "********",
        "********",
        "********",
        "********",
        "********"}) == 49);

    assert(chess({
        "********",
        "********",
        "******B*",
        "********",
        "********",
        "********",
        "********",
        "********"}) == 54);

    assert(chess({
        "********",
        "********",
        "********",
        "*****B**",
        "********",
        "********",
        "********",
        "********"}) == 40);
}

int chess(std::vector<std::string> chessBoard){
    int freeCellCount = 0;

    std::array<std::bitset<8>,8> resultBits = {255,255,255,255,255,255,255,255};
    std::vector<std::tuple<char, int8_t, int8_t>> figCoords;

    for(int8_t rowIdx=0; rowIdx<8; ++rowIdx)
        for (int8_t colIdx=0; colIdx<8; ++colIdx)
            if (chessBoard[rowIdx][colIdx] != '*')
                figCoords.push_back(std::make_tuple(chessBoard[rowIdx][colIdx], rowIdx, colIdx));

    for(auto it=figCoords.begin(); it!=figCoords.end();++it)
        addMaskToResultBits(std::get<0>(*it),std::get<1>(*it),std::get<2>(*it),resultBits);

    std::for_each(resultBits.begin(), resultBits.end(), 
        [&freeCellCount](const std::bitset<8>& byteToCheck){freeCellCount += byteToCheck.count();});

    return freeCellCount;
}

void addMaskToResultBits(char signChar, char rowIdx, char colIdx, std::array<std::bitset<8>,8>& resultBits){
    if (signChar == 'R')
        addMaskToResultBitsR(rowIdx, colIdx, resultBits);
    else if (signChar == 'B')
        addMaskToResultBitsB(rowIdx, colIdx, resultBits);
}

void addMaskToResultBitsR(char rowIdx, char colIdx, std::array<std::bitset<8>,8>& resultBits){
    resultBits[rowIdx] &= 0b00000000;
    for(int8_t rowI=0; rowI<8; rowI++)
        resultBits[rowI].reset(colIdx);
}

void addMaskToResultBitsB(char rowIdx, char colIdx, std::array<std::bitset<8>,8>& resultBits){

}