#include <iostream>
#include <vector>
#include <cassert>

//#define UNIT_TESTING

typedef std::vector<std::vector<int16_t>> int16_matrix;

void matrixTrans(const int16_matrix& srcMatrix, int16_matrix& dstMatrix);
int  matrixTransTest();

int main(){

    #ifdef UNIT_TESTING
        return matrixTransTest();
    #endif

    int16_t n=0;
    int16_t m=0;

    std::cin >> n >> m;

    if (n==0 || m==0)
        return 0;

    int16_matrix srcMatrix(n);
    for (int16_t iRow=0; iRow<n; ++iRow)
        srcMatrix[iRow].resize(m);

    for (int16_t iRow=0; iRow<n; ++iRow)
        for (int16_t iCol=0; iCol<m; ++iCol)
            std::cin >> srcMatrix[iRow][iCol];

    int16_matrix dstMatrix;
    matrixTrans(srcMatrix, dstMatrix);

    for(int16_t iRow=0; iRow<m; ++iRow){
        for(int16_t iCol=0; iCol<n; ++iCol){
            if (iCol>0){
                std::cout << " ";
            }
            std::cout << dstMatrix[iRow][iCol];
        };
        std::cout << "\n";
    };

    return 0;
}

int matrixTransTest(){
    
    int16_matrix srcMatrix;
    int16_matrix dstMatrix;
    int16_matrix dstMatrixPlan;

    srcMatrix = {
        {1,2,3},
        {0,2,6},
        {7,4,1},
        {2,7,0}
    };
    dstMatrixPlan = {
        {1,0,7,2},
        {2,2,4,7},
        {3,6,1,0}
    };
    matrixTrans(srcMatrix, dstMatrix);
    assert(dstMatrix == dstMatrixPlan);

    std::cout << "OK matrixTransTest" << "\n";

    return 0;
}

void matrixTrans(const int16_matrix& srcMatrix, int16_matrix& dstMatrix){

    dstMatrix.clear();

    dstMatrix.resize(srcMatrix[0].size());
    for (int16_t rowIdx=0; rowIdx<srcMatrix[0].size(); ++rowIdx)
        dstMatrix[rowIdx].resize(srcMatrix.size());

    for (int16_t colIdx=0; colIdx<srcMatrix.size(); ++colIdx)
        for (int16_t rowIdx=0; rowIdx<srcMatrix[0].size(); ++rowIdx)
            dstMatrix[rowIdx][colIdx] = srcMatrix[colIdx][rowIdx];

}
