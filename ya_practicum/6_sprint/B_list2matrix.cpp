#include <iostream>
#include <vector>

int main(){

    int n=0;
    int m=0;
    std::cin >> n >> m;

    std::vector<std::vector<int>> result(n);
    for (int i=0; i<n; ++i)
        result[i].resize(n);

    int u=0;
    int v=0;
    for (int i=0; i<m; ++i){
        std::cin >> u >> v;
        result[--u][--v] = 1;
    }

    for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j){
            std::cout << result[i][j] << " ";
        }
        std::cout << "\n";
    }

    return 0;
}