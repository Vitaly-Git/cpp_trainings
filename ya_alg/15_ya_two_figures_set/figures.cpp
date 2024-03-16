#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

int main(){

    int32_t n,k;
    std::cin >> n;
    std::vector<int32_t> figures(n);

    for(int32_t i=0;i<n;++i)
        std::cin >> figures[i];
    //std::sort(figures.begin(), figures.end(), [](auto lhs, auto rhs){return lhs < rhs;});

    std::cin >> k;    

    std::set<int32_t> setFigures;

    bool found = false;

    for(int32_t i=0; i<n; ++i){

        int32_t findingFig = k-figures[i];

        if (setFigures.find(findingFig)==setFigures.end()){
            setFigures.insert(figures[i]);
        }else{
            std::cout << findingFig << " " << figures[i];
            found = true;
            break;
        }
    }

    if(!found)
        std::cout << "None";

    return 0;
}