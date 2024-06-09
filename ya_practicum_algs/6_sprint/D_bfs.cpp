#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <queue>

struct Vertexes{
    int vertexCount = 0;
    std::vector<int> vertexes;
};

typedef std::vector<std::string> Colors;
typedef std::vector<Vertexes> VertexesVector;

void bfs(VertexesVector& vertexesVector, int s, Colors& color, 
    std::vector<int>& previous, std::vector<int>& distance);

int main(){

    int n=0;
    int m=0;
    std::cin >> n >> m;

    VertexesVector vertexesVector(n+1);

    int u,v;
    for (int idxEdge = 0; idxEdge<m; ++idxEdge){
        std::cin >> u >> v;
        ++(vertexesVector[u].vertexCount);
        vertexesVector[u].vertexes.push_back(v);
        // Граф не ориентированный, поэтому добавим два вектора
        ++(vertexesVector[v].vertexCount);
        vertexesVector[v].vertexes.push_back(u);        
    }

    for (int idxVertex = 0; idxVertex<=n; ++idxVertex){
        std::sort(vertexesVector[idxVertex].vertexes.begin(), vertexesVector[idxVertex].vertexes.end());        
    }   

    int startVectice;
    std::cin >> startVectice;

    Colors color(n+1);
    for(auto it = color.begin(); it!=color.end(); ++it)
        *it = "white";

    std::vector<int> previous(n+1);
    std::vector<int> distance(n+1);

    //startDfsFromVertex(vertexesVector, startVectice, color);

    bfs(vertexesVector, startVectice, color, previous, distance);

    // for (int i=1; i<n+1; ++i){
    //     std::cout << result[i].vertexCount;
    //     for (int j=0; j<result[i].vertexes.size(); ++j)
    //         std::cout << " " << result[i].vertexes[j];
    //     std::cout << "\n";
    // }

    return 0;
}


// Длины массивов равны числу вершин |V|.
//vector<string> color = {"white", "white", ...};


void bfs(VertexesVector& vertexesVector, int s, Colors& color, 
    std::vector<int>& previous, std::vector<int>& distance) {

    // Создадим очередь вершин и положим туда стартовую вершину.
    std::queue<int> planned;
    planned.push(s);
    color[s] = "gray";
    distance[s] = 0;

    while (!planned.empty()) {
        int u = planned.front();  // Возьмём вершину из очереди.
        planned.pop();

        for (int v : vertexesVector[u].vertexes) {
            if (color[v] == "white") {
                // Серые и чёрные вершины уже
                // либо в очереди, либо обработаны.
                distance[v] = distance[u] + 1;
                previous[v] = u;
                color[v] = "gray";
                planned.push(v);  // Запланируем посещение вершины.
            }
        }

        std::cout << u << " ";
        color[u] = "black";  // Теперь вершина считается обработанной.
    }
}

// vector<int> shortest_path(int v) {
//     // Класть вершины будем в стек, тогда
//     // стартовая вершина окажется наверху стека
//     // и порядок следования от s до v будет соответствовать
//     // порядку извлечения вершин из стека.
//     vector<int> path;
//     int current_vertex = v;

//     while (current_vertex != -1) {
//         // Предшественник вершины s равен -1.
//         path.push_back(current_vertex);
//         current_vertex = previous[current_vertex];
//     }

//     return path;
// }