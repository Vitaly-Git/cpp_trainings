#include <iostream>
#include <vector>
#include <algorithm>

int main(){

    int32_t n,k;
    std::cin >> n;
    std::vector<int32_t> figures(n);

    for(int32_t i=0;i<n;++i)
        std::cin >> figures[i];
    std::sort(figures.begin(), figures.end(), [](auto lhs, auto rhs){return lhs < rhs;});

    std::cin >> k;    

    bool found = false;
    int32_t leftSidePointer = 0;
    int32_t rightSidePointer = figures.size()-1;

    while(leftSidePointer<rightSidePointer){

        if (figures[leftSidePointer] + figures[rightSidePointer] > k)
            --rightSidePointer;
        else if (figures[leftSidePointer] + figures[rightSidePointer] < k)
            ++leftSidePointer;
        else{
            std::cout << figures[leftSidePointer] << " " << figures[rightSidePointer];
            found = true;
            break;
        }
    }

    if(!found)
        std::cout << "None";

    return 0;
}