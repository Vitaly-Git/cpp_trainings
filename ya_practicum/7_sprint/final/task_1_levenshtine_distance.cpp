#include <iostream>
#include <vector>
#include <string>

int main(){

    // std::vector<char> word1;
    // std::vector<char> word2;

    std::string word1;
    std::string word2;

    std::getline(std::cin, word1);
    std::getline(std::cin, word2);

    std::vector< std::vector<int> > rowsByWord1(word1.size());

    for (int i=0; i<word1.size(); ++i)
        rowsByWord1[0] = std::vector<int>(word2.size());

    for (int y=0; y<word1.size(); ++y){
        for (int x=0; x<word2.size(); ++x){
            
        }
    }


    return 0;
}