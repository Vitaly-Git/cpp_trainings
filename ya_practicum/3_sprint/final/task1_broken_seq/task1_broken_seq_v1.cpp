#include <iostream>
#include <vector>
#include <cassert>

#define UNIT_TESTING

int broken_search(const std::vector<int>& numSeq, int numToFind);
int binaryLikeSearch(const std::vector<int>& numSeq, int numToFind, int lhp, int rhp);
int broken_searchTest();
void test();

int main(){

    #ifdef UNIT_TESTING
        return broken_searchTest();
    #endif

    int n;
    std::cin >> n;

    int k;
    std::cin >> k;

    std::vector<int> numSeq(n);
    for (int i=0; i<n; ++i)
        std::cin >> numSeq[i];

    std::cout << broken_search(numSeq, k);

    return 0;
}

int broken_searchTest(){

    std::vector<int> numSeq;

    numSeq = {1,2,3,4,5,6}; assert(broken_search(numSeq, 2) == 1);
    numSeq = {1,2,3,4,5}; assert(broken_search(numSeq, 8) == -1);
    numSeq = {4,5,1,2,3,3}; assert(broken_search(numSeq, 5) == 1);
    numSeq = {4,5,9,1,2,3}; assert(broken_search(numSeq, 2) == 4);
    numSeq = {4,5,9,2,3,4}; assert(broken_search(numSeq, 8) == -1);
    numSeq = {4,5,9,2,3,4}; assert(broken_search(numSeq, 9) == 2);
    numSeq = {4,5,9,2,3,4}; assert(broken_search(numSeq, 3) == 4);
    numSeq = {4,5,9,10,11,2,3,4}; assert(broken_search(numSeq, 3) == 6);
    numSeq = {4,5,9,10,11,2,3,4}; assert(broken_search(numSeq, 3) == 6);
    numSeq = {4,5,9,0,1,2,3,4}; assert(broken_search(numSeq, 3) == 6);
    numSeq = {4,5,9,0,1,2,3,4}; assert(broken_search(numSeq, 5) == 1);
    numSeq = {19,21,100,101,1,4,5,7,12}; assert(broken_search(numSeq, 5) == 6);
    numSeq = {5,1,2}; assert(broken_search(numSeq, 1) == 1);
    numSeq = {5,1,2}; assert(broken_search(numSeq, 5) == 0);
    numSeq = {5,1,2}; assert(broken_search(numSeq, 2) == 2);
    numSeq = {5,1,2}; assert(broken_search(numSeq, 6) == -1);
    numSeq = {5,1,2}; assert(broken_search(numSeq, 4) == -1);
    numSeq = {19,21,100,101,1,4,5,7,12}; assert(broken_search(numSeq, 19) == 0);
    numSeq = {19,21,100,101,1,4,5,7,12}; assert(broken_search(numSeq, 8) == -1);
    numSeq = {19,21,100,101,1,4,5,7,12}; assert(broken_search(numSeq, 12) == 8);

    numSeq = {19,21,100,101,1,4,5,7,12};
    for (int totalLoops=0; totalLoops<numSeq.size()-1; ++totalLoops){
        
        int firstItem = numSeq[0];
        for (int i=0; i<numSeq.size()-1; ++i)
            numSeq[i] = numSeq[i+1];
        numSeq[numSeq.size()-1] = firstItem;

        for (int iNum=0; iNum<numSeq.size(); ++iNum){
            int num = numSeq[iNum];
            assert(broken_search(numSeq, num) == iNum);
        }
    }
    


    std::cout << "OK broken_searchTest()" << "\n";

    return 0;
}

int broken_search(const std::vector<int>& numSeq, int numToFind){

    int lhp = 0;
    int rhp = numSeq.size();
    int res = binaryLikeSearch(numSeq, numToFind, lhp, rhp);

    return res;
}

