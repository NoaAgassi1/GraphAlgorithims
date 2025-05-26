//agassinoa20@gmail.com
#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include "graph.hpp"
#include "DataStructures/Queue.hpp"
#include "DataStructures/Stack.hpp"
#include "DataStructures/PriorityQueue.hpp"
#include "DataStructures/UnionFind.hpp"

namespace algo {

class Algorithms {
public:
    // BFS traversal from start vertex.
    // Output should be printed or stored manually.
    static graph::Graph bfs(const graph::Graph& g, int startVertex);

    // DFS traversal from start vertex.
    static graph::Graph dfs(const graph::Graph& g, int startVertex);

    // Dijkstra's algorithm: computes shortest paths from start vertex.
    static graph::Graph dijkstra(const graph::Graph& g, int startVertex);

    // Prim's algorithm: builds MST.
    static graph::Graph prim(const graph::Graph& g);

    // Kruskal's algorithm: builds MST using Union-Find.
    static graph::Graph kruskal(const graph::Graph& g);
};

} // namespace algo

#endif // ALGORITHMS_HPP
