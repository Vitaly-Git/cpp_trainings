#include <iostream>
#include <map>

int main(){

    int res = 0;

    std::string str1;
    std::string str2;

    std::cin >> str1 >> str2;

    if (str1.size()!=str2.size()){
        res = 0;
        std::cout << res;
        return 0;
    }

    std::map<char, int64_t> freeLettersCount;

    for(int i=0; i<str1.size(); ++i){
        ++freeLettersCount[str1[i]];
        --freeLettersCount[str2[i]];
    }

    for(auto it=freeLettersCount.begin(); it!=freeLettersCount.end(); ++it)
        if(it->second==0){
            res=1;
        }else{
            res=0;
            break;
        }

    std::cout << res;

    return 0;
}


