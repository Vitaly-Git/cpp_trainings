// Ссылка на отчёт в контесте:
// https://contest.yandex.ru/contest/22450/run-report/110318346/
//
// Описание принципов и алгоритма решения задачи:
// 1. Сложность решения O(N), т.к. все числа анализируем за один обход цикла.
// 2. Вектор обходим с двух противоположных сторон.
// 3. Обход с двух сторон необходим для поиска наименьших расстояний слева и справа.
// 4. С каждой стороны перемещаем два указателя: положение нуля и текущая цифра.
// 5. Минимальные расстояния запоминаем в результирующем векторе.
// 6. Результирующий вектор передается как переметр по ссылке для оптимизации решения.
// 7. Для включения режима тестирования необходимо определить макрос UNIT_TESTING,
//    или раскомментировать соответствующую строчку ниже.
// 8. Сборка программы может быть выполнена с помощью ./make

//#define UNIT_TESTING

#include <iostream>
#include <vector>
#include <cassert>
#include <limits>
#include <iterator>

typedef std::vector<int32_t> vec32_t;

void getVectorZeroDist(const vec32_t& vecHouseNums, vec32_t& vecZeroDist);
int getVectorZeroDistTest();
bool checkDist(const vec32_t& vecHouseNums, const vec32_t& vecZeroDistPlan);

template <typename T>
void vectorCout(const T& vector);

int main(){

    #ifdef UNIT_TESTING
        return getVectorZeroDistTest();
    #endif

    int32_t n;
    std::cin >> n;
    
    vec32_t vecHouseNums(n);
    for (int32_t i=0; i<n; ++i)
        std::cin >> vecHouseNums[i];

    vec32_t vecZeroDist(n);
    getVectorZeroDist(vecHouseNums, vecZeroDist);

    vectorCout(vecZeroDist);

    return 0;
}

int getVectorZeroDistTest(){

    assert(checkDist({0,1,4,9,0},{0,1,2,1,0}));
    assert(checkDist({0,1,4,0,0},{0,1,1,0,0}));
    assert(checkDist({0,7,9,4,8,20},{0,1,2,3,4,5}));
    assert(checkDist({0},{0}));
    assert(checkDist({0,0},{0,0}));
    assert(checkDist({0,0,0},{0,0,0}));
    assert(checkDist({0,1,0},{0,1,0}));
    assert(checkDist({1,0,1},{1,0,1}));
    assert(checkDist({1,1,0,1,1},{2,1,0,1,2}));
    assert(checkDist({0,1,1,1,1,1000000000,1,0},{0,1,2,3,3,2,1,0}));

    std::cout << "OK getVectorZeroDistTest" << '\n';

    return 0;
}

bool checkDist(const vec32_t& vecHouseNums, const vec32_t& vecZeroDistPlan){
    vec32_t vecZeroDist;
    getVectorZeroDist(vecHouseNums, vecZeroDist);
    return (vecZeroDistPlan == vecZeroDist); 
}

void getVectorZeroDist(const vec32_t& vecHouseNums, vec32_t& vecZeroDist){

    int32_t houseCount = vecHouseNums.size();

    vecZeroDist = vec32_t(houseCount, std::numeric_limits<int32_t>::max());

    int32_t leftHousePtrNum = 0;
    int32_t leftHousePtrZero = -1;
    int32_t rightHousePtrNum = houseCount-1;
    int32_t rightHousePtrZero = -1;

    while (leftHousePtrNum < houseCount){

        int32_t curLeftHouseNum = vecHouseNums[leftHousePtrNum];
        if (curLeftHouseNum==0)
            leftHousePtrZero = leftHousePtrNum;
        if (leftHousePtrZero >= 0) 
            vecZeroDist[leftHousePtrNum] = std::min(vecZeroDist[leftHousePtrNum], leftHousePtrNum - leftHousePtrZero);
        
        int32_t curRightHouseNum = vecHouseNums[rightHousePtrNum];
        if (curRightHouseNum==0)
            rightHousePtrZero = rightHousePtrNum;
        if (rightHousePtrZero >= 0) 
            vecZeroDist[rightHousePtrNum] = std::min(vecZeroDist[rightHousePtrNum], rightHousePtrZero - rightHousePtrNum);

        ++leftHousePtrNum;
        --rightHousePtrNum;
    }
}

template <typename T>
void vectorCout(const T& vector){
    for(auto it=vector.begin(); it!=vector.end(); ++it){
        if (it!=vector.begin()){
            std::cout << " ";
        }
        std::cout << *it;
    }
}