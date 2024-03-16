#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

template <typename T>
void contCout(T cont){
    for_each(cont.begin(), cont.end(), [](const auto& i){
        // if(i!=cont.begin())
        //     std::cout<<" ";
        std::cout<< i << " ";
        });
}

int main(){

    int64_t vecSize = 0;
    std::cin >> vecSize;

    std::vector<int64_t> vecTest(vecSize);

    for(int64_t i=0; i<vecSize; ++i)
        std::cin >> vecTest[i];

    for(auto it = vecTest.begin(); it != vecTest.end(); ++it){
        if(it!=vecTest.begin())
            std::cout << " ";
            std::cout << *it;
    }

    std::cout << "\n";

    std::sort(vecTest.begin(), vecTest.end(), [](int64_t lhs, int64_t rhs){return lhs < rhs;});
    contCout(vecTest);

    std::cout << "\n";

    std::sort(vecTest.begin(), vecTest.end(), [](int64_t lhs, int64_t rhs){return lhs > rhs;});
    contCout(vecTest);

    return 1;
}



