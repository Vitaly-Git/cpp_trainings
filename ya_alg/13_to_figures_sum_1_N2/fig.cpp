#include <iostream>
#include <vector>
#include <algorithm>

int main(){

    int32_t n,k;
    std::cin >> n;
    std::vector<int32_t> figures(n);

    for(int32_t i=0;i<n;++i)
        std::cin >> figures[i];

    std::cin >> k;    

    std::sort(figures.begin(), figures.end(), [](auto lhs, auto rhs){return lhs < rhs;});

    bool found = false;

    for(int i=0; i<n; ++i)
        for(int32_t j=i+1; j<n; ++j)
            if (figures[i] + figures[j] == k){
                std::cout << figures[i] << " " << figures[j];
                i=n; 
                j=n;
                found = true;
                break;
            }

    if(!found)
        std::cout << "None";

    return 0;
}