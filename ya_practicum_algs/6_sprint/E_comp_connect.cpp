#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int component_count = 1;

struct Vertexes{
    int vertexCount = 0;
    std::vector<int> vertexes;
};

typedef std::vector<int> Colors;
typedef std::vector<Vertexes> VertexesVector;

void startDfs(VertexesVector& vertexesVector, Colors& color);
void Dfs(VertexesVector& vertexesVector, Colors& color, int v);
void startDfsFromVertex(VertexesVector& vertexesVector, int startVertex, Colors& color);

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

    // int startVectice;
    // std::cin >> startVectice;

    Colors color(n+1);
    for(auto it = color.begin(); it!=color.end(); ++it)
        *it = -1;

    //startDfsFromVertex(vertexesVector, startVectice, color);
    startDfs(vertexesVector, color);

    // for (int i=1; i<n+1; ++i){
    //     std::cout << result[i].vertexCount;
    //     for (int j=0; j<result[i].vertexes.size(); ++j)
    //         std::cout << " " << result[i].vertexes[j];
    //     std::cout << "\n";
    // }

    std::cout << component_count-2 << "\n";

    // int componentNum = 2;
    // for (int i=1; i<color.size(); ++i){

    //     if (componentNum != color[i])
    //         std::cout << "\n";

    //     std::cout << i << " ";

    //     componentNum = color[i];

    // }

    for (int compNum = 2; compNum < component_count; compNum++)
    {
        for (int j = 1; j < color.size(); j++)
        {
            if (color[j] != compNum)
                continue;
            std::cout << j << " ";
        }
        std::cout << "\n";        
    }

    return 0;
}

void startDfsFromVertex(VertexesVector& vertexesVector, int startVertex, Colors& color){
    std::cout << startVertex << " ";
        Dfs(vertexesVector, color, startVertex); // Запускаем обход, стартуя с i-й вершины.
}

void startDfs(VertexesVector& vertexesVector, Colors& color){
    for (int i = 0; i < color.size(); ++i) {
        // Перебираем варианты стартовых вершин, пока они существуют.
        if (color[i] == -1){
            Dfs(vertexesVector, color, i); // Запускаем обход, стартуя с i-й вершины.
            ++component_count;
        }
    }
}

void Dfs(VertexesVector& vertexesVector, Colors& color, int v) { // v - номер вершины
    color[v] = 0; // Вершина посещена, но ещё не обработана.
    //for (int w : outgoing_edges(v)) { // Получите список исходящих ребер в зависимости от способа хранения графа
    for (int w : vertexesVector[v].vertexes) { // Получите список исходящих ребер в зависимости от способа хранения графа
        if (color[w] == -1){ // Если вершина не посещена, то
            //std::cout << w << " ";
            Dfs(vertexesVector, color, w); // запустим обход от найденной смежной вершины.
        }
    }
    color[v] = component_count; // Теперь вершина обработана.
    // std::cout << v;
}
