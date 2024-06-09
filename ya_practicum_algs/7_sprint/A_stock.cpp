#include <iostream>
#include <vector>

int main(){

    std::int16_t n;
    std::cin >> n;

    std::vector<std::int16_t> prices(n);
    for(std::int16_t i=0; i<n; ++i)
        std::cin >> prices[i];

    std::int32_t maxProfit = 0;
    std::int32_t curPrice = 0;
    std::int32_t nextPrice = 0;

    for(std::int16_t i=0; i<n-1; ++i){
        curPrice = prices[i];
        nextPrice = prices[i+1];

        if (nextPrice > curPrice)
            maxProfit += nextPrice - curPrice;
    }

    std::cout << maxProfit;

    return 0;
}