int binaryLikeSearch(const std::vector<int>& numSeq, int numToFind, int lhp, int rhp){

    if (lhp>=rhp)
        return -1;

    int midp = (lhp+rhp)/2;

    int lValue = numSeq[lhp];
    int mValue = numSeq[midp];
    int rValue = numSeq[rhp-1];

    if (numToFind == mValue)
        return midp;
    else if (numToFind == lValue)
        return lhp;
    else if (numToFind == rValue)
        return rhp-1;
    else if (rhp == midp+1)
        return -1;
    else if (lhp == midp)
        return -1;

    else if (numToFind >= lValue && numToFind <= mValue && numToFind <= rValue)
        rhp = midp;

    else if (numToFind >= lValue && numToFind >= mValue && numToFind <= rValue && mValue <= rValue)
        lhp = midp;

    else if (numToFind >= lValue && numToFind >= mValue && mValue <= rValue)
        rhp = midp;

    else if (numToFind >= lValue && numToFind >= mValue) // && numToFind <= rValue)
        lhp = midp;

    else if (numToFind <= rValue && mValue >= rValue)
        lhp = midp;

    else if (lValue >= numToFind && numToFind <= mValue)
        rhp = midp;

    // else if (numToFind >= lValue && numToFind >= mValue)
    //     lhp = midp;

    else if (numToFind >= lValue && numToFind <= mValue)
        rhp = midp;
    else if (numToFind >= mValue && numToFind <= rValue)
        lhp = midp;
    else if (numToFind <= rValue)
        lhp = midp;
    else    
        rhp = midp+1;

  return binaryLikeSearch(numSeq, numToFind, lhp, rhp);
}

int binaryLikeSearchV2(const std::vector<int>& numSeq, int numToFind, int lhp, int rhp){

    if (lhp>=rhp)
        return -1;

    int midp = (lhp+rhp)/2;

    int lValue = numSeq[lhp];
    int mValue = numSeq[midp];
    int rValue = numSeq[rhp-1];

    if (numToFind == mValue)
        return midp;
    else if (numToFind == lValue)
        return lhp;
    else if (numToFind == rValue)
        return rhp-1;
    else if (rhp == midp+1)
        return -1;
    else if (lhp == midp)
        return -1;

    else if (numToFind >= lValue && numToFind <= mValue && numToFind <= rValue)
        rhp = midp;

    else if (numToFind >= lValue && numToFind >= mValue && numToFind <= rValue && mValue <= rValue)
        lhp = midp;

    else if (numToFind >= lValue && numToFind >= mValue && mValue <= rValue)
        rhp = midp;

    else if (numToFind >= lValue && numToFind >= mValue) // && numToFind <= rValue)
        lhp = midp;

    else if (numToFind <= rValue && mValue >= rValue)
        lhp = midp;

    else if (lValue >= numToFind && numToFind <= mValue)
        rhp = midp;

    // else if (numToFind >= lValue && numToFind >= mValue)
    //     lhp = midp;

    else if (numToFind >= lValue && numToFind <= mValue)
        rhp = midp;
    else if (numToFind >= mValue && numToFind <= rValue)
        lhp = midp;
    else if (numToFind <= rValue)
        lhp = midp;
    else    
        rhp = midp+1;

  return binaryLikeSearch(numSeq, numToFind, lhp, rhp);
}

int binaryLikeSearchV1(const std::vector<int>& numSeq, int numToFind, int lhp, int rhp){

    if (lhp>=rhp)
        return -1;

    int mid = (lhp+rhp)/2;

    if (numToFind == numSeq[mid])
        return mid;
    else if (numToFind == numSeq[lhp])
        return lhp;
    else if (numToFind == numSeq[rhp-1])
        return rhp-1;
    else if (numToFind <= numSeq[mid] && numToFind >= numSeq[lhp])
        rhp = mid;
    else if (numToFind <= numSeq[rhp-1])
        lhp = mid;
    else if (rhp == mid+1)
        return -1;
    else    
        rhp = mid+1;

  return binaryLikeSearch(numSeq, numToFind, lhp, rhp);
}

void test() {
    std::vector<int> arr = {19, 21, 100, 101, 1, 4, 5, 7, 12};
    assert(6 == broken_search(arr, 5));
}