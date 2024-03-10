#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

bool bs(std::vector<int64_t> orderedVector, int64_t searchValue);
void bsTest();

int main(){
    bsTest();
    return 0;
}

void bsTest(){
    assert(bs({1,2,3,4,5,6,7}, 6) == true);
    assert(bs({1,2,3,4,5,6,7}, 5) == true);
    assert(bs({1,2,3,4,5,6,7}, 8) == false);
    assert(bs({1,2,3,4,5,6,7}, 0) == false);
    assert(bs({1,2,3,5,6,7}, 8) == false);
    assert(bs({1,2,3,5,6,7}, 0) == false);
    assert(bs({}, 6) == false);
    assert(bs({1}, 6) == false);
    assert(bs({6}, 6) == true);
    assert(bs({1,6}, 6) == true);
    assert(bs({6,7}, 6) == true);
    assert(bs({6,7,8}, 6) == true);
    assert(bs({5,6,8}, 6) == true);

    std::vector<int64_t> vecTest = {1,2,3,4,5,6,7};
    assert(bs(vecTest, 6) == std::binary_search(vecTest.begin(), vecTest.end(), 6));
    assert(bs(vecTest, 5) == std::binary_search(vecTest.begin(), vecTest.end(), 5));
    assert(bs(vecTest, 8) == std::binary_search(vecTest.begin(), vecTest.end(), 8));
    assert(bs(vecTest, 0) == std::binary_search(vecTest.begin(), vecTest.end(), 0));

    vecTest.clear();
    assert(bs(vecTest, 6) == std::binary_search(vecTest.begin(), vecTest.end(), 6));

    vecTest.push_back(1);
    assert(bs(vecTest, 6) == std::binary_search(vecTest.begin(), vecTest.end(), 6));
    
    vecTest[0] = 6;
    assert(bs(vecTest, 6) == std::binary_search(vecTest.begin(), vecTest.end(), 6));

    vecTest.clear();
    vecTest.push_back(1);
    vecTest.push_back(6);
    assert(bs(vecTest, 6) == std::binary_search(vecTest.begin(), vecTest.end(), 6));

    vecTest.clear();
    vecTest.push_back(6);
    vecTest.push_back(7);
    assert(bs(vecTest, 6) == std::binary_search(vecTest.begin(), vecTest.end(), 6));

    vecTest.push_back(8);
    assert(bs(vecTest, 6) == std::binary_search(vecTest.begin(), vecTest.end(), 6));

    vecTest.clear();
    vecTest.push_back(5);
    vecTest.push_back(6);
    vecTest.push_back(8);
    assert(bs(vecTest, 6) == std::binary_search(vecTest.begin(), vecTest.end(), 6));

    std::cout << "OK bsTest" << std::endl;
}

bool bs(std::vector<int64_t> orderedVector, int64_t searchValue){

    bool valueFound = false;

    int64_t lhi = 0;
    int64_t rhi = orderedVector.size()-1;
    int64_t mi = lhi + (rhi-lhi)/2;

    while(lhi <= rhi && (valueFound = (orderedVector[mi] == searchValue), !valueFound)){

        if (searchValue>orderedVector[mi])
            lhi = mi + 1;
        else
            rhi = mi - 1;   

        mi = lhi + (rhi-lhi)/2;    
    }
    
    return valueFound;
}