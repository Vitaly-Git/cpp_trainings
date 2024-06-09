#include <iostream>
#include <vector>

typedef std::int64_t int_t;
typedef std::string str_t;
typedef std::vector<str_t> vec_str_t;

str_t isGoodCheatSheet(const str_t& cheatSheet, const vec_str_t& words);

int main(){

    // Ввод исходных данных
    str_t cheatSheet;
    std::getline(std::cin, cheatSheet);

    int_t n;
    std::cin >> n;

    vec_str_t words(n);
    for(int_t i = 0; i<n; ++i)
        std::getline(std::cin, words[i]);

    // Проверяем хорошая подсказка или нет
    std::cout << isGoodCheatSheet(cheatSheet, words);

    return 0;
}

str_t isGoodCheatSheet(const str_t& cheatSheet, const vec_str_t& words){
    str_t result = "YES";


    return result;
}