#include <iostream>
#include <cassert>

bool is4pow(int16_t num);
void is4powTest();

int main(){

    //is4powTest();

    int16_t num;

    std::cin >> num;

    std::cout << (is4pow(num)?"True":"False");

    return 0;
}

void is4powTest(){

    assert(is4pow(15) == false);
    assert(is4pow(16) == true);
    assert(is4pow(64) == true);
    assert(is4pow(1) == true);
    assert(is4pow(151) == false);
    assert(is4pow(0) == false);
}

bool is4pow(int16_t num){

    if(num==1)
        return true;

    int16_t reminder = 0;

    while(num>1 && reminder==0){
        reminder = num%4;
        num = num/4;
    }

    return (abs(num)==1 && reminder==0);
}