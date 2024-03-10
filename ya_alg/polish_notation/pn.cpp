#include <iostream>
#include <stack>
#include <cassert>
#include <algorithm>
#include <limits>


void calcPolishNotationTest();
int64_t calcPolishNotation(std::string formula);

int main(){
    calcPolishNotationTest();
    return 0;
}

void calcPolishNotationTest(){
    assert(calcPolishNotation("(+ 2 4)") == 6);
    assert(calcPolishNotation("(*(+3 6)(*1 2 3))") == 54);
    assert(calcPolishNotation("(*(*3 6)(+1 2 3 4))") == 180);

    std::cout << "OK calcPolishNotationTest" << std::endl;
}

int64_t calcPolishNotation(std::string formula){
    int64_t result = 0;

    std::stack<char> signStack;
    std::stack<int64_t> digitStack;

    for(char ch:formula){
        int64_t curValue = 0;
        int64_t localResult = 0;

        switch (ch){
        case '(':
            break;

        case ')':
            curValue = 0;
            result = signStack.top()=='+'?0:1;
            do {
                switch (signStack.top()){
                    case '+':
                        result += digitStack.top();
                        break;
                    case '*':
                        result *= digitStack.top();
                        break;
                }
                digitStack.pop();
                curValue = digitStack.top();
            } while (curValue != std::numeric_limits<int64_t>::max());
            signStack.pop();
            digitStack.pop();
            digitStack.push(result);
            break;

        case '+':
        case '*':    
            signStack.push(ch);
            digitStack.push(std::numeric_limits<int64_t>::max());
            break;

        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            digitStack.push((int64_t)(ch-'0'));
            break;

        }

    }

    return result;
}