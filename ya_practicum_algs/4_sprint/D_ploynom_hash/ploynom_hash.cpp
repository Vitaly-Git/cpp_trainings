#include <iostream>

u_int64_t getPolynomeHash(const u_int64_t& base, const u_int64_t& mod, 
    const std::string& srcStr);

int main(){

    u_int64_t base;
    u_int64_t mod;
    std::cin >> base >> mod;

    std::string srcStr;
    std::cin.ignore();
    std::getline(std::cin, srcStr);

    std::cout << getPolynomeHash(base, mod, srcStr);

    return 0;
}

u_int64_t getPolynomeHash(const u_int64_t& base, const u_int64_t& mod, 
    const std::string& srcStr){

    u_int64_t hash = 0;
    u_int64_t lsrcStrLen = srcStr.size();
    u_int64_t pwrBase = 1;

    for (u_int64_t i=lsrcStrLen-1; i>=0 && i<lsrcStrLen; --i){
        char curChr = srcStr[i];
        hash = (hash + curChr * pwrBase) % mod;
        pwrBase = (pwrBase * base) % mod;
    }

    return hash;
}