#include <iostream>
#include <vector>
#include <algorithm>

void reversVector(std::vector<int64_t>& vecSrc);
void coutVector(const std::vector<int64_t>& vecSrc);

int main(){

    std::vector<int64_t> vecSrc;

    vecSrc = {};
    coutVector(vecSrc);
    reversVector(vecSrc);
    coutVector(vecSrc);

    vecSrc = {1};
    coutVector(vecSrc);
    reversVector(vecSrc);
    coutVector(vecSrc);

    vecSrc = {1,2};
    coutVector(vecSrc);
    reversVector(vecSrc);
    coutVector(vecSrc);

    vecSrc = {1,2,3};
    coutVector(vecSrc);
    reversVector(vecSrc);
    coutVector(vecSrc);

    std::reverse(vecSrc.begin(), vecSrc.end());
    coutVector(vecSrc);

    return 0;
}

void reversVector(std::vector<int64_t>& vecSrc){

    int64_t lhp = 0;
    int64_t rhp = (int64_t)vecSrc.size() - 1;

    while(lhp<rhp){
        std::swap(vecSrc[lhp], vecSrc[rhp]);
        ++lhp;
        --rhp;
    }
}

void coutVector(const std::vector<int64_t>& vecSrc){
    std::cout<<"[";
    std::for_each(vecSrc.begin(), vecSrc.end(), [](auto value){std::cout<<value<<"";});
    std::cout<<"]";
    std::cout<<std::endl;
}