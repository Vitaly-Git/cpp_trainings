#include <iostream>

int main(){

    std::string str1;
    std::string str2;

    std::getline(std::cin, str1);
    std::getline(std::cin, str2);

    int strLen1 = str1.size();
    int strLen2 = str2.size();
    int maxLen = std::max(strLen1, strLen2);

    if (abs(strLen1-strLen2) > 1){
        std::cout << "FAIL";
        return 0;
    } else if ((strLen1 == strLen2) && (strLen1 == 0)){
        std::cout << "OK";
        return 0;
    } else if ((strLen1 == strLen2) && (strLen1 == 1)){    
        std::cout << "OK";
        return 0;
    } else if ((strLen1 == strLen2) && (str1 == str2)) {
        std::cout << "OK";
        return 0;
    }
        
    // bool strEq = true;
    // bool diffFound = false;

    int shiftStr1 = 0;
    int shiftStr2 = 0;

    for (int i=0; i<maxLen; ++i){
        
        // if (str1[i + shiftStr1] == str2[i + shiftStr2]){
        //     strEq = strEq & true;
        //     continue;
        // }

        if (str1[i + shiftStr1] != str2[i + shiftStr2]){
            
            // if (diffFound){
            //     std::cout << "FAIL";
            //     return 0;                
            // }

            // diffFound = true;
            if (strLen1 > strLen2)
                ++shiftStr1;
            else if (strLen1 < strLen2)    
                ++shiftStr2;
            else{
                ++shiftStr1;
                ++shiftStr2;
            }

            if (str1.substr(i + shiftStr1, str1.size() - (i + shiftStr1)) == str2.substr(i + shiftStr2, str2.size() - (i + shiftStr2)))
                std::cout << "OK";
            else
                std::cout << "FAIL";

            return 0; 
        }
    }

    std::cout << "OK";

    return 0;
}