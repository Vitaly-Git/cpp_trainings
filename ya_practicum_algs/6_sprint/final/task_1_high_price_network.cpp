/*
   Ссылка на отчёт в контесте:
   https://contest.yandex.ru/contest/25070/run-report/114720324/

-- ПРИНЦИП РАБОТЫ --
1. Подумал, что интереснее быдет сделать что-то неизвестное.
   Поэтому, решил использовать алгоритм Алгоритм Краскала.
   Информацию брал тут: 
   https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%9A%D1%80%D0%B0%D1%81%D0%BA%D0%B0%D0%BB%D0%B0
   https://youtu.be/5XEjNWHc_NI?si=VGaepcyE6Iy6nGWg
2. Алгоритм может использоваться как для поиска минимального, так и максимального оставного дерева.
3. Для поиска максимального остовного дерева мы просто меняем знаки весов ребер на противоположные.
4. Алгоритм:
4.1. Вначале мы производим сортировку рёбер по неубыванию по их весам.
4.2. Добавляем i-ое ребро в наш подграф только в том случае, если данное ребро соединяет две разные компоненты связности, 
     одним из которых является наш подграф. То есть, на каждом шаге добавляется минимальное по весу ребро, один конец которого 
     содержится в нашем подграфе, а другой - еще нет.
4.3. Алгоритм завершит свою работу после того, как множество вершин нашего подграфа совпадет с множеством вершин исходного графа.
5. Так как не все вершины могут быть связаны, перед началом поиска оставного дерева проверяем количество связнных графов.
6. Для проверки связанности используем поиск в глубину.
-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
1. Подтверждено решением задачи.
2. Точная формулировка дана в Википедии:
   Алгоритм Краскала действительно находит остовное дерево минимального веса, поскольку он является частным случаем алгоритма 
   Радо — Эдмондса для графического матроида, где независимые множества — ациклические множества рёбер.
-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
1. До начала работы алгоритма необходимо отсортировать рёбра по весу и вершины по возрастанию, это требует O(Elog(E))+O(Vlog(V)).
2. Скорость DFS для проверки связанности O(V+E).
3. Сложность Алгоритма Краскала O(E*log(E))
4. Выберем максимальную сложность: O(E*log(E))
5. Максимальная сложность: O(Elog(E))
-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
1. Сложность DFS для проверки связанности O(V), не забыв про рекурсию.
2. Алгоритм Краскала также потребуется выделения памяти равной количеству вершин: O(V).
3. Таким образом, пространственная сложность равна O(V). 
4. Итоговая пространственная сложность решения равна O(V). 
*/


#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

struct Edge{
  int vertice1 = 0;
  int vertice2 = 0;
  int weight = 0;
};
struct Vertices{
    int verticeCount = 0;
    std::vector<int> vertexes;
};

typedef std::vector<int> Colors;
typedef std::vector<Vertices> VerticesVector;

int maxOstTree(int verticeCount, std::vector<Edge>& edges);
int getConnectedComponentCount(VerticesVector& verticesVector, int n);
void startDfsToCalcConnectedComponentCount(VerticesVector& verticesVector, Colors& color, int& connectedComponentCount);
void Dfs(VerticesVector& verticesVector, Colors& color, int v, int& connectedComponentCount);

int main(){

  int n=0;
  int m=0;
  std::cin >> n >> m;

  std::vector<Edge> edges(m); 
  VerticesVector verticesVector(n+1);

  int u,v,w;
  for (int idxEdge = 0; idxEdge<m; ++idxEdge){
    std::cin >> u >> v >> w;

    edges[idxEdge].vertice1 = --u;
    edges[idxEdge].vertice2 = --v;
    edges[idxEdge].weight = -w;

    ++(verticesVector[u].verticeCount);
    verticesVector[u].vertexes.push_back(v);
    ++(verticesVector[v].verticeCount);
    verticesVector[v].vertexes.push_back(u); 
  }

  int connectedComponentCount = getConnectedComponentCount(verticesVector, n);

  int maxOst = maxOstTree(n, edges);
  if ((maxOst == 0 || connectedComponentCount > 1) && !(n==1 && m==0))
    std::cout << "Oops! I did it again" << '\n';
  else
    std::cout << maxOst << '\n';

  return 0;
}

int maxOstTree(int verticeCount, std::vector<Edge>& edges){
  int maxOst = 0;

  std::map<int, int> mapVertexSet;
  std::vector<std::vector<int>> setsItems(verticeCount);

  for(int itemIdx=0; itemIdx < verticeCount; ++itemIdx){
    mapVertexSet[itemIdx] = itemIdx;
    
    std::vector<int>* itemsOfSet = new std::vector<int>{itemIdx};
    setsItems[itemIdx] = *itemsOfSet;
  }

  std::sort(edges.begin(), edges.end(), [](auto& lhs, auto& rhs)
    {
      if (lhs.weight!=rhs.weight)
        return lhs.weight<rhs.weight;

      if (lhs.vertice1!=rhs.vertice1)
         return lhs.vertice1<rhs.vertice1;

      return lhs.vertice2<rhs.vertice2;
    });

  for (auto& edge: edges){
    if (mapVertexSet[edge.vertice1] == mapVertexSet[edge.vertice2])
      continue;

    int oldSetIdx = mapVertexSet[edge.vertice2];
    int newSetIdx = mapVertexSet[edge.vertice1];

    for (auto item : setsItems[oldSetIdx]){
      setsItems[newSetIdx].push_back(item);
      mapVertexSet[item] = newSetIdx;
    }
    setsItems[oldSetIdx].clear();
    
    maxOst += edge.weight;
  }

  return -maxOst;
}

int getConnectedComponentCount(VerticesVector& verticesVector, int n){
  int connectedComponentCount = 1;

  for (int idxVertex = 0; idxVertex<=n; ++idxVertex)
      std::sort(verticesVector[idxVertex].vertexes.begin(), verticesVector[idxVertex].vertexes.end());        
  
  Colors color(n+1);
  for(auto it = color.begin(); it!=color.end(); ++it)
      *it = -1;

  startDfsToCalcConnectedComponentCount(verticesVector, color, connectedComponentCount);
  return connectedComponentCount - 2;
}

void startDfsToCalcConnectedComponentCount(VerticesVector& verticesVector, Colors& color, int& connectedComponentCount){
    for (int i = 0; i < color.size(); ++i) {
        if (color[i] == -1){
            Dfs(verticesVector, color, i, connectedComponentCount);
            ++connectedComponentCount;
        }
    }
}

void Dfs(VerticesVector& verticesVector, Colors& color, int v, int& connectedComponentCount) {
    color[v] = 0;
    for (int w : verticesVector[v].vertexes) {
        if (color[w] == -1){
            Dfs(verticesVector, color, w, connectedComponentCount);
        }
    }
    color[v] = connectedComponentCount;
}
