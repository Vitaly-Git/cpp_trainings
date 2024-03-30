#include <iostream>
#include <vector>

#define UNIT_TESTING

int64_t findNum(const std::vector<int64>& numSeq, int64_t numToFind);
int64_t findNumTest();

int main(){

  #ifdef UNIT_TESTING
    return findNumTest();
  #endif

  return 0;
}

int findNumTest(){

  assert(findNum({1,2,3,4,5,6}, 2) == 1);
  assert(findNum({1,2,3,4,5}, 8) == -1);
  assert(findNum({4,5,1,2,3,3}, 5) == 1);
  assert(findNum({4,5,9,1,2,3}, 2) == 4);
  assert(findNum({4,5,9,2,3,4}, 8) == -1);
  assert(findNum({4,5,9,2,3,4}, 9) == 2);
  assert(findNum({4,5,9,2,3,4}, 3) == 4);
  assert(findNum({4,5,9,10,11,2,3,4}, 3) == 6);
  assert(findNum({4,5,9,10,11,2,3,4}, 3) == 6);
  assert(findNum({4,5,9,0,1,2,3,4}, 3) == 6);
  assert(findNum({4,5,9,0,1,2,3,4}, 5) == 1);

  std::cout << «OK findNumTest()” << “\n »
  return 0;
}

int64_t findNum(const std::vector<int64>& numSeq, int64_t numToFind){

int64_t res = -1;

int64_t lhp = 0;
int64_t rhp = numSeq.size();

res = binaryLikeSearch(numSeq, lhp, rhp);

  return res;
}

int64_t binaryLikeSearch(const std::vector<int64>& numSeq, int64_t numToFind, int64_t lhp, int64_t rhp){

if (lhp>=rhp)
 return -1;

 int64_t mid = (lhp+rhp)/2;

If (numSeq[mid] == numToFind)
 return mid;

if (numToFind <= numSeq[mid] && numToFind >= numSeq[lhp]){
rhp = mid;
mid = (lhp+rhp)/2;
} else if (numToFind <= numSeq[rhp-1]){
lhp = mid
mid = (lhp+rhp)/2;
} else {
rhp = mid+1;
mid = (lhp+rhp)/2;
}

  return binaryLikeSearch(numSeq, lhp, rhp);
}