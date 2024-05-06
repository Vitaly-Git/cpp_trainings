#include <iostream>
#include <vector>
#include <iterator>

struct Vertexes{
    int vertexCount = 0;
    std::vector<int> vertexes;
};

typedef std::vector<std::string> Colors;
typedef std::vector<Vertexes> VertexesVector;

void startDfs(VertexesVector& vertexesVector, Colors& color);
void Dfs(VertexesVector& vertexesVector, Colors& color, int v);

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
    }

    Colors color(n);
    for(auto it = color.begin(); it!=color.end(); ++it)
        *it = "white";

    startDfs(vertexesVector, color);


    // for (int i=1; i<n+1; ++i){
    //     std::cout << result[i].vertexCount;
    //     for (int j=0; j<result[i].vertexes.size(); ++j)
    //         std::cout << " " << result[i].vertexes[j];
    //     std::cout << "\n";
    // }

    return 0;
}

void startDfs(VertexesVector& vertexesVector, Colors& color){
    for (int i = 0; i < color.size(); ++i) {
        // Перебираем варианты стартовых вершин, пока они существуют.
        if (color[i] == "white")
            Dfs(vertexesVector, color, i); // Запускаем обход, стартуя с i-й вершины.
    }
}

void Dfs(VertexesVector& vertexesVector, Colors& color, int v) { // v - номер вершины
    color[v] = "gray"; // Вершина посещена, но ещё не обработана.
    //for (int w : outgoing_edges(v)) { // Получите список исходящих ребер в зависимости от способа хранения графа
    for (int w : vertexesVector[v].vertexes) { // Получите список исходящих ребер в зависимости от способа хранения графа
        if (color[w] == "white") // Если вершина не посещена, то
            Dfs(vertexesVector, color, w); // запустим обход от найденной смежной вершины.
    }
    color[v] = "black"; // Теперь вершина обработана.
    std::cout << v;
}
