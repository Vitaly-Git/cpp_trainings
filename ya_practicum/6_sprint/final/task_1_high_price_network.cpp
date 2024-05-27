// Будеем использовать алгоритм Алгоритм Краскала.
// https://youtu.be/5XEjNWHc_NI?si=VGaepcyE6Iy6nGWg
// Подумал, что интереснее быдет сделать что-то отличное от лекций

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

std::map<int, int> mapVertexSet;

struct Edge{
  int vertice1 = 0;
  int vertice2 = 0;
  int weight = 0;
};
std::vector<Edge> edges; 

int main(){

  int n=0;
  int m=0;
  std::cin >> n >> m;

  edges.resize(n);

  int u,v,w;
  for (int idxEdge = 0; idxEdge<m; ++idxEdge){
    std::cin >> edges[idxEdge].vertice1 >> edges[idxEdge].vertice2 >> edges[idxEdge].weight;
    edges[idxEdge].weight = -edges[idxEdge].weight;
  }





    return 0;
}

minimum_spanning_tree = []   # Рёбра, составляющие MST.

added = {}          # Множество вершин, уже добавленных в остов.
not_added = {}      # Множество вершины, ещё не добавленных в остов. 
edges = []          # Массив рёбер, исходящих из остовного дерева.

функция add_vertex(v)
  added += v
  not_added -= v
  # Добавляем все рёбра, которые инцидентны v, но их конец ещё не в остове.
  #
  # Вершины not_added стоит хранить в таком контейнере,
  # чтобы проверка (end in not_added) выполнялась эффективно.
  #
  # Для этого подойдёт, например, хеш-таблица.
  # Также в некоторых языках программирования имеется контейнер set.
  edges += graph.edges.filter(start == v, end in not_added)


функция find_MST(graph):
  not_added = graph.vertices
    
  # Берём первую попавшуюся вершину.
  v = graph.vertices[0]
  add_vertex(v)

  пока not_added не пуст и edges не пуст:
    # Подразумеваем, что extract_minimum извлекает минимальное ребро 
    # из массива рёбер и больше данного ребра в массива не будет.
    e = extract_minimum(edges)
    если e.end in not_added, то:
      minimum_spanning_tree += e
      add_vertex(e.end)

  если not_added не пуст, то 
    верни ошибку "Исходный граф несвязный"
  иначе
    верни minimum_spanning_tree





var minimumSpanningTree = mutableListOf<Edge>()  // Рёбра, составляющие MST.

val added = mutableSetOf<Vertex>()  // Множество вершин, уже добавленных в остов.
val notAdded = mutableSetOf<Vertex>()  // Множество вершин, ещё не добавленных в остов.
val edges = mutableListOf<Edge>()  // Массив рёбер, исходящих из остовного дерева.

fun addVertex(v: Vertex) {
    added += v
    notAdded -= v
    // Добавляем все рёбра, которые инцидентны v, но их конец ещё не в остове.
    //
    // Вершины notAdded стоит хранить в таком контейнере,
    // чтобы проверка (end in notAdded) выполнялась эффективно.
    //
    // Для этого подойдёт, например, хеш-таблица.
    // Также в некоторых языках программирования имеется контейнер set.
    edges += graph.edges.filter { it.start == v && it.end in notAdded }
}

fun findMST(graph: Graph): List<Edge> {
    notAdded.addAll(graph.vertices)

    // Берём первую попавшуюся вершину.
    val v = graph.vertices[0]
    addVertex(v)

    while (notAdded.isNotEmpty() && edges.isNotEmpty()) {
        // Подразумеваем, что extractMinimum извлекает минимальное ребро
        // из массива рёбер и больше данного ребра в массива не будет.
        val e = extractMinimum(edges)
        if (e.end in notAdded) {
            minimumSpanningTree += e
            addVertex(e.end)
        }
    }

    return if (notAdded.isNotEmpty()) {
        error("Исходный граф несвязный")
    } else {
        minimumSpanningTree
    }
}    