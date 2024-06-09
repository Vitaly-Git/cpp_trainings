#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

int main(){

    int n;
    std::cin >> n;

    std::vector<std::string> words(n);
    for(int i=0; i<n; ++i){
        std::cin >> words[i];
        std::sort(words[i].begin(), words[i].end());
    }

    std::map<std::string, int> anagramsInVector;
    std::vector<std::vector<int>> anagramPos;
    for (int i=0; i<n; ++i)
        if (anagramsInVector.find(words[i]) == anagramsInVector.end()){
            anagramPos.push_back({i});
            anagramsInVector[words[i]] = anagramPos.size()-1;
        } else {
            anagramPos[anagramsInVector[words[i]]].push_back(i);
        }

    std::sort(anagramPos.begin(), anagramPos.end());

    for (int i=0; i<anagramPos.size(); ++i){
        std::sort(anagramPos[i].begin(), anagramPos[i].end());
        for (auto idx : anagramPos[i])
            std::cout << idx << " ";
        std::cout << '\n';
    }

    return 0;
}