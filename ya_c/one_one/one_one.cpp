#include <iostream>
#include <vector>
#include <cassert>

int64_t onesCount(const std::vector<int64_t>& binData);
void onesCountTest();

int main(){

    //onesCountTest();

    int64_t n=0;
    std::cin >> n;
    
    std::vector<int64_t> binData(n);
    for(int64_t i=0;i<n;++i)
        std::cin >> binData[i];

    std::cout << onesCount(binData);

    return 0;
}

void onesCountTest(){
    assert(onesCount({1,0,1,1,1,0}) == 3);
    assert(onesCount({1,1,1}) == 3);
    assert(onesCount({0}) == 0);
    assert(onesCount({}) == 0);
    assert(onesCount({1}) == 1);
    assert(onesCount({1,0,1,1}) == 2);
    assert(onesCount({1,1,0,1}) == 2);
    assert(onesCount({1,0,1,0,1}) == 1);

    std::cout << "OK onesCountTest" << std::endl;
}

int64_t onesCount(const std::vector<int64_t>& binData){

    int64_t onesCount = 0;
    int64_t lastSeqLen=0;

    for(int64_t i=0; i<binData.size(); ++i){
        int64_t curValue = binData[i];

        if (curValue == 1)
            ++lastSeqLen;
        else
            lastSeqLen = 0;    

        onesCount = std::max(onesCount, lastSeqLen);
    }

    return onesCount;
}