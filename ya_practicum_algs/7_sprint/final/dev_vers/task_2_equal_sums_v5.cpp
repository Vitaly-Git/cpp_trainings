#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <vector>

typedef std::vector<int> CalcVector;
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

    std::sort(nominals.begin(), nominals.end(), [](int lhs, int rhs){return lhs < rhs;});

    CalcSet calcVarsResult;
    calcVarsResult.insert(0);
    CalcVector CalcVarsTemp;
    CalcVarsTemp.push_back(0);
    int curNum = 0;

    CalcSet added;

    bool found = false;
    for(int i=0; i<k; ++i){

        int endIndex = CalcVarsTemp.size();

        //CalcVarsTemp.clear();
        curNum = nominals[i];
        //for (auto curResultSum : calcVarsResult){
        for (int j=0; j<endIndex; ++j){
            int newSum = CalcVarsTemp[j] + curNum;
            if (newSum == x){
                std::cout << "True";
                return 0;
            } else if (newSum > x)
                continue;
            //CalcVarsTemp.insert(newSum);
            
            //if (added.find(newSum) == added.end()){
                CalcVarsTemp.push_back(newSum);
                //added.insert(newSum);
            //}
                
        }

        // Скопируем временную в результат, без замены значений, т.к. идем с больших номиналов
        //calcVarsResult.insert(CalcVarsTemp.begin(), CalcVarsTemp.end());
    }
    
    if (std::find(CalcVarsTemp.begin(), CalcVarsTemp.end(), x) != CalcVarsTemp.end())
    //if (calcVarsResult.find(x) != calcVarsResult.end())    
        std::cout << "True";
    else
        std::cout << "False";

    return 0;
}#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <vector>

typedef std::vector<int> CalcVector;
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

    std::sort(nominals.begin(), nominals.end(), [](int lhs, int rhs){return lhs < rhs;});

    CalcSet calcVarsResult;
    calcVarsResult.insert(0);
    CalcVector CalcVarsTemp;
    CalcVarsTemp.push_back(0);
    int curNum = 0;

    CalcSet added;

    bool found = false;
    for(int i=0; i<k; ++i){

        int endIndex = CalcVarsTemp.size();

        //CalcVarsTemp.clear();
        curNum = nominals[i];
        //for (auto curResultSum : calcVarsResult){
        for (int j=0; j<endIndex; ++j){
            int newSum = CalcVarsTemp[j] + curNum;
            if (newSum == x){
                std::cout << "True";
                return 0;
            } else if (newSum > x)
                continue;
            //CalcVarsTemp.insert(newSum);
            
            //if (added.find(newSum) == added.end()){
                CalcVarsTemp.push_back(newSum);
                //added.insert(newSum);
            //}
                
        }

        // Скопируем временную в результат, без замены значений, т.к. идем с больших номиналов
        //calcVarsResult.insert(CalcVarsTemp.begin(), CalcVarsTemp.end());
    }
    
    if (std::find(CalcVarsTemp.begin(), CalcVarsTemp.end(), x) != CalcVarsTemp.end())
    //if (calcVarsResult.find(x) != calcVarsResult.end())    
        std::cout << "True";
    else
        std::cout << "False";

    return 0;
}