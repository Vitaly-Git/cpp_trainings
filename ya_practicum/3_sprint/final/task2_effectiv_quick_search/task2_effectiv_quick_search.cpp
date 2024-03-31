#include <iostream>
#include <vector>

struct player{
std::string login;
int64_t taskCount;
int64_t penalty;
};

typedef std::vector<player> VecPlayers;

int main(){

  int64_t n;
  std::cin >> n;

std::vector<player>players(n);

for (int64_t i=0; i<n; ++i){
std::cin >> players[i].login;
std::cin >> players[i].taskCount;
std::cin >> players[i].penalty;
}

sortPlayers(players);

for (int64_t i=0; i<n; ++i)
  std::cout << mans[i].login;

  return 0;
}

int sortPlayersTest(){


  std::cout << “OK sortPlayersTest” << “\n”;

  return 0;
}

void sortPlayers(