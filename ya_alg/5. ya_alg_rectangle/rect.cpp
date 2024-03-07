#include <iostream>
#include <limits>
#include <cmath>

int main(){

    int64_t k;
    int64_t resXMin = std::numeric_limits<int64_t>::max();
    int64_t resYMin = std::numeric_limits<int64_t>::max();
    int64_t resXMax = std::numeric_limits<int64_t>::min();
    int64_t resYMax = std::numeric_limits<int64_t>::min();
    int64_t x,y;

    std::cin >> k;

    for(char i=0;i<k;++i){
        std::cin>>x;
        std::cin>>y;
        resXMin = std::min(resXMin, x);
        resYMin = std::min(resYMin, y);
        resXMax = std::max(resXMax, x);
        resYMax = std::max(resYMax, y);
    }

    std::cout<<resXMin<<" "<<resYMin<<" "<<resXMax<<" "<<resYMax;

    return 0;
}