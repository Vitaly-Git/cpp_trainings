#include <iostream>
#include <vector>

int main(){

    int32_t n;
    std::cin >> n;

    std::vector<int32_t> numsCnt(3);

    int32_t inputNumber;
    for(int32_t i=0; i<n; ++i){
        std::cin >> inputNumber;
        ++numsCnt[inputNumber];
    }

    for(int32_t i=0; i<numsCnt.size(); ++i)
        for(int32_t numCnt=0; numCnt < numsCnt[i]; ++numCnt)
            std::cout << i << " ";

    return 0;
}