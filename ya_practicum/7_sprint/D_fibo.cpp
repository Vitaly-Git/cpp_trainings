#include <iostream>
#include <vector>

int main(){

    std::int64_t n,k;
    std::cin >> n;
    k=2;
    ++n;

    std::vector<std::int64_t> steps(n);
    steps[0] = 1;
    steps[1] = 1;

    std::int64_t mod = 1000000000 + 7;

    for (std::int64_t i=2; i<n; ++i)
        for (std::int64_t c=((i-k < 0) ? 0 : (i-k)); c<i; ++c){
            steps[i] += steps[c];
            steps[i] = steps[i] % mod;
        }
    
    std::cout << steps[n-1];

    return 0;
}