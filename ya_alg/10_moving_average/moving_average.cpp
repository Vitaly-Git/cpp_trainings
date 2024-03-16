#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>

typedef std::vector<int32_t> vec32;
typedef std::vector<double> vecD;

void movAvgTest();
vecD movAvg(int32_t n, const std::vector<int32_t>& vecSrc, int32_t k);
double roundD(double value, double exp = 10000);

int main(){

    //movAvgTest();    
    int32_t n, k;
    
    std::cin >> n;

    vec32 vecSrc(n);

    for(int32_t i=0; i<n; ++i)
        std::cin >> vecSrc[i];
    std::cin >> k;

    vecD vecRes = movAvg(n, vecSrc, k);

    std::for_each(vecRes.begin(), vecRes.end(),[](auto value){std::cout<<value<<" ";}); 

    return 0;
}

void movAvgTest(){

    vecD vecRes = {roundD(2.5),roundD(3.5),roundD(4.5),roundD(5.5)};
    assert(movAvg(7,{1,2,3,4,5,6,7},4) == vecRes);

    vecRes = {roundD(4.6666666667), roundD(1.666666667), roundD(1), roundD(2), roundD(2.333333335), roundD(2), roundD(0.3333333)};
    assert(movAvg(9,{9,3,2,0,1,5,1,0,0},3) == vecRes);

    vecRes = {roundD(3)};
    assert(movAvg(5,{1,2,3,4,5},5) == vecRes);
}

vecD movAvg(int32_t n, const std::vector<int32_t>& vecSrc, int32_t k){

    vecD vecRes(n-k+1);    

    double sumKWnd = 0;
    for (int32_t i=0; i<k; ++i)
        sumKWnd += vecSrc[i];
    vecRes[0] = roundD(sumKWnd/k);

    for(int32_t i=0; i<(n-k); ++i){
        sumKWnd = sumKWnd - vecSrc[i] + vecSrc[i+k];
        vecRes[i+1] = roundD(sumKWnd / k);
    }

    return vecRes;
}

double roundD(double value, double exp){
    double res = floor(value * exp) / exp;
    return res;
}