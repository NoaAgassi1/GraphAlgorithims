//agassinoa20@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "graph.hpp"
#include "Algorithms.hpp"

using namespace graph;
using namespace algo;

// Utility function to count unique edges in an undirected graph
int countUniqueEdges(const Graph& g) {
    int total = 0;
    for (int i = 0; i < g.getNumVertices(); ++i) {
        Neighbor* curr = g.getAdjList()[i];
        while (curr != nullptr) {
            total++;
            curr = curr->next;
        }
    }
    return total / 2;
}

// -------------------- BFS --------------------
TEST_CASE("BFS builds valid spanning tree") {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    Graph tree = Algorithms::bfs(g, 0);
    CHECK(tree.getNumVertices() == 5);
    CHECK(countUniqueEdges(tree) == 4);
}

// -------------------- DFS --------------------
TEST_CASE("DFS builds valid spanning tree") {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    Graph tree = Algorithms::dfs(g, 0);
    CHECK(tree.getNumVertices() == 4);
    CHECK(countUniqueEdges(tree) == 3);
}

// -------------------- Dijkstra --------------------
TEST_CASE("Dijkstra computes shortest path tree") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 2, 5);
    g.addEdge(2, 3, 1);

    Graph tree = Algorithms::dijkstra(g, 0);
    CHECK(tree.getNumVertices() == 4);
    CHECK(countUniqueEdges(tree) == 3);
}

// -------------------- Prim --------------------
TEST_CASE("Prim builds minimum spanning tree") {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    Graph tree = Algorithms::prim(g);
    CHECK(tree.getNumVertices() == 4);
    CHECK(countUniqueEdges(tree) == 3);
}

// -------------------- Kruskal --------------------
TEST_CASE("Kruskal builds minimum spanning tree") {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    Graph tree = Algorithms::kruskal(g);
    CHECK(tree.getNumVertices() == 4);
    CHECK(countUniqueEdges(tree) == 3);
}
