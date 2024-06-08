#include <iostream>
#include <vector>

int main(){

    // Input values and cals deltas
    // We will find by deltas

    std::int64_t n;
    std::cin >> n;

    std::vector<std::int64_t> tempers(n);
    std::vector<std::int64_t> tempersDeltas(n-1);
    std::int64_t prevValue = -7777777;
    for (std::int64_t i=0; i<n; ++i){
        std::cin >> tempers[i];
        if (prevValue != -7777777)
            tempersDeltas[i-1] = tempers[i] - prevValue;
        prevValue = tempers[i];    
    }
        
    std::int64_t m;
    std::cin >> m; 

    std::vector<std::int64_t> pattern(m);
    std::vector<std::int64_t> patternDeltas(m-1);
    prevValue = -7777777;
    for (std::int64_t i=0; i<m; ++i){
        std::cin >> pattern[i];
        if (prevValue != -7777777)
            patternDeltas[i-1] = pattern[i] - prevValue;
        prevValue = pattern[i];    
    }    

    // Find values by deltas
    for (std::int64_t i=0; i<(n-1); ++i){
        bool patternFound = false;
        for (std::int64_t s=i; s<(i+m-1); ++s){
            if (tempersDeltas[s] != patternDeltas[s-i]){
                patternFound = false;
                break;
            } else {
                patternFound = true;
            }
        }
        if (patternFound)
            std::cout << i+1 << " ";
    }

    return 0;
}