#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
//#include <unordered_map>
//#include <multimap>
#include <set>

struct SumByNominals{
    std::int64_t sum = 0;
    std::int64_t nominal = 0;
    std::int64_t count = 0;

    bool operator < (const SumByNominals& rhs) const {
        return (sum < rhs.sum);
    };
};

typedef std::set<SumByNominals> NominalsSet;
typedef std::multimap<std::int64_t, NominalsSet> CalcMap;

int main(){

    std::int64_t x, k;
    std::cin >> x >> k;

    std::vector<std::int64_t> nominals(k);
    for(std::int64_t i=0; i<k; ++i)
        std::cin >> nominals[i];

    std::sort(nominals.begin(), nominals.end(), [](std::int64_t lhs, std::int64_t rhs){return lhs > rhs;});

    CalcMap calcVarsResult;
    //calcVarsResult[0] = NominalsSet();
    calcVarsResult.insert({0, NominalsSet()});

    for(std::int64_t i=0; i<k; ++i){

        std::int64_t maxCalsSum = 0;
        std::int64_t curNominal = 0;
        CalcMap CalcVarsTemp;

        // Заполним временную таблицу на основе результата
        while (curNominal <= x){
            curNominal += nominals[i];
            
            for (auto item : calcVarsResult){
                std::int64_t curResultSum = item.first;
                std::int64_t newSum = curResultSum + curNominal;

                if (newSum > x)
                    continue;
                // else if (newSum != x)
                //     if (calcVarsResult.count(newSum)>0 || CalcVarsTemp.count(newSum)>0) 
                //         continue; 

                NominalsSet nominalsSet = item.second;
                
                SumByNominals sumByNominals = {curNominal, nominals[i], curNominal / nominals[i]};
                nominalsSet.insert(sumByNominals);
                CalcVarsTemp.insert({newSum, nominalsSet});                
            }

        }

        // Скопируем временную в результат, без замены значений, т.к. идем с больших номиналов
        for (auto item : CalcVarsTemp){
            std::int64_t curSum = item.first;
            NominalsSet nominalsSet = item.second;
            calcVarsResult.insert({curSum, nominalsSet});                
        }
    }

    std::cout << calcVarsResult.count(x);

    return 0;
}