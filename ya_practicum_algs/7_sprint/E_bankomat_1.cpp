#include <iostream>
#include <vector>
#include <algorithm>

int main(){

    std::int64_t x, k;
    std::cin >> x >> k;

    std::vector<std::int64_t> nominals(k);
    for(std::int64_t i=0; i<k; ++i)
        std::cin >> nominals[i];

    std::sort(nominals.begin(), nominals.end(), [](std::int64_t lhs, std::int64_t rhs){return lhs > rhs;});

    std::int64_t totalGotMoney = 0;
    std::int64_t minCupurs = 0;
    std::int64_t moneyToGet = x;
    for(std::int64_t i=0; i<k; ++i){

        std::int64_t curNominal = nominals[i];
        std::int64_t coupursCount = 0;
        std::int64_t remaindToGet = 0;
        std::int64_t gotMoney = 0;

        coupursCount = moneyToGet / curNominal;
        if (coupursCount == 0)
            continue;

        remaindToGet = moneyToGet % curNominal;
        gotMoney = coupursCount*curNominal;
        
        moneyToGet -= gotMoney;
        totalGotMoney += gotMoney;

        minCupurs += coupursCount;

        if (remaindToGet == 0)
            break;

        if (totalGotMoney >= x)
            break;
    }

    if (totalGotMoney == x)
        std::cout << minCupurs;
    else    
        std::cout << -1;

    return 0;
}