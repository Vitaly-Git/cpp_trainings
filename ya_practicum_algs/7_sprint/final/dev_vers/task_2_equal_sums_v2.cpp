#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
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
    std::vector<int> nominals(k);
    //std::vector<int> nominals;
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

    // Удалим одинаковые пары значений
    // std::sort(nominalsInput.begin(), nominalsInput.end(), [](int lhs, int rhs){return lhs > rhs;});

    // x = 0;
    // int prevValue = -1;
    // for(int i=0; i<k; ++i){
    //     if (prevValue == nominalsInput[i]){
    //         nominals.pop_back();
    //         x -= nominalsInput[i];
    //         prevValue = -1;
    //     } else {
    //         nominals.push_back(nominalsInput[i]);
    //         x += nominalsInput[i];
    //         prevValue = nominalsInput[i];
    //     }
    // }
    // k = nominals.size();

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

    bool found = false;
    for(int i=0; i<k; ++i){

        CalcVarsTemp.clear();
        for (auto curResultSum : calcVarsResult){
            int newSum = curResultSum + nominals[i];

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