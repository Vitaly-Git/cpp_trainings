
/*
   Ссылка на отчёт в контесте:
   https://contest.yandex.ru/contest/26133/run-report/115225765/

-- ПРИНЦИП РАБОТЫ --
   УРААА :))) Задача прошла в контесте с первого раза :)))
1. Эту задачу решал второй в этом финале, т.к. показалась изначально более сложной.
2. В этой задаче основной этап, который заставил задуматься - это распаковка строк, её реализовал рекурсией.
3. Вторым этапом выполнялся поиск одинаковых префиксов.
4. Распаковку планировал реализовать либо рекурсией, либо стеком - избавившись от рекурсии чтобы
   попасть в ограничения задачи.
5. В итоге, выбрал первым вариантом реурсию, т.к. наиболее понятен.
6. Если бы рекурсия не прошла по условиям, заменил бы её.
7. Первый этап выполяется за линейное время, т.к. обхожу буквы последовательно.
8. Второй этап выполняется максимально линейно, символьным сравнением букв в строках (параллельно).
9. Второй этап ещё быстрее, т.к. строки проверяются только по совпадающим префиксам, остальное не смотрим.
-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
1. Мы идем последовательно по каждой букве, в каждом этапе.
2. Перестановок не делаем.
3. Вывод делаем после распаковки по первым буквам слов.
-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
1. O(N) - распаковка, где N общее количество букв во всех словах.
2. O(N) - поиск префикса, где N количество букв в самом коротком слове. 
   При этом это худщий вариант, если в словах все буквы совпадают.
3. Поэтому, итоговая сложность равна: O(N)
-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
1. O(N*X) - распаковка, где N общее количество букв во всех словах, 
   не более 10^5 * X - число слов. Плюс рекурсия, в худшем случае может потребить ещё столькоже, т.к. для 
   распаковки скобок набираем отдельные строки. 
2. O(N) - поиск префикса, где N количество букв в самом коротком слове. 
3. В итоге, в худшем случаем мы выделим место O(N*X*2).
   В худшем случае O(N^2), если X=N.
*/

#include <iostream>
#include <vector>

typedef std::int64_t int_t;
typedef std::string str_t;
typedef std::vector<str_t> vec_str_t;

str_t maxCommonPrefix(const vec_str_t& strings);
int_t decodeStrings(const vec_str_t& srcStr, vec_str_t& dstStr);
void decodeString(const str_t& srcStr, int_t& startPos, str_t& dstStr);
str_t maxPrefix(const vec_str_t& srcVecStr, int_t minStrLen);

int main(){

    // Ввод исходных данных
    int_t n;
    std::cin >> n;

    std::cin.ignore();
    vec_str_t strings(n);
    for(int_t i = 0; i<n; ++i)
        std::getline(std::cin, strings[i]);

    // Выведем наибольший общий префикс
    std::cout << maxCommonPrefix(strings);

    return 0;
}

str_t maxCommonPrefix(const vec_str_t& strings){
    str_t resultMaxPrefix;

    // Распакуем строки
    vec_str_t decodedStrings;
    int_t minStrLen = decodeStrings(strings, decodedStrings);

    // Сравним префиксы
    resultMaxPrefix = maxPrefix(decodedStrings, minStrLen);

    return resultMaxPrefix;
}

int_t decodeStrings(const vec_str_t& srcVecStr, vec_str_t& dstVecStr){
    
    int_t minStrLen = INT64_MAX;
    
    for (int i=0; i<srcVecStr.size(); ++i){
        str_t newStr;
        int_t startPos = 0;
        decodeString(srcVecStr[i], startPos, newStr);
        dstVecStr.push_back(newStr);
        minStrLen = (minStrLen < newStr.size() ? minStrLen : newStr.size());
    }

    return minStrLen;
}

void decodeString(const str_t& srcStr, int_t& startPos, str_t& dstStr){

    if (startPos > srcStr.size()-1)
        return;

    char curLetter = srcStr[startPos];

    if (curLetter >= '0' && curLetter <= '9'){
        str_t resStr;
        decodeString(srcStr, ++startPos, resStr);
        for (int i=0; i<(curLetter-'0');++i)
            dstStr = dstStr + resStr;
    } else if (curLetter == '[') 
        ;
    else if (curLetter == ']')
        return;
    else
        dstStr = dstStr + curLetter;
 
    decodeString(srcStr, ++startPos, dstStr);    
}

str_t maxPrefix(const vec_str_t& srcVecStr, int_t minStrLen){

    str_t prefResult = "";
    bool allLetterEqual = true;

    for (int_t letNum = 0; letNum<minStrLen; ++letNum){
        allLetterEqual = true;
        char checkLetter = srcVecStr[0][letNum];
        for (int_t strNum = 1; strNum < srcVecStr.size(); ++strNum){
            allLetterEqual = allLetterEqual && srcVecStr[strNum-1][letNum] == srcVecStr[strNum][letNum];
            if (!allLetterEqual)
                break;
        }
        if (!allLetterEqual)
            break;
        else
           prefResult = prefResult + checkLetter;
    }

    return prefResult;
}