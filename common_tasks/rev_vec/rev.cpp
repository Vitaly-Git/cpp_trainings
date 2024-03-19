#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

int main(){

    std::vector<std::int64_t> srcData = {1,2,3,4,5,6};

    int64_t lhp = 0;
    int64_t rhp = srcData.size()-1;

    while(lhp < rhp){
        if(srcData[lhp]<srcData[rhp])
            std::swap(srcData[lhp], srcData[rhp]);
        ++lhp;
        --rhp;
    }
    
    std::sort(srcData.begin(), srcData.end(),[](auto lhs, auto rhs){return lhs < rhs;});

    std::reverse(srcData.begin(), srcData.end());

    return 0;
}