#include <iostream>
#include <stack>
#include <unordered_map>
#include <cassert>

//#define UNIT_TESTING

bool is_correct_bracket_seq(std::string strBrackets);
int is_correct_bracket_seq_test();

int main(){

    #ifdef UNIT_TESTING
        return is_correct_bracket_seq_test();
    #endif

    std::string strBrackets;
    std::getline(std::cin, strBrackets);

    std::cout << (is_correct_bracket_seq(strBrackets) ? "True" : "False");

    return 0;
}

int is_correct_bracket_seq_test(){

    assert(is_correct_bracket_seq("") == true);
    assert(is_correct_bracket_seq("()") == true);
    assert(is_correct_bracket_seq("[]") == true);
    assert(is_correct_bracket_seq("()]") == false);
    assert(is_correct_bracket_seq("[(()())(((()())))]") == true);

    std::cout << "OK is_correct_bracket_seq_test" << "\n";

    return 0;   
}

bool is_correct_bracket_seq(std::string strBrackets){
    
    bool isCorrectSeq = true;
    std::stack<char> openBrackets;
    std::unordered_map<char,char> pairsGood;

    pairsGood['{'] = '}';
    pairsGood['['] = ']';
    pairsGood['('] = ')';
    pairsGood[')'] = '(';
    pairsGood[']'] = '[';
    pairsGood['}'] = '{';

    for(int64_t i=0; i<strBrackets.size(); ++i){
        
        char curChar = strBrackets[i];

        if (curChar == '{' || curChar== '[' || curChar == '('){
            openBrackets.push(curChar);
        }else if(curChar == '}' || curChar== ']' || curChar == ')'){
            if (openBrackets.size() == 0 || openBrackets.top()!=pairsGood[curChar]){
                isCorrectSeq = false;
                break;               
            }
            openBrackets.pop();
        }else{
            isCorrectSeq = false;
            break;
        }
    }

    return isCorrectSeq && openBrackets.size() == 0;
}

