#include <iostream>
#include <vector>
#include <algorithm>

int main(){

    int32_t n,k;
    std::cin >> n >> k;

    std::vector<int32_t> prices(n);
    for(int32_t i=0; i<n; ++i)
        std::cin >> prices[i];

    std::sort(prices.begin(), prices.end());

    int32_t maxHouseCount = 0;

    for(int32_t price : prices)
        if (price > k){
            break;
        }else{
            k -= price;
            ++maxHouseCount;
        }

    std::cout << maxHouseCount;

    return 0;
}