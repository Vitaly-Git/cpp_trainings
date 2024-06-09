#include <iostream>
#include <vector>

typedef std::int64_t int_t;
typedef std::string str_t;
typedef std::vector<str_t> vec_str_t;

str_t maxCommonPrefix(const vec_str_t& strings);

int main(){

    // Ввод исходных данных
    int_t n;
    std::cin >> n;

    vec_str_t strings(n);
    for(int_t i = 0; i<n; ++i)
        std::getline(std::cin, strings[i]);

    // Выведем наибольший общий префикс
    std::cout << maxCommonPrefix(strings);

    return 0;
}

str_t maxCommonPrefix(const vec_str_t& strings){
    str_t result;



    return result;
}