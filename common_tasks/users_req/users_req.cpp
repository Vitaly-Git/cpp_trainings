#include <iostream>
#include <map>
#include <string>

typedef ulong TimeStamp;
typedef std::string Token;

struct UserReqRate{
    long lastSec = 0;
    long reqInLastSec = 0;
};

int main(){

    long n;
    long k;
    std::map<Token, UserReqRate> usersLastReq;

    std::cin >> n >> k;

    for (ulong i=0; i<k; ++i){

        TimeStamp timeStamp;
        Token userToken;

        std::cin >> timeStamp;
        std::cin >> userToken;

        long lastSec = usersLastReq[userToken].lastSec;
        long curSec = timeStamp - (timeStamp % 1000);

        if (lastSec != curSec){
            std::cout << timeStamp << " " << userToken << '\n';
            usersLastReq[userToken].lastSec = curSec;            
            usersLastReq[userToken].reqInLastSec=1;
        } else if (lastSec == curSec && usersLastReq[userToken].reqInLastSec < n){
            std::cout << timeStamp << " " << userToken << '\n';
            usersLastReq[userToken].lastSec = curSec;            
            usersLastReq[userToken].reqInLastSec++;
        }
    }

    return 0;
}