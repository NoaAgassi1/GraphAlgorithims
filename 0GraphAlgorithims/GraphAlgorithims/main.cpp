#include <iostream>
#include"include/graph.hpp"
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

    std::cout << "Original Graph:" << std::endl;
    g.print_graph();
    
    std::cout << "\nBFS Tree from vertex 0:" << std::endl;
    Graph bfsTree = algo::Algorithms::bfs(g, 0);
    bfsTree.print_graph();

    std::cout << "\nDFS Tree from vertex 0:" << std::endl;
    Graph dfsTree = algo::Algorithms::dfs(g, 0);
    dfsTree.print_graph();

    std::cout << "\nDijkstra Shortest Path Tree from vertex 0::" << std::endl;
    Graph dijkstraTree = algo::Algorithms::dijkstra(g, 0);
    dijkstraTree.print_graph();

    std::cout << "\nPrim's Minimum Spanning Tree:" << std::endl;
    Graph primTree = algo::Algorithms::prim(g);
    primTree.print_graph();

    std::cout << "\nKruskal's Minimum Spanning Tree:" << std::endl;
    Graph kruskalTree = algo::Algorithms::kruskal(g);
    kruskalTree.print_graph();

    return 0;
}