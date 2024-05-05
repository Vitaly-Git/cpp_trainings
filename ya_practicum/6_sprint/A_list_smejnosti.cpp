#include <iostream>
#include <vector>

struct Vertexes{
    int vertexCount = 0;
    std::vector<int> vertexes;
};

int main(){

    int n=0;
    int m=0;
    std::cin >> n >> m;

    std::vector<Vertexes> result(n+1);

    int u,v;
    for (int idxEdge = 0; idxEdge<m; ++idxEdge){
        std::cin >> u >> v;
        ++(result[u].vertexCount);
        result[u].vertexes.push_back(v);
    }

    for (int i=1; i<n+1; ++i){
        std::cout << result[i].vertexCount;
        for (int j=0; j<result[i].vertexes.size(); ++j)
            std::cout << " " << result[i].vertexes[j];
        std::cout << "\n";
    }

    return 0;
}