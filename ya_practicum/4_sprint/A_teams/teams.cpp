#include <iostream>
#include <unordered_map>
#include <vector>

int main(){

    std::unordered_map<std::string, int> uniqTeams;

    int n;
    std::cin >> n;

    std::cin.ignore();
    std::string team;
    std::vector<std::string> teams;
    for (int i=0; i<n; ++i){
        std::getline(std::cin, team);
        if (uniqTeams.find(team) == uniqTeams.end()){
            teams.push_back(team);
            uniqTeams[team] = 0;
        }
    }

    for (int i=0; i<teams.size(); ++i)
        std::cout << teams[i] << '\n';

    return 0;
}