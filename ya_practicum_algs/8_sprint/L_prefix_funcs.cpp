#include <iostream>
#include <vector>

std::vector<int> prefix_function(const std::string& s) {
    // Функция возвращает массив длины |s|
    int n = s.length();
    std::vector<int> pi(n, 0);

    for (int i = 1; i < n; ++i) {
        int k = pi[i - 1];
        while (k > 0 && s[k] != s[i]) {
            k = pi[k - 1];
        }
        if (s[k] == s[i]) {
            ++k;
        }
        pi[i] = k;
    }
    return pi;
}

int main(){

    std::string str;
    std::getline(std::cin, str);

    std::vector<int> prefsPoss = prefix_function(str);

    for (const int& pos : prefsPoss)
        std::cout << pos << " ";

    return 0;
}