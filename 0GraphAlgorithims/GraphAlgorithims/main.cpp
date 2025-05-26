//agassinoa20@gmail.com
#include <cstdio>  
#include "include/graph.hpp"
#include "include/Algorithms.hpp"

using namespace graph;

int main() {
    Graph g(6);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 4, 3); 
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 5, 5); // extra edge to demonstrate multiple paths

    printf("Original Graph:\n");
    g.print_graph();
    
    printf("\nBFS Tree from vertex 0:\n");
    Graph bfsTree = algo::Algorithms::bfs(g, 0);
    bfsTree.print_graph();

    printf("\nDFS Tree from vertex 0:\n");
    Graph dfsTree = algo::Algorithms::dfs(g, 0);
    dfsTree.print_graph();

    printf("\nDijkstra Shortest Path Tree from vertex 0:\n");
    Graph dijkstraTree = algo::Algorithms::dijkstra(g, 0);
    dijkstraTree.print_graph();

    printf("\nPrim's Minimum Spanning Tree:\n");
    Graph primTree = algo::Algorithms::prim(g);
    primTree.print_graph();

    printf("\nKruskal's Minimum Spanning Tree:\n");
    Graph kruskalTree = algo::Algorithms::kruskal(g);
    kruskalTree.print_graph();

    return 0;
}
