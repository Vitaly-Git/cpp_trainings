#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

typedef std::set<int> CalcSet;

int main(){

    // Ввод данных

    int n;
    int x, k;
    x = 0;
    std::cin >> k;

    int zeroCount = 0;
    int inputValue = 0;
    std::vector<int> nominals;
    for(int i=0; i<k; ++i){
        std::cin >> inputValue;
        if (inputValue == 0)
            continue;
        nominals.push_back(inputValue);
        x += inputValue;
    }
    k = nominals.size();

    if ((x % 2) > 0){
        std::cout << "False";
        return 0;
    } else{
        x /= 2;
    }

    std::sort(nominals.begin(), nominals.end(), [](int lhs, int rhs){return lhs > rhs;});

    CalcSet calcVarsResult;
    calcVarsResult.insert(0);
    CalcSet CalcVarsTemp;
    int curNum = 0;

    bool found = false;
    for(int i=0; i<k; ++i){

        CalcVarsTemp.clear();
        curNum = nominals[i];
        for (auto curResultSum : calcVarsResult){
            int newSum = curResultSum + curNum;
            if (newSum == x){
                std::cout << "True";
                return 0;
            } else if (newSum > x)
                continue;
            CalcVarsTemp.insert(newSum);
        }

        // Скопируем временную в результат, без замены значений, т.к. идем с больших номиналов
        calcVarsResult.merge(CalcVarsTemp);
    }
    
    if (calcVarsResult.find(x) != calcVarsResult.end())
        std::cout << "True";
    else
        std::cout << "False";

    return 0;
}