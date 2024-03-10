#include <iostream>
#include <cassert>
#include <cmath>

void footballTest();
int footballScore(const std::string scoreGame1, const std::string scoreGame2, const int8_t guestGameMarker);
int footballScoreV1(const std::string scoreGame1, const std::string scoreGame2, const int8_t guestGameMarker);

int main(){
    footballTest();    

    // std::string scoreGame1;
    // std::string scoreGame2;
    // std::string guestGameMarkerStr;

    // std::cin >> scoreGame1 >> scoreGame2 >> guestGameMarkerStr;
    // std::cout << footballScore(scoreGame1, scoreGame2, std::stoi(guestGameMarkerStr));

    return 0;
}

void footballTest(){
    assert(footballScore("0:0","0:0",1)==1);
    assert(footballScore("0:2","0:3",1)==5);
    assert(footballScore("0:2","0:3",2)==6);
    assert(footballScore("2:2","0:3",1)==4);
    assert(footballScore("2:2","0:3",2)==4);
    assert(footballScore("2:2","3:0",1)==0);
    assert(footballScore("2:2","3:0",2)==0);
    assert(footballScore("2:2","3:3",1)==1);
    assert(footballScore("2:2","3:3",2)==1);
    assert(footballScore("0:2","5:3",1)==0);
    assert(footballScore("0:2","5:3",2)==1);
    assert(footballScore("5:2","0:1",1)==0);
    assert(footballScore("5:2","0:1",2)==0);
    assert(footballScore("3:2","2:4",1)==1);
    assert(footballScore("3:2","2:4",2)==2);
    assert(footballScore("4:1","1:4",1)==1);
    assert(footballScore("4:1","1:4",2)==1);
    assert(footballScore("0:1","1:3",1)==3);
    assert(footballScore("0:1","1:3",2)==4);
    assert(footballScore("4:4","1:4",1)==4);
    assert(footballScore("4:4","1:4",2)==4);
    assert(footballScore("2:1","1:3",1)==1);
    assert(footballScore("2:1","1:3",2)==2);
    assert(footballScore("0:1","0:3",1)==4);
    assert(footballScore("0:1","0:3",2)==5);
    assert(footballScore("5:0","0:0",1)==0);
    assert(footballScore("5:0","0:0",2)==0);
    assert(footballScore("5:0","1:2",1)==0);
    assert(footballScore("5:0","1:2",2)==0);
    assert(footballScore("2:0","1:3",1)==0);
    assert(footballScore("2:0","1:3",2)==1);
    // assert(footballScore("1:4","0:0",1)==4);
    assert(footballScore("1:4","0:0",2)==3);

    std::cout << "OK footballTest" << std::endl;
}


int footballScore(const std::string scoreGame1, const std::string scoreGame2, const int8_t guestGameMarker){

    int scoreNeeded = 0;

    int8_t game1GoalsTeam1 = scoreGame1[0] - '0';
    int8_t game1GoalsTeam2 = scoreGame1[2] - '0';
    int8_t game2GoalsTeam1 = scoreGame2[0] - '0';
    int8_t game2GoalsTeam2 = scoreGame2[2] - '0';
    int8_t guestGoalsTeam1 = guestGameMarker == 2 ? game1GoalsTeam1 : game2GoalsTeam1;
    int8_t guestGoalsTeam2 = guestGameMarker == 1 ? game1GoalsTeam2 : game2GoalsTeam2;

    if ((game1GoalsTeam1 + game2GoalsTeam1) > (game1GoalsTeam2 + game2GoalsTeam2))
        return 0;

    if ((game1GoalsTeam1 + game2GoalsTeam1) == (game1GoalsTeam2 + game2GoalsTeam2))
        return 1;
        // if (guestGoalsTeam1 < guestGoalsTeam2)
        //     return guestGoalsTeam2 - guestGoalsTeam1;
        // else
        //     return 0;    

    if ((game1GoalsTeam1 == game2GoalsTeam2) && (game1GoalsTeam2 == game2GoalsTeam1))
        return 1;

    int8_t diffGoalsGame1 = game1GoalsTeam2 - game1GoalsTeam1;
    int8_t diffGoalsGame2 = game2GoalsTeam2 - game2GoalsTeam1;

    if (diffGoalsGame1 == 0)
        scoreNeeded = diffGoalsGame2 + 1;
    else
        scoreNeeded = diffGoalsGame2 + diffGoalsGame1 + (guestGameMarker - 1);

    scoreNeeded = std::max(scoreNeeded, 0);

    return scoreNeeded;
}

int footballScoreV1(const std::string scoreGame1, const std::string scoreGame2, const int8_t guestGameMarker){

    int scoreNeeded = 0;

    int8_t game1GoalsTeam1 = scoreGame1[0] - '0';
    int8_t game1GoalsTeam2 = scoreGame1[2] - '0';
    int8_t game2GoalsTeam1 = scoreGame2[0] - '0';
    int8_t game2GoalsTeam2 = scoreGame2[2] - '0';

    if ((game1GoalsTeam1 + game2GoalsTeam1) > (game1GoalsTeam2 + game2GoalsTeam2))
        return 0;

    if ((game1GoalsTeam1 == game2GoalsTeam2) && (game1GoalsTeam2 == game2GoalsTeam1))
        return 1;

    int8_t diffGoalsGame1 = game1GoalsTeam2 - game1GoalsTeam1;
    int8_t diffGoalsGame2 = game2GoalsTeam2 - game2GoalsTeam1;

    if (diffGoalsGame1 < 0)
        scoreNeeded = diffGoalsGame2 + diffGoalsGame1 + (guestGameMarker - 1); // 1; //(guestGameMarker==2 ? 0 : 1);
    else if (diffGoalsGame1 == 0)
        scoreNeeded = diffGoalsGame2 + 1;
    else
        scoreNeeded = diffGoalsGame2 + diffGoalsGame1 + (guestGameMarker - 1);

    scoreNeeded = std::max(scoreNeeded, 0);

    return scoreNeeded;
}