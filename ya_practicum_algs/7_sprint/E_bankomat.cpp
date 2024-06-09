#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

typedef int CoupersCount;
typedef std::multimap<int, CoupersCount> CalcMap;

int main(){

    int x, k;
    std::cin >> x >> k;

    std::set<int> checkDoubles;

    std::vector<int> nominals;
    for(int i=0; i<k; ++i){
        
        int num;
        std::cin >> num;

        if (checkDoubles.count(num)>0)
             continue;

        nominals.push_back(num); 
        checkDoubles.insert(num);
    }
    k = nominals.size();

    std::sort(nominals.begin(), nominals.end(), [](int& lhs, int& rhs){return lhs > rhs;});

    CalcMap calcVarsResult;
    calcVarsResult.emplace(0, 0);

    std::set<int> checkDoubls;

    for(int i=0; i<k; ++i){

        int maxCalsSum = 0;
        int curNominal = 0;
        CalcMap CalcVarsTemp;
        CalcVarsTemp.clear();
        int newSum = 0;

        // Заполним временную таблицу на основе результата
        while (curNominal <= x){
            curNominal += nominals[i];
            newSum = 0;

            for (const auto& item : calcVarsResult){
                newSum = item.first + curNominal;
                if (newSum > x)
                    break;

                if (newSum == x){
                    CalcVarsTemp.emplace(newSum, item.second + curNominal / nominals[i]);
                    break;
                }else if (checkDoubls.find(newSum)==checkDoubls.end()){
                     CalcVarsTemp.emplace(newSum, item.second + curNominal / nominals[i]);
                     checkDoubls.insert(newSum);
                }
                    
            }
            if (newSum == x)
                break;
        }

        // Скопируем временную в результат, без замены значений, т.к. идем с больших номиналов
        for (const auto& item : CalcVarsTemp){
            int curSum = item.first;
            CoupersCount coupersCount = item.second;
            if (curSum == x) {
                calcVarsResult.emplace(curSum, coupersCount);                
            } else {
                if (calcVarsResult.find(newSum)==calcVarsResult.end())
                    calcVarsResult.emplace(curSum, coupersCount);                
            }
        }
        CalcVarsTemp.clear();

    }

    if (calcVarsResult.count(x)>0){
        int resultMinCupCount = INT16_MAX;
        for (auto[itr, rangeEnd] = calcVarsResult.equal_range(x); itr != rangeEnd; ++itr)
            resultMinCupCount = std::min(resultMinCupCount, itr->second);
        std::cout << resultMinCupCount;
    } else {
        std::cout << -1;
    }

    return 0;
}