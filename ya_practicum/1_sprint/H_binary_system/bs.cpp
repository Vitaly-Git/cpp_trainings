#include <iostream>
#include <cassert>

std::string getBinSum(const std::string& binStr1, const std::string& binStr2);
void getBinSumTest();

int main(){

    //getBinSumTest();

    std::string str1;
    std::string str2;

    std::getline(std::cin, str1);
    std::getline(std::cin, str2);

    std::cout << getBinSum(str1, str2);

    return 0;
}

void getBinSumTest(){
    assert(getBinSum("1010", "1011") == "10101");
    assert(getBinSum("10000", "1") == "10001");
    assert(getBinSum("10000", "101") == "10101");
    assert(getBinSum("10000", "10101") == "100101");
    assert(getBinSum("1", "1") == "10");
    assert(getBinSum("1", "0") == "1");

    std::cout << "OK getBinSumTest" << std::endl;
}

std::string getBinSum(const std::string& binStr1, const std::string& binStr2){

    std::string resultSumStr = "";

    int16_t str1Len = binStr1.size();
    int16_t str2Len = binStr2.size();
    int16_t maxLen = std::max(str1Len, str2Len);
    char nextHiDig = '0';

    for(int i=1; i<=maxLen; ++i){
        
        int16_t curPosStr1 = str1Len-i;
        int16_t curPosStr2 = str2Len-i;
        char charStr1 = 0;
        char charStr2 = 0;

        if (curPosStr1>=0)
            charStr1 = binStr1[curPosStr1];
        else    
            charStr1 = '0';

        if (curPosStr2>=0)
            charStr2 = binStr2[curPosStr2];
        else    
            charStr2 = '0';

        char resChar = '0';
        char newNextHiDig = '0';

        if(charStr1!=charStr2){
            if (nextHiDig == '1'){
                resChar = '0';
                newNextHiDig = '1';
            }else{
                resChar = '1';
            }
        }else if(charStr1=='0')
            if (nextHiDig == '1')
                resChar = '1';
            else
                resChar = '0';
        else{
            if (nextHiDig == '1')
                resChar = '1';
            else
                resChar = '0';
            newNextHiDig = '1';
        }
        nextHiDig = newNextHiDig;

        resultSumStr = resChar + resultSumStr;
    }

    if (nextHiDig == '1')
        resultSumStr = nextHiDig + resultSumStr;

    return resultSumStr;
}