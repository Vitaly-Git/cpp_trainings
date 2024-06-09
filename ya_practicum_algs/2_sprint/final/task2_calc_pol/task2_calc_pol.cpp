/*
Ссылка на отчёт в контесте:
https://contest.yandex.ru/contest/22781/run-report/110498103/

-- ПРИНЦИП РАБОТЫ --
1. Для решение задачи примнили стек.
2. С помощью него реализовали алгоритм по условию задачи:
   Для вычисления значения выражения, записанного в обратной польской нотации, 
   нужно считывать выражение слева направо и придерживаться следующих шагов:
   2.1. Обработка входного символа:
      - Если на вход подан операнд, он помещается на вершину стека.
      - Если на вход подан знак операции, то эта операция выполняется 
        над требуемым количеством значений, взятых из стека в порядке добавления. 
        Результат выполненной операции помещается на вершину стека.
   2.2. Если входной набор символов обработан не полностью, перейти к шагу 1.
   2.3. После полной обработки входного набора символов результат вычисления
        выражения находится в вершине стека. Если в стеке осталось несколько чисел, 
        то надо вывести только верхний элемент.
3. Тип значений стека выбран int32_t (значения от -2,147,483,647 до 2,147,483,647), 
   т.к. гарантируется, что значение промежуточных выражений в тестовых данных по модулю 
   не больше 50000.
   Тип int16_t содержит значения от -32767 до 32767, поэтому его не достаточно.
4. Для включения режима тестирования необходимо определить макрос UNIT_TESTING,
   или раскомментировать соответствующую строчку ниже. 

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
1. Стек позволяет работать с операндами по принципу LIFO, что и требовалось нам в 
   данной задаче. Мы складывали в стек операнды, а при получении операции обрабатывали
   операнды помещая результат обратно в стек.

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
1. Для обеспечения сложности О(N) выбран контейнер стек.
2. Помещение и извлечение данных из стека выполняется за О(1), 
   и в нашем случаем сложность обработки зависит только от количества элементов N,
   поэтому итогая сложность О(N).
3. Амортизированная сложность равна О(1), т.к. всего элементов N, то О(N)/N=О(1).
   
-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
1. Память расходуется на создание стека и равна O(N), где N - количество операндов.
*/

#include <iostream>
#include <stack>
#include <cassert>
#include <cmath>

//#define UNIT_TESTING

int calculatePolandStringTest();
int32_t calculatePolandString(const std::string& polStr);
void processValueString(const std::string& valueStr, std::stack<int32_t>& operands);
void getOperandsFromStack(int32_t& operand1, int32_t& operand2, std::stack<int32_t>& operands);

int main(){

    #ifdef UNIT_TESTING
        return calculatePolandStringTest();
    #endif    

    std::string polandString;
    std::getline(std::cin, polandString);

    std::cout << calculatePolandString(polandString);

    return 0;
}

int calculatePolandStringTest(){

    assert(calculatePolandString("")==0);
    assert(calculatePolandString("3 4 +")==7);
    assert(calculatePolandString("12 5 /")==2);
    assert(calculatePolandString("10 2 4 * -")==2);
    assert(calculatePolandString("2 1 + 3 *")==9);
    assert(calculatePolandString("7 2 + 4 * 2 +")==38);
    assert(calculatePolandString("-1 3 /")==-1);
    assert(calculatePolandString("256 -256 +")==0);

    std::cout << "OK calculatePolandStringTest" << "\n";

    return 0;
}

int32_t calculatePolandString(const std::string& polStr){

    int32_t result = 0;

    std::stack<int32_t> operands;

    std::string valueStr;
    int64_t startNewValue = 0;
    bool spaceWasFound = false;

    for(int64_t i=0; i<polStr.size(); ++i){
        char currentChar = polStr[i];

        if (currentChar == ' ' && !spaceWasFound){
            valueStr = polStr.substr(startNewValue, i-startNewValue);
            processValueString(valueStr, operands);
            spaceWasFound = true;
        }else if (spaceWasFound && currentChar != ' '){
            startNewValue = i;
            spaceWasFound = false;
        }
    }

    if (!spaceWasFound && polStr.size()>0){
        valueStr = polStr.substr(startNewValue, polStr.size()-startNewValue);
        processValueString(valueStr, operands);        
    }

    result = (operands.size() == 0 ? 0 : operands.top());
    return result;
}

void processValueString(const std::string& valueStr, std::stack<int32_t>& operands){

    if (valueStr.size()==0)
        return;

    char operation = valueStr[0];

    if (valueStr.size()==1 && (operation == '+' || operation == '-' || operation == '*' || operation == '/')){

        int32_t operand1 = 0;
        int32_t operand2 = 0;
        int32_t operationResult = 0;

        getOperandsFromStack(operand1, operand2, operands);

        switch (operation){
            case '+':
                operationResult = operand1 + operand2;
                break;
            case '-':
                operationResult = operand1 - operand2;
                break;
            case '*':
                operationResult = operand1 * operand2;
                break;
            case '/':
                operationResult = std::floor(operand1 / (double)operand2);
                break;
        }
        operands.push(operationResult);

    }else{
        int32_t value = std::stol(valueStr);
        operands.push(value);
    }    
}

void getOperandsFromStack(int32_t& operand1, int32_t& operand2, std::stack<int32_t>& operands){
    operand2 = operands.top();
    operands.pop();
    operand1 = operands.top();
    operands.pop();
}