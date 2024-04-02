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

//#define UNIT_TESTING

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

struct PointersPos{
  int lhp;
  int rhp;
};

typedef std::vector<Player> VecPlayers;

void sortPlayers(VecPlayers& players);
int sortPlayersTest();
void quickSortInPlace(VecPlayers& players, int lhp, int rhp);
PointersPos partitionInPlace(VecPlayers& players, int lhp, int rhp, int pivot);

int main(){

  #ifdef UNIT_TESTING
    return sortPlayersTest();
  #endif

  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  int n;
  std::cin >> n;

  VecPlayers players(n);
  for (int i=0; i<n; ++i){
    std::cin >> players[i].login;
    std::cin >> players[i].taskCount;
    std::cin >> players[i].penalty;
  }

  sortPlayers(players);

  for (int i=0; i<n; ++i)
    std::cout << players[i].login << '\n';

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

  std::cout << "OK sortPlayersTest" << "\n";
  return 0;
}

void sortPlayers(VecPlayers& players){
  quickSortInPlace(players, 0, players.size()-1);
}

void quickSortInPlace(VecPlayers& players, int lhp, int rhp){
    
  if (rhp-lhp < 1)
      return;

  // srand(time(0));
  int pivot = players[rand() % (rhp-lhp) + lhp].taskCount;
  PointersPos pPos = partitionInPlace(players, lhp, rhp, pivot);
  
  quickSortInPlace(players, 0, pPos.lhp);
  quickSortInPlace(players, pPos.lhp+1, rhp);
}

PointersPos partitionInPlace(VecPlayers& players, int lhp, int rhp, int pivot) {
    
  bool lhpStop = false;
  bool rhpStop = false;

  while (lhp<rhp){
    
    // Player playerL = players[lhp];
    // Player playerR = players[rhp];


    // if (playerL.taskCount > pivot)
    //   ++lhp;
    // else if (playerR.taskCount < pivot)
    //   --rhp;
    // else if ((playerL.taskCount == pivot) && (playerR.taskCount == pivot)) {
      
    //   if (playerL.penalty > playerR.penalty){
    //     std::swap(players[lhp], players[rhp]);  
    //     --rhp;
    //   }else if (playerL.penalty == playerR.penalty){
    //     if (playerL.login > playerR.login){
    //       std::swap(players[lhp], players[rhp]);  
    //       --rhp;
    //     }else{
    //       --rhp; //++lhp;
    //     }
    //   } else {
    //     --rhp; //++lhp;
    //   }

    // }else  
    //   std::swap(players[lhp], players[rhp]);


    if (players[lhp].taskCount > pivot)
      ++lhp;
    else if (players[rhp].taskCount < pivot)
      --rhp;
    else if ((players[lhp].taskCount == pivot) && (players[rhp].taskCount == pivot)) {
      
      if (players[lhp].penalty > players[rhp].penalty){
        std::swap(players[lhp], players[rhp]);  
        --rhp;
      }else if (players[lhp].penalty == players[rhp].penalty){
        if (players[lhp].login > players[rhp].login){
          std::swap(players[lhp], players[rhp]);  
          --rhp;
        }else{
          --rhp; //++lhp;
        }
      } else {
        --rhp; //++lhp;
      }

    }else  
      std::swap(players[lhp], players[rhp]);
  }

  return {lhp, rhp};
}
