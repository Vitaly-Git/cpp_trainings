/*
1. Порядок сортировки:
1.1. При сравнении двух участников выше будет идти тот, у которого решено больше
     задач. 
1.2. При равенстве числа решённых задач первым идёт участник с меньшим штрафом. 
1.3. Если же и штрафы совпадают, то первым будет тот, у которого логин идёт 
     раньше в алфавитном (лексикографическом) порядке.

1. Для технической реализации задачи можно воспользоваться функцией стандартной
   библиотеки std::sort с созданием компаратора в соответствии с требуемыми 
   условиями. Но в нашем случаем исключаем этот вариант, т.к. сортировку необходимо
   реализовать самостоятельно.
2. Для реализации задачи нам необходимо хранилище данных в виде таблицы состоящей
   из записей или набора кортежей, которые мы сможем сортировать по полям.
3. Выберем в качестве хранилища вектор структур, как наиболее понятный и 
   структурирванный.
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <chrono>

//#define UNIT_TESTING
//#define PROFILING

struct Player{
  std::string login;
  int taskCount;
  int penalty;
};

bool operator==(const Player& lhs, const Player& rhs)
{
  return lhs.login == rhs.login && 
         lhs.taskCount == rhs.taskCount && 
         lhs.penalty == rhs.penalty;
}

typedef std::vector<Player> VecPlayers;

int sortPlayersTest();
void sortPlayers(VecPlayers& players);
void quickSortInPlace(VecPlayers& players, int lhp, int rhp);
int partitionInPlace(VecPlayers& players, int lhp, int rhp, int pivot);

class TimeSpent{
  private:
    std::chrono::system_clock::time_point time_start;
    std::chrono::system_clock::time_point time_finish;

  public:
    TimeSpent(){
      time_start = std::chrono::high_resolution_clock::now();
    }
    ~TimeSpent(){
      time_finish = std::chrono::high_resolution_clock::now();
      auto time_span = std::chrono::duration_cast<std::chrono::duration<double>>(time_finish - time_start);
      std::cout << time_span.count() << " seconds\n";
    }    
};

int main(){

  #ifdef UNIT_TESTING
    return sortPlayersTest();
  #endif

  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  int n;
  std::cin >> n;

  VecPlayers players(n);

  {
    #ifdef PROFILING
      TimeSpent ts;
    #endif
    for (int i=0; i<n; ++i)
      std::cin >> players[i].login >> players[i].taskCount >> players[i].penalty;
  }

  {
    #ifdef PROFILING
      TimeSpent ts;
    #endif
    sortPlayers(players);
  }

  {
    #ifdef PROFILING
      TimeSpent ts;
    #endif
    for (int i=0; i<n; ++i)
      std::cout << players[i].login << '\n';
  }

  return 0;
}

int sortPlayersTest(){

  VecPlayers players;
  VecPlayers playersAfterSort;

  players = {
    {"alla", 4, 100},
    {"gena", 4, 1000},
    {"gosha", 4, 90},
    {"rita", 4, 90},
    {"timofey", 4, 80},
  };
  playersAfterSort = {
    {"timofey", 4, 80},
    {"gosha", 4, 90},
    {"rita", 4, 90},
    {"alla", 4, 100},
    {"gena", 4, 1000}
  };
  sortPlayers(players);
  assert(players == playersAfterSort);

  players = {
    {"alla", 5, 100},
    {"gena", 4, 1000},
    {"gosha", 4, 90},
    {"rita", 1, 90},
    {"timofey", 2, 80}
  };
  playersAfterSort = {
    {"alla", 5, 100},
    {"gosha", 4, 90},
    {"gena", 4, 1000},
    {"timofey", 2, 80},
    {"rita", 1, 90}
  };
  sortPlayers(players);
  assert(players == playersAfterSort);

  players = {
    {"rita", 1, 90},
    {"alla", 4, 100},
    {"gosha", 2, 90},
    {"timofey", 5, 80},
    {"gena", 6, 1000}
  };
  playersAfterSort = {
    {"gena", 6, 1000},
    {"timofey", 5, 80},
    {"alla", 4, 100},
    {"gosha", 2, 90},
    {"rita", 1, 90},
  };
  sortPlayers(players);
  assert(players == playersAfterSort);

  players = {
    {"alla", 4, 100},
    {"gena", 6, 1000},
    {"gosha", 2, 90},
    {"rita", 2, 90},
    {"timofey", 4, 80},
  };
  playersAfterSort = {
    {"gena", 6, 1000},
    {"timofey", 4, 80},
    {"alla", 4, 100},
    {"gosha", 2, 90},
    {"rita", 2, 90},
  };
  sortPlayers(players);
  assert(players == playersAfterSort);

  players = {
    {"alla", 0, 0},
    {"gena", 0, 0},
    {"gosha", 0, 0},
    {"rita", 0, 0},
    {"timofey", 0, 0},
  };
  playersAfterSort = {
    {"alla", 0, 0},
    {"gena", 0, 0},
    {"gosha", 0, 0},
    {"rita", 0, 0},
    {"timofey", 0, 0},
  };
  sortPlayers(players);
  assert(players == playersAfterSort);

 players = {
    {"alpyx", 3, 49},
    {"qly", 62, 28},
    {"cpbablljhrnlejcwq", 45, 32},
    {"yusoldfqnjlvwrcruts", 81, 39},
    {"kzmleudk", 52, 89},
    {"hpnpszayf", 4, 12},
    {"ojywnxuyqgmf", 54, 31},
    {"tvomvisbqrflkghnojt", 49, 79},
    {"yc", 17, 84},
    {"k", 16, 14},
    {"dgmqeqezjgzxfwhcn", 68, 21},
    {"zdbonelpgmbou", 47, 64},
    {"ehtxaytzgcsim", 21, 66},
    {"burbwymmeal", 56, 80},
    {"wqzynngqasdjj", 8, 15},
    {"auirlnkhxtmmytr", 23, 14},
    {"poypocw", 0, 72},
    {"uf", 40, 68},
    {"ezfetpflzoi", 0, 30},
    {"ygegvjzlfgumbo", 80, 33},
    {"rcwp", 8, 30},
    {"oaes", 7, 59},
    {"zgbktifgwvsgesleqclp", 4, 8},
    {"knzsujegjqmer", 99, 72}
  };
  sortPlayers(players);

  std::cout << "OK sortPlayersTest" << "\n";
  return 0;
}

void sortPlayers(VecPlayers& players){
  quickSortInPlace(players, 0, players.size()-1);
}

void quickSortInPlace(VecPlayers& players, int lhp, int rhp){
    
  if (rhp-lhp < 1)
      return;

  srand(time(0));
  int pivot = players[rand() % (rhp-lhp) + lhp].taskCount;
  int newLhp = partitionInPlace(players, lhp, rhp, pivot);
  
  quickSortInPlace(players, lhp, newLhp);
  quickSortInPlace(players, newLhp+1, rhp);
}

int partitionInPlace(VecPlayers& players, int lhp, int rhp, int pivot) {
    
  while (lhp<rhp){

    bool ptrsWasChange = false;
    if (players[lhp].taskCount > pivot){
      ++lhp;
      ptrsWasChange = true;
    }
    if (players[rhp].taskCount < pivot){
      --rhp;
      ptrsWasChange = true;
    }

    if (ptrsWasChange)
      continue;

    if ((players[lhp].taskCount == pivot) && (players[rhp].taskCount == pivot)) {
      
      if (players[lhp].penalty > players[rhp].penalty){
        std::swap(players[lhp].login, players[rhp].login);  
        std::swap(players[lhp].penalty, players[rhp].penalty);  
        --rhp;
      }else if (players[lhp].penalty == players[rhp].penalty){
        if (players[lhp].login > players[rhp].login){
          std::swap(players[lhp].login, players[rhp].login);
          --rhp;
        }else{
          --rhp;
        }
      } else {
        --rhp;
      }

    }else  
      std::swap(players[lhp], players[rhp]);
  }

  return lhp;
}
