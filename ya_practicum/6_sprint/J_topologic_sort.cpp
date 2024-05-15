#include <iostream>
#include <vector>
#include <stack>
#include <iterator>
#include <algorithm>

struct Vertexes{
    int vertexCount = 0;
    std::vector<int> vertexes;
};

typedef std::vector<std::string> Colors;
typedef std::vector<Vertexes> VertexesVector;

std::stack<int> order; // В этом стеке будет записан порядок обхода.

void topSort(VertexesVector& vertexesVector, Colors& color, int v) {
    color[v] = "gray";
    for (int w : vertexesVector[v].vertexes) {
        if (color[w] == "white") {
            // std::cout << w << " ";
            topSort(vertexesVector, color, w);
        }
    }
    color[v] = "black";
    order.push(v); // Кладём обработанную вершину в стек.
}

void mainTopSort(VertexesVector& vertexesVector, Colors& color) {
    for (int i = 1; i < vertexesVector.size(); ++i) {
        if (color[i] == "white") {
            topSort(vertexesVector, color, i);
        }
    }
} 

int main(){

    int n=0;
    int m=0;
    std::cin >> n >> m;

    VertexesVector vertexesVector(n+1);

    int u,v;
    for (int idxEdge = 0; idxEdge<m; ++idxEdge){
        std::cin >> v >> u;
        ++(vertexesVector[u].vertexCount);
        vertexesVector[u].vertexes.push_back(v);
    }

    // for (int idxVertex = 0; idxVertex<=n; ++idxVertex){
    //     std::sort(vertexesVector[idxVertex].vertexes.begin(), vertexesVector[idxVertex].vertexes.end());        
    // }   

    // int startVectice;
    // std::cin >> startVectice;

    Colors color(n+1);
    for(auto it = color.begin(); it!=color.end(); ++it)
        *it = "white";

    // startDfsFromVertex(vertexesVector, startVectice, color);
    mainTopSort(vertexesVector, color);

    // for (int i=1; i<n+1; ++i){
    //     std::cout << vertexesVector[i].vertexCount;
    //     for (int j=0; j<vertexesVector[i].vertexes.size(); ++j)
    //         std::cout << " " << vertexesVector[i].vertexes[j];
    //     std::cout << "\n";
    // }


    // for (int i=1; i<n+1; ++i){
    //     std::cout << result[i].vertexCount;
    //     for (int j=0; j<result[i].vertexes.size(); ++j)
    //         std::cout << " " << result[i].vertexes[j];
    //     std::cout << "\n";
    // }

    return 0;
}
