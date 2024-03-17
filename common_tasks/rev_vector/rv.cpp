#include <iostream>
#include <vector>

int main(){

    std::vector<int64_t> srcVector = {1,2,3,4,5};

    int64_t lhs = 0;
    int64_t rhs = srcVector.size()-1;

    while(lhs<rhs){
        std::swap(srcVector[lhs], srcVector[rhs]);
        ++lhs;
        --rhs;        
    }

    return 0;
}