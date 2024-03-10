#include <iostream>
#include <array>
#include <bitset>
#include <cassert>
#include <tuple>
#include <iterator>
#include <algorithm>
#include <map>
#include <vector>

void chessTest();
int chess(std::vector<std::string> chessBoard);
// int chessV1(std::vector<std::string> chessBoard);
void addMaskToResultBits(char signChar, char rowIdx, char colIdx, 
    std::array<std::bitset<8>,8>& resultBits, const std::map<std::pair<int8_t, int8_t>, char>& figPlaces);
void addMaskToResultBitsR(char rowIdx, char colIdx, 
    std::array<std::bitset<8>,8>& resultBits, const std::map<std::pair<int8_t, int8_t>, char>& figPlaces);
void addMaskToResultBitsB(char rowIdx, char colIdx, 
    std::array<std::bitset<8>,8>& resultBits, const std::map<std::pair<int8_t, int8_t>, char>& figPlaces);
void resetBitWithPlaceCheck(char rowIdx, char colIdx, std::array<std::bitset<8>,8>& resultBits, 
    const std::map<std::pair<int8_t, int8_t>, char>& figPlaces, 
    bool &figFound);

int main(){
    // chessTest();

    std::string chessLine;
    std::vector<std::string> chessBoard;

    for(char i=0;i<8;++i){
        std::cin >> chessLine;
        chessBoard.push_back(chessLine); 
    }

    std::cout << chess(chessBoard);

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
        "*R****B*",
        "********",
        "********",
        "********",
        "********",
        "********"}) == 42);

    assert(chess({
        "********",
        "*R******",
        "********",
        "*****B**",
        "********",
        "********",
        "********",
        "********"}) == 40);

    assert(chess({
        "********",
        "********",
        "***R****",
        "********",
        "********",
        "********",
        "********",
        "********"}) == 49);

    assert(chess({
        "********",
        "***B****",
        "**BRB***",
        "***B****",
        "********",
        "********",
        "********",
        "********"}) == 41);

        std::cout << "OK chessTest";
}

int chess(std::vector<std::string> chessBoard){
    int freeCellCount = 0;

    std::array<std::bitset<8>,8> resultBits = {255,255,255,255,255,255,255,255};
    std::map<std::pair<int8_t, int8_t>, char> figPlaces;

    for(int8_t rowIdx=0; rowIdx<8; ++rowIdx)
        for (int8_t colIdx=0; colIdx<8; ++colIdx)
            if (chessBoard[rowIdx][colIdx] != '*')
                figPlaces[{rowIdx,colIdx}] = chessBoard[rowIdx][colIdx];

    for(auto it=figPlaces.begin(); it!=figPlaces.end();++it)
        addMaskToResultBits(it->second, it->first.first, it->first.second, resultBits, figPlaces);

    std::for_each(resultBits.begin(), resultBits.end(), 
        [&freeCellCount](const std::bitset<8>& byteToCheck){freeCellCount += byteToCheck.count();});

    return freeCellCount;
}

// int chessV1(std::vector<std::string> chessBoard){
//     int freeCellCount = 0;

//     std::array<std::bitset<8>,8> resultBits = {255,255,255,255,255,255,255,255};
//     std::vector<std::tuple<char, int8_t, int8_t>> figCoords;

//     for(int8_t rowIdx=0; rowIdx<8; ++rowIdx)
//         for (int8_t colIdx=0; colIdx<8; ++colIdx)
//             if (chessBoard[rowIdx][colIdx] != '*'){
//                 figCoords.push_back(std::make_tuple(chessBoard[rowIdx][colIdx], rowIdx, colIdx));
//                 }

//     for(auto it=figCoords.begin(); it!=figCoords.end();++it)
//         addMaskToResultBits(std::get<0>(*it),std::get<1>(*it),std::get<2>(*it),resultBits);

//     std::for_each(resultBits.begin(), resultBits.end(), 
//         [&freeCellCount](const std::bitset<8>& byteToCheck){freeCellCount += byteToCheck.count();});

//     return freeCellCount;
// }

void addMaskToResultBits(char signChar, char rowIdx, char colIdx, 
    std::array<std::bitset<8>,8>& resultBits, const std::map<std::pair<int8_t, int8_t>, char>& figPlaces){
    if (signChar == 'R')
        addMaskToResultBitsR(rowIdx, colIdx, resultBits, figPlaces);
    else if (signChar == 'B')
        addMaskToResultBitsB(rowIdx, colIdx, resultBits, figPlaces);
}

void addMaskToResultBitsR(char rowIdx, char colIdx, 
    std::array<std::bitset<8>,8>& resultBits, const std::map<std::pair<int8_t, int8_t>, char>& figPlaces){

    // resultBits[rowIdx] &= 0b00000000;
    // for(int8_t rowI=0; rowI<8; ++rowI)
    //     resultBits[rowI].reset(colIdx);

    resultBits[rowIdx].reset(colIdx);

    bool vector1Done = false;
    bool vector2Done = false;
    bool vector3Done = false;
    bool vector4Done = false;

    for (char i=1;i<8;++i){
        if (!vector1Done && rowIdx+i<8)
            resetBitWithPlaceCheck(rowIdx+i, colIdx, resultBits, figPlaces, vector1Done);
        if (!vector2Done && rowIdx-i>=0)
            resetBitWithPlaceCheck(rowIdx-i, colIdx, resultBits, figPlaces, vector2Done);
        if (!vector3Done && colIdx-i>=0)
            resetBitWithPlaceCheck(rowIdx, colIdx-i, resultBits, figPlaces, vector3Done);
        if (!vector4Done && colIdx+i<8)
            resetBitWithPlaceCheck(rowIdx, colIdx+i, resultBits, figPlaces, vector4Done);
    }
}

void addMaskToResultBitsB(char rowIdx, char colIdx, 
    std::array<std::bitset<8>,8>& resultBits, const std::map<std::pair<int8_t, int8_t>, char>& figPlaces){

    resultBits[rowIdx].reset(colIdx);

    bool vector1Done = false;
    bool vector2Done = false;
    bool vector3Done = false;
    bool vector4Done = false;

    for (char i=1;i<8;++i){
        if (!vector1Done && rowIdx+i<8 && colIdx+i<8)
            resetBitWithPlaceCheck(rowIdx+i, colIdx+i, resultBits, figPlaces, vector1Done);
        if (!vector2Done && rowIdx-i>=0 && colIdx-i>=0)
            resetBitWithPlaceCheck(rowIdx-i, colIdx-i, resultBits, figPlaces, vector2Done);
        if (!vector3Done && rowIdx+i<8 && colIdx-i>=0)
            resetBitWithPlaceCheck(rowIdx+i, colIdx-i, resultBits, figPlaces, vector3Done);
        if (!vector4Done && rowIdx-i>=0 && colIdx+i<8)
            resetBitWithPlaceCheck(rowIdx-i, colIdx+i, resultBits, figPlaces, vector4Done);
    }
}

void resetBitWithPlaceCheck(char rowIdx, char colIdx, 
    std::array<std::bitset<8>,8>& resultBits, const std::map<std::pair<int8_t, int8_t>, char>& figPlaces, 
    bool &figFound){

    if (figPlaces.find({rowIdx, colIdx}) ==  figPlaces.end())
        resultBits[rowIdx].reset(colIdx);
    else     
        figFound = true;
}