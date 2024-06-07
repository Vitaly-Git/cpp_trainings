#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

typedef std::set<int> CalcSet;

int main(){

    int n;

    int x, k;
    x = 0;
    std::cin >> k;

    int zeroCount = 0;
    int inputValue = 0;
    std::vector<int> nominals(k);
    int doubsCount = 0;
    std::map<int, int> doubs;
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
    } else{
        x /= 2;
    }

    std::sort(nominals.begin(), nominals.end(), [](int lhs, int rhs){return lhs > rhs;});

    CalcSet calcVarsResult;
    calcVarsResult.insert(0);

    bool found = false;

    for(int i=0; i<k; ++i){

        int maxCalsSum = 0;
        int curNominal = 0;
        CalcSet CalcVarsTemp;
        CalcVarsTemp.clear();

        // Заполним временную таблицу на основе результата
        curNominal = nominals[i];
        
        for (auto curResultSum : calcVarsResult){
            int newSum = curResultSum + curNominal;

            if (newSum == x){
                std::cout << "True";
                return 0;
            } else if (newSum > x)
                continue;

            CalcVarsTemp.insert(newSum);
        }

        // Скопируем временную в результат, без замены значений, т.к. идем с больших номиналов
        for (auto item : CalcVarsTemp)
            calcVarsResult.insert(item);
    }
    
    if (calcVarsResult.count(x) > 0)
        std::cout << "True";
    else
        std::cout << "False";

    return 0;
}