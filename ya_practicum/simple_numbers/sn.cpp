#include <iostream>
#include <vector>
using namespace std;

vector<bool> eratosthenes(int n) {
    vector<bool> numbers(n + 1, true);
    numbers[0] = numbers[1] = false;
    for (int num = 2; num < n; num++) {
        if (numbers[num]) {
            for (int j = 2 * num; j <= n; j += num) {
                numbers[j] = false;
            }
        }
    }
    return numbers;
}

int main(){

    auto vecSimplNums = eratosthenes(9);

    std::cout << "[";
    for(auto it = vecSimplNums.begin(); it!=vecSimplNums.end(); ++it){
        if (it != vecSimplNums.begin())
            std::cout << " ";
        //std::cout << static_cast<bool>(*it);
        std::cout << *it;
    }
    std::cout << "]" << std::endl;

    return 0;
}
