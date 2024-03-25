#include <iostream>
#include <vector>

int binarySearchFirstIdx(int32_t searchValue, const std::vector<int32_t>&data, int32_t leftBound, int32_t rightBound);

int main(){
    
    int32_t n;
    std::cin >> n;

    std::vector<int32_t> data(n);
    for(int32_t i=0;i<n;++i)
        std::cin >> data[i];

    int32_t k;
    std::cin >> k;

    int32_t valIdx = binarySearchFirstIdx(k, data, 0, data.size());
    std::cout << (valIdx == -1 ? valIdx : ++valIdx) << " ";

    valIdx = binarySearchFirstIdx(k*2, data, 0, data.size());
    std::cout << (valIdx == -1 ? valIdx : ++valIdx) << " ";

    return 0;
}

int binarySearchFirstIdx(int32_t searchValue, const std::vector<int32_t>&data, int32_t leftBound, int32_t rightBound){

    if (leftBound >= rightBound)
        return -1;

    int32_t middle = (leftBound + rightBound) / 2;
    int32_t centerValue = data[middle];

    if (searchValue <= centerValue){
        int32_t result = binarySearchFirstIdx(searchValue, data, leftBound, middle);
        if (result == -1)
            return middle;
        else    
            return result;    
    }else{
        return binarySearchFirstIdx(searchValue, data, middle+1, rightBound);
    }    
}