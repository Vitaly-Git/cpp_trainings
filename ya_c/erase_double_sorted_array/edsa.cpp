#include <iostream>

int main(){

    int64_t n=0;
    std::cin >> n;
    
    int64_t prevValue = 0;
    int64_t inputValue = 0;

    for(int64_t i=0;i<n;++i){
        std::cin >> inputValue;
        
        if(i==0)
            prevValue = inputValue;
        else if (prevValue == inputValue)
            continue;
        
        std::cout << inputValue << std::endl;
        
        prevValue = inputValue;
    }
        
    return 0;
}
