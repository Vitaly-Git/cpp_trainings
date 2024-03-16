#include <iostream>
#include <vector>
#include <iterator>
#include <cassert>

std::vector<int32_t> mergeVec(int32_t vecSize, const std::vector<int32_t>& vec1, const std::vector<int32_t>& vec2);
void mergeVecTest();

int main(){

    mergeVecTest();

    // int32_t vecSize;
    // std::cin >> vecSize;

    // std::vector<int32_t> vec1(vecSize);
    // std::vector<int32_t> vec2(vecSize);

    // for(int32_t i=0; i<vecSize; ++i)
    //     std::cin >> vec1[i];

    // for(int32_t i=0; i<vecSize; ++i)
    //     std::cin >> vec2[i];

    // std::vector<int32_t> vecResult = mergeVec(vecSize, vec1, vec2);
    
    // for(auto i=vecResult.begin(); i!=vecResult.end(); ++i){
    //     if(i!=vecResult.begin())
    //         std::cout << " ";
    //     std::cout << *i;    
    // }

    return 0;
}

void mergeVecTest(){

    std::vector<int32_t> vecRes = {1,2,3,4,5,6};
    assert(mergeVec(3, {1,2,3}, {4,5,6}) == vecRes);

    vecRes = {1,1,1,1,1,2,2,2,2,2};
    assert(mergeVec(5, {2,2,2,2,2}, {1,1,1,1,1}) == vecRes);

    vecRes = {1,2};
    assert(mergeVec(1, {1}, {2}) == vecRes);

    vecRes = {1,1,2,3,8,9};
    assert(mergeVec(3, {1,8,9}, {2,3,1}) == vecRes);
}

std::vector<int32_t> mergeVec(int32_t vecSize, const std::vector<int32_t>& vec1, const std::vector<int32_t>& vec2){

    std::vector<int32_t> vecRes;
    vecRes.reserve(vecSize*2);

    int32_t iVec1 = 0;
    int32_t iVec2 = 0;
    while(iVec1<vecSize || iVec2<vecSize){

        if (iVec1>=vecSize){
            vecRes.push_back(vec2[iVec2]);
            ++iVec2;
        }else if(iVec2>=vecSize){
            vecRes.push_back(vec1[iVec1]);
            ++iVec1;
        }else if (vec1[iVec1] < vec2[iVec2]){
            vecRes.push_back(vec1[iVec1]);
            ++iVec1;
        }else{
            vecRes.push_back(vec2[iVec2]);
            iVec2++;
        }
    }

    return vecRes;
}



