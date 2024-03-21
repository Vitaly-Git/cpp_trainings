// Описание алгоритма решения задачи
// 1. Сложность решения O(N), т.к. все числа аналиируем за один обход цикла
// 2. Вектор обходим с двух противоположных сторон
// 3. Обход с двух сторон необходим для поиска наименьших расстояний слева и справа
// 4. С каждой стороны перемещаем два индикатора: положение нуля и текущая цифра
// 5. Для включения режима тестирования необходимо определить макрос UNIT_TESTING

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

    for(auto it=vecZeroDist.begin(); it!=vecZeroDist.end(); ++it){
        if (it!=vecZeroDist.begin()){
            std::cout << " ";
        }
        std::cout << *it;
    }

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

    std::cout << "OK getVectorZeroDistTest" << std::endl;

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
