#include <iostream>
#include <vector>

int main(){

    int32_t vecSize;
    std::cin >> vecSize;

    std::vector<int32_t> vec1(vecSize);
    std::vector<int32_t> vec2(vecSize);

    for(int32_t i=0; i<vecSize; ++i)
        std::cin >> vec1[i];

    for(int32_t i=0; i<vecSize; ++i){
        std::cin >> vec2[i];
        std::cout << (i==0?"":" ") << vec1[i] << " " << vec2[i];
    }

    return 0;
}
