#include <iostream>
#include <cassert>
#include <vector>

void maxFishProfitTest();
int maxFishProfit(int16_t n, int16_t k, const std::vector<int64_t>& prices);
int maxFishProfitV1(int16_t n, int16_t k, const std::vector<int64_t>& prices);

int main(){
    // maxFishProfitTest();

    int16_t n;
    int16_t k;
    int64_t dayPrice;
    std::vector<int64_t> prices;

    std::cin >> n;
    std::cin >> k;

    for(int16_t i=0; i<n; ++i){
        std::cin >> dayPrice;
        prices.push_back(dayPrice);
    }

    std::cout<<maxFishProfit(n, k, prices);

    return 0;
}

void maxFishProfitTest(){
    assert(maxFishProfit(3,1,{1,2,4}) == 2);
    assert(maxFishProfit(5,2,{1,2,3,4,5}) == 2);
    assert(maxFishProfit(5,2,{5,4,3,2,1}) == 0);
    assert(maxFishProfit(6,2,{1,3,2,5,4,6}) == 3);
    assert(maxFishProfit(5,2,{1,0,9,4,3}) == 9);
    assert(maxFishProfit(6,3,{1,8,0,7,3,9}) == 9);

    std::cout<<"OK maxFishProfitTest"<<std::endl;
}

int maxFishProfit(int16_t n, int16_t k, const std::vector<int64_t>& prices){

    int64_t maxProfit = 0;

    for(int16_t i=0; i<n; ++i)
        for(int16_t k_range = i; k_range <= std::min(((int16_t)(i+k)), (int16_t)(n-1)); ++k_range)
            maxProfit = std::max(maxProfit, prices[k_range] - prices[i]);

    return maxProfit;
}

int maxFishProfitV1(int16_t n, int16_t k, const std::vector<int64_t>& prices){

    int64_t maxProfit = 0;

    for(int16_t i=0; i<n; ++i){
        int64_t maxProfitInterval = 0;
        int64_t maxProfitIndexInterval = i;
        for(int16_t k_range = i; k_range <= std::min(((int16_t)(i+k)), (int16_t)(n-1)); ++k_range){
            maxProfitInterval = std::max(maxProfitInterval, prices[k_range] - prices[i]);
            if (maxProfitInterval > maxProfit){
                maxProfit = maxProfitInterval;
                maxProfitIndexInterval = k_range;
            }
        }
        i = maxProfitIndexInterval;
    }

    return maxProfit;
}