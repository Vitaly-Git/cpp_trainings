// Будеем использовать алгоритм Алгоритм Краскала.
// https://youtu.be/5XEjNWHc_NI?si=VGaepcyE6Iy6nGWg
// Подумал, что интереснее быдет сделать что-то отличное от лекций

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
      
      //return true;

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
