#include <iostream>

int main(){

    int64_t a,b,c;

    std::cin >> a >> b >> c;
    std::cout << (((abs(a)%2==abs(b)%2) && (abs(b)%2==abs(c)%2)) ? "WIN" : "FAIL");

    return 0;
}