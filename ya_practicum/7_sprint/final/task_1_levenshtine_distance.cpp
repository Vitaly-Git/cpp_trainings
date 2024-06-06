#include <iostream>
#include <vector>
#include <string>

int main(){

    std::string word1;
    std::string word2;

    // Ввод данных
    std::getline(std::cin, word1);
    std::getline(std::cin, word2);

    // Инициализация матрицы расстояний
    std::vector< std::vector<int> > rowsByWord1(word1.size()+1);
    for (int i=0; i<=word1.size(); ++i){
        rowsByWord1[i] = std::vector<int>(word2.size()+1);
        rowsByWord1[i][0] = i;
    }
    for (int i=0; i<=word2.size(); ++i)
        rowsByWord1[0][i] = i;
        
    // Расчет матрицы расстояний
    for (int y=1; y<=word1.size(); ++y){
        for (int x=1; x<=word2.size(); ++x){
            
            int distLocal = 0;
            
            int leftVal = rowsByWord1[y][x-1] + 1;
            int leftTopVal = rowsByWord1[y-1][x-1] + (word1[y-1] == word2[x-1] ? 0 : 1);
            int toptVal = rowsByWord1[y-1][x] + 1;

            distLocal = std::min(leftVal, leftTopVal);
            distLocal = std::min(distLocal, toptVal);

            rowsByWord1[y][x] = distLocal;
        }
    }

    std::cout << rowsByWord1[word1.size()][word2.size()];

    return 0;
}