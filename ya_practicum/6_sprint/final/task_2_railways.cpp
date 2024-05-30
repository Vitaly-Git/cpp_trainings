#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

struct Vertices{
    int VerticeCount = 0;
    std::vector<int> Vertices;
};

typedef std::vector<std::string> Colors;
typedef std::vector<Vertices> VerticesVector;

bool isGraphCycled(VerticesVector& VerticesVector, Colors& color);
void startDfs(VerticesVector& VerticesVector, Colors& color, bool& graphCycled);
void Dfs(VerticesVector& VerticesVector, Colors& color, int v, bool& graphCycled);

int main(){

    // Ввод количества городов

    int n=0;
    std::cin >> n;

    VerticesVector VerticesVector(n+1);

    // Превращаем символы в ребра графа:
    // R - прямое ребро
    // B - обратное ребро

    int u,v;
    char direction;
    for (int idxPathPoint1 = 0; idxPathPoint1<n; ++idxPathPoint1){
        
        for (int idxPathPoint2 = idxPathPoint1+1; idxPathPoint2<n; ++idxPathPoint2){
            std::cin >> direction;
            if (direction == 'R'){
                u = idxPathPoint1;
                v = idxPathPoint2;
            } else {
                u = idxPathPoint2;
                v = idxPathPoint1;
            }
            ++(VerticesVector[u].VerticeCount);
            VerticesVector[u].Vertices.push_back(v);                    
        }
    }

    for (int idxVertice = 0; idxVertice<=n; ++idxVertice)
        std::sort(VerticesVector[idxVertice].Vertices.begin(), VerticesVector[idxVertice].Vertices.end());        

    Colors color(n+1);
    for(auto it = color.begin(); it!=color.end(); ++it)
        *it = "white";

    // Обходим граф через DFS, выполняя поиск цикло в графе

    if (isGraphCycled(VerticesVector, color))
        std::cout << "NO";
    else    
        std::cout << "YES";

    return 0;
}

bool isGraphCycled(VerticesVector& VerticesVector, Colors& color){
    bool graphCycled = false;
    startDfs(VerticesVector, color, graphCycled);
    return graphCycled; 
}

void startDfs(VerticesVector& VerticesVector, Colors& color, bool& graphCycled){
    for (int i = 0; i < color.size(); ++i) {
        if (color[i] == "white")
            Dfs(VerticesVector, color, i, graphCycled);
            if (graphCycled)
                return;
    }
}

void Dfs(VerticesVector& VerticesVector, Colors& color, int v, bool& graphCycled) {
    color[v] = "gray";
    for (int w : VerticesVector[v].Vertices) {
        if (color[w] == "white"){
            Dfs(VerticesVector, color, w, graphCycled);
        }else if (color[w] == "gray") {
            graphCycled = true;
            return;
        }
    }
    color[v] = "black";
}
