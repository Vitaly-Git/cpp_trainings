// Расчет барл тут:
// https://github.com/fuodorov/yaalgorithms/blob/main/sprint_4/crash_polynomial_hash.py

#include <iostream>
#include <map>

u_int64_t getHash(std::string srcStr);
void findEqualsHashString();
std::string getRandomString(int strLen);

std::string alphabit = "abcdefghijklmnopqrstuvwxyz";
int alphabit_len = alphabit.size();

int main(){

    std::cout << getHash("ezhgeljkablzwnvuwqvp") << '\n';
    std::cout << getHash("gbpdcvkumyfxillgnqrv") << '\n';

    findEqualsHashString();

    return 0;
}

void findEqualsHashString(){

    std::map<u_int64_t, std::string> hashs;

    for (int strLen=900; strLen<1000; ++strLen){
        for (int testCntForStrLen = 0; testCntForStrLen<1000; ++testCntForStrLen){

            std::string rndStr = getRandomString(strLen);
            u_int64_t hashStr = getHash(rndStr);

            if (hashs.find(hashStr) != hashs.end()){
                std::cout << hashs[hashStr] << " - " << hashStr << '\n';
                std::cout << rndStr << " - " << hashStr << '\n';
                return;
            }else{
                hashs[hashStr] = rndStr;
            }
        }
    }
}

std::string getRandomString(int strLen){

    std::string rndStr;

    for (int i=0; i<strLen; ++i)
        rndStr = rndStr + alphabit[rand() % alphabit_len];

    return rndStr;
}

u_int64_t getHash(std::string srcStr){

    u_int64_t s = 0;
    u_int64_t a = 1000;
    u_int64_t m = 123987123;
    u_int64_t l = srcStr.size();
    u_int64_t p = 1;

    for (u_int64_t n=l-1; n>=0 && n<l; --n){
        char c = srcStr[n];
        s = (s + c * p) % m;
        p = (p * a) % m;
    }

    return s;
}
