#include <iostream>
#include <algorithm>
#include <vector>

struct Heap{
    std::int64_t m;
    std::int64_t c;
};

int main(){

    std::int64_t m;
    std::int64_t n;
    std::cin >> m >> n;

    std::vector<Heap> heaps(n);
    for(std::int64_t i=0; i<n; ++i)
        std::cin >> heaps[i].c >> heaps[i].m;

    std::sort(heaps.begin(), heaps.end(), [](Heap& lhs, Heap& rhs){
        if (lhs.c != rhs.c)
            return lhs.c > rhs.c;
        else
            return lhs.m > rhs.m;
    });

    std::int64_t totalCost = 0;    
    std::int64_t totalWeight = 0;    

    for(std::int64_t i=0; i<n; ++i){
        
        if (totalWeight >= m)
            break;

        std::int64_t weightToRukFree = m - totalWeight;
        std::int64_t curHeapPrice = heaps[i].c;
        std::int64_t curHeapWeight = heaps[i].m;

        std::int64_t addWeigtToRuk = std::min(weightToRukFree, curHeapWeight);

        totalCost += addWeigtToRuk*curHeapPrice;
        totalWeight += addWeigtToRuk;
    }

    std::cout << totalCost << '\n';

    return 0;
}