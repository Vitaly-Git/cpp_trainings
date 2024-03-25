#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>

int main(){

    int16_t n;
    std::cin >> n;

    std::unordered_map<int16_t, int16_t> vuzCount;

    int16_t vuzNum;
    for(int16_t i=0; i<n; ++i){
        std::cin >> vuzNum;
        ++vuzCount[vuzNum];
    }

    int16_t k;
    std::cin >> k;

    std::vector<std::pair<int16_t,int16_t>> sortVector(vuzCount.begin(), vuzCount.end());
    
    std::sort(sortVector.begin(), sortVector.end(), [](const auto& lhv, const auto& rhv){
        if (lhv.second == rhv.second)
            return lhv.first < rhv.first;
        else     
            return lhv.second > rhv.second;
    });

    for (int16_t i=0; i<sortVector.size() && i < k; ++i)
        std::cout << sortVector[i].first << " ";

    return 0;
}