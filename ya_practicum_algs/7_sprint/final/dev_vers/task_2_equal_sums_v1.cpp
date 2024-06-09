#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

struct SumByNominals{
    int sum = 0;
    int nominal = 0;
    int count = 0;

    bool operator < (const SumByNominals& rhs) const {
        if (sum != rhs.sum)
            return sum < rhs.sum;

        if (nominal != rhs.nominal)
            return nominal < rhs.nominal;

        if (count != rhs.count)
            return count < rhs.count;

        return false;    
    };
};

//typedef std::multimap<int, int> CalcMap;
typedef std::set<int> CalcSet;

int main(){

    int n;

    int x, k;
    x = 0;
    std::cin >> k;

    int zeroCount = 0;
    int inputValue = 0;
    std::vector<int> nominals(k);
    for(int i=0; i<k; ++i){
        std::cin >> inputValue;
        if (inputValue == 0){
            ++zeroCount;
            continue;
        }
        nominals[i-zeroCount] = inputValue;
        x += nominals[i-zeroCount];
    }
    k -= zeroCount;

    if ((x % 2) > 0){
        std::cout << "False";
        return 0;
    }

    x /= 2;    

    //std::sort(nominals.begin(), nominals.end(), [](int lhs, int rhs){return lhs > rhs;});

    CalcSet calcVarsResult;
    //calcVarsResult.insert({0, 0});
    calcVarsResult.insert(0);

    bool found = false;

    for(int i=0; i<k; ++i){

        int maxCalsSum = 0;
        int curNominal = 0;
        //CalcMap CalcVarsTemp;
        CalcSet CalcVarsTemp;
        CalcVarsTemp.clear();

        // Заполним временную таблицу на основе результата
        curNominal = nominals[i];
        
        for (auto item : calcVarsResult){
            //int curResultSum = item.first;
            int curResultSum = item;
            int newSum = curResultSum + curNominal;

            if (newSum == x){
                std::cout << "True";
                return 0;
            } else if (newSum > x)
                continue;

            CalcVarsTemp.insert({newSum, 0});
        }

        // Скопируем временную в результат, без замены значений, т.к. идем с больших номиналов
        for (auto item : CalcVarsTemp){
            // int curSum = item.first;
            // calcVarsResult.insert({curSum, 0});
            int curSum = item;
            calcVarsResult.insert(curSum);
        }
    }

    int varsCount = calcVarsResult.count(x);
    
    if (varsCount > 0)
        std::cout << "True";
    else
        std::cout << "False";

    return 0;
}