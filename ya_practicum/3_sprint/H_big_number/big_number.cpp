#include <iostream>
#include <vector>
#include <algorithm>

struct numWithOrder{
    int16_t number;
    int16_t order;
    int16_t orderPrec;
};

int main(){

    int16_t n;
    std::cin >> n;

    std::vector<numWithOrder> numbers(n);
    for(int16_t i=0; i<n; ++i){

        std::cin >> numbers[i].number;

        if (numbers[i].number >= 1000)
            numbers[i].order = 0;
        else if (numbers[i].number == 10)
            numbers[i].order = 101;
        else if (numbers[i].number < 10)
            numbers[i].order = numbers[i].number*100 + numbers[i].number*10 + numbers[i].number; // Создаем порядок на основе максимального числа, которое может следовать после.
        else if (numbers[i].number < 100){
            numbers[i].order = numbers[i].number*10 + numbers[i].number/10;
        }else{
            numbers[i].order = numbers[i].number;
        }    

        if (numbers[i].order > 100)
            numbers[i].orderPrec = numbers[i].number%100;
        else if (numbers[i].order > 10)
            numbers[i].orderPrec = numbers[i].number%10;
    }

    std::sort(numbers.begin(), numbers.end(), [](const numWithOrder& lhs, const numWithOrder& rhs){
        if (lhs.order == rhs.order)
            return lhs.orderPrec < rhs.orderPrec;
        else
            return lhs.order > rhs.order;});

    for(auto numWithOrder : numbers)
        std::cout << numWithOrder.number;

    return 0;    
}
