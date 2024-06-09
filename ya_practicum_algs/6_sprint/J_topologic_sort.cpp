#include <iostream>
#include <vector>
#include <stack>
#include <iterator>
#include <algorithm>
#include <set>

struct Vertexes{
    int verticeNum = 0;
    int vertexCount = 0;
    std::vector<int> vertexes;
};

typedef std::vector<std::string> Colors;
typedef std::vector<Vertexes> VertexesVector;

std::stack<int> order; // В этом стеке будет записан порядок обхода.

void topSort(VertexesVector& vertexesVector, Colors& color, int v) {
    // if (color[v] == "black")
    //     return;
    
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

std::set<int> connectedVertices;

void mainTopSort(VertexesVector& vertexesVector, Colors& color) {
    
    for (int i = 1; i < vertexesVector.size(); ++i) {
        if (connectedVertices.find(i) == connectedVertices.end()){
            color[i] = "black";
            order.push(i);
        }
    }
    
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
        vertexesVector[u].verticeNum = u;
        ++(vertexesVector[u].vertexCount);
        vertexesVector[u].vertexes.push_back(v);
        connectedVertices.insert(u);
        connectedVertices.insert(v);
    }

    // std::sort(vertexesVector.begin(), vertexesVector.end(), [](Vertexes& lhs, Vertexes& rhs){
    //         if (lhs.vertexCount==0 && rhs.vertexCount==0)
    //             return lhs.verticeNum < rhs.verticeNum;
    //         else if (lhs.vertexCount==0)
    //             return true;
    //         else if (rhs.vertexCount==0)
    //             return false;
    //         else 
    //             return lhs.verticeNum < rhs.verticeNum;
    //     });


    // for (int idxVertex = 0; idxVertex<=n; ++idxVertex){
    //     std::sort(vertexesVector[idxVertex].vertexes.begin(), vertexesVector[idxVertex].vertexes.end());        
    // }   

    // int startVectice;
    // std::cin >> startVectice;

    Colors color(n+1);
    for(auto it = color.begin(); it!=color.end(); ++it)
        *it = "white";

    //std::reverse(vertexesVector.begin(), vertexesVector.end());

    // startDfsFromVertex(vertexesVector, startVectice, color);
    mainTopSort(vertexesVector, color);

    // for (int i=1; i<n+1; ++i){
    //     std::cout << vertexesVector[i].vertexCount;
    //     for (int j=0; j<vertexesVector[i].vertexes.size(); ++j)
    //         std::cout << " " << vertexesVector[i].vertexes[j];
    //     std::cout << "\n";
    // }

    std::vector<int> result; 

    for (int i=1; i<n+1; ++i){
        result.push_back(order.top());
        order.pop();
    }

    for (int i=n-1; i>=0; --i)
        std::cout << result[i] << " ";

    return 0;
}
