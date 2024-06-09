// Ссылка на отчёт в контесте:
// https://contest.yandex.ru/contest/22450/run-report/110340792/
//
// Описание принципов и алгоритма решения задачи:
// 1. Для подсчета количества введенных цифр записываем их с количестовом 
//    в ассоциативный контейнер, а затем сравниваем с возможным максимумом (к*2).
// 2. Выбор контейнера осущестлялся между map и unordered_map.
// 3. Выбран unordered_map, т.к. время вставки у него O(1) против O(log n) у map,
//    будут затраты памяти на хэш таблицу, но у нас всего 9 чисел, а 
//    ограничение памяти по задаче равно 64Mb, поэтому приемлемо.
// 4. Минимальная сложность решения O(1), т.к. в случае исключения подпрограммы 
//    расчёт и выноса функционал в функцию main, добавление в хэш таблицу будет выполняться 
//    за O(1), а обход хэша будет равен количеству различных цифр (не более 9).
// 5. Фактическая сложность решения O(N), т.к. функционал расчета вынесен в подпрограмму,
//    которая обходит вектор входных данных.
// 6. Для включения режима тестирования необходимо определить макрос UNIT_TESTING,
//    или раскомментировать соответствующую строчку ниже.
// 7. Сборка программы может быть выполнена с помощью ./make

//#define UNIT_TESTING

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <iterator>

int maxScore(int k, const std::vector<std::string>& inputDataRows);
int maxScoreTest();

int main(){

    #ifdef UNIT_TESTING
        return maxScoreTest();
    #endif

    int k;
    std::cin >> k;

    std::vector<std::string> inputDataRows(4);
    std::cin.ignore();
    for(int strIdx=0; strIdx<4; ++strIdx)
        std::getline(std::cin, inputDataRows[strIdx]);

    std::cout << maxScore(k, inputDataRows);

    return 0;
}

int maxScoreTest(){

    assert(maxScore(3, {"1231","2..2","2..2","2..2"}) == 2);
    assert(maxScore(4 ,{"1111","9999","1111","9911"}) == 1);
    assert(maxScore(4, {"1111","1111","1111","1111"}) == 0);
    assert(maxScore(2, {"1113","2223","4644","5553"}) == 6);
    assert(maxScore(1, {"1113","2223","4644","5553"}) == 1);
    assert(maxScore(9, {"1113","2223","4644","5553"}) == 6);
    assert(maxScore(9, {"1111","1111","1111","1111"}) == 1);
    assert(maxScore(9, {"....","....","....","...."}) == 0);
    assert(maxScore(1, {"....","....","..1.","...."}) == 1);
    assert(maxScore(1, {"1...","....","..1.","...1"}) == 0);
    assert(maxScore(1, {"1...","....","....","...1"}) == 1);

    std::cout << "OK maxScoreTest" << '\n';

    return 0;
}

int maxScore(int k, const std::vector<std::string>& inputDataRows){
    
    int resultScore = 0;
    std::unordered_map<int, int> numsCount;
    int max_k = k*2;

    for(auto strData : inputDataRows)
        for (int charIdx=0; charIdx<strData.size(); ++charIdx)
            if (strData[charIdx]>='0' && strData[charIdx]<='9')
                ++numsCount[strData[charIdx]-'0'];

    for(auto it=numsCount.begin(); it!=numsCount.end(); ++it)
        resultScore = resultScore + (it->second <= max_k ? 1 : 0);

    return resultScore;
}
