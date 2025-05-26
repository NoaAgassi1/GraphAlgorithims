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

// Utility to check if edge exists
bool hasEdge(const Graph& g, int u, int v, int weight) {
    Neighbor* curr = g.getAdjList()[u];
    while (curr) {
        if (curr->vertex == v && curr->weight == weight) return true;
        curr = curr->next;
    }
    return false;
}

// -------------------- BFS --------------------

TEST_CASE("BFS - builds valid spanning tree") {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    Graph tree = Algorithms::bfs(g, 0);
    CHECK(tree.getNumVertices() == 5);
    CHECK(countUniqueEdges(tree) == tree.getNumVertices() - 1);
}

TEST_CASE("BFS - disconnected graph only includes reachable part") {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    Graph tree = Algorithms::bfs(g, 0);
    CHECK(tree.getNumVertices() == 5);
    CHECK(countUniqueEdges(tree) == 2);
}

// -------------------- DFS --------------------

TEST_CASE("DFS - builds valid spanning tree") {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    Graph tree = Algorithms::dfs(g, 0);
    CHECK(tree.getNumVertices() == 4);
    CHECK(countUniqueEdges(tree) == tree.getNumVertices() - 1);
}

TEST_CASE("DFS - handles cycle correctly") {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);

    Graph tree = Algorithms::dfs(g, 0);
    CHECK(countUniqueEdges(tree) == 3);
}

// -------------------- Dijkstra --------------------

TEST_CASE("Dijkstra - builds shortest path tree") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 2, 5);
    g.addEdge(2, 3, 1);

    Graph tree = Algorithms::dijkstra(g, 0);
    CHECK(tree.getNumVertices() == 4);
    CHECK(countUniqueEdges(tree) == tree.getNumVertices() - 1);
}

TEST_CASE("Dijkstra - prefers shorter weighted path") {
    Graph g(3);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(0, 2, 10);
    Graph tree = Algorithms::dijkstra(g, 0);
    CHECK(countUniqueEdges(tree) == 2);
}

TEST_CASE("Dijkstra - fails on negative weights") {
    Graph g(2);
    g.addEdge(0, 1, -5);
    CHECK_THROWS(Algorithms::dijkstra(g, 0));
}

TEST_CASE("Dijkstra - returns tree with n-1 edges") {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 4, 3);

    Graph result = Algorithms::dijkstra(g, 0);
    CHECK(result.getNumVertices() == 5);
    CHECK(countUniqueEdges(result) == result.getNumVertices() - 1);
}

// -------------------- Prim --------------------

TEST_CASE("Prim - builds MST from general graph") {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    Graph tree = Algorithms::prim(g);
    CHECK(tree.getNumVertices() == 4);
    CHECK(countUniqueEdges(tree) == tree.getNumVertices() - 1);
}

TEST_CASE("Prim - builds MST with equal weights") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);

    Graph result = Algorithms::prim(g);
    CHECK(result.getNumVertices() == 4);
    CHECK(countUniqueEdges(result) == result.getNumVertices() - 1);
}

TEST_CASE("Prim - builds MST from tree input") {
    Graph g(4);
    g.addEdge(0, 1, 5);
    g.addEdge(1, 2, 7);
    g.addEdge(2, 3, 2);

    Graph result = Algorithms::prim(g);
    CHECK(result.getNumVertices() == 4);
    CHECK(countUniqueEdges(result) == result.getNumVertices() - 1);
    CHECK(hasEdge(result, 0, 1, 5));
    CHECK(hasEdge(result, 1, 2, 7));
    CHECK(hasEdge(result, 2, 3, 2));
}

TEST_CASE("Prim - empty graph returns empty tree") {
    Graph g(3);
    Graph result = Algorithms::prim(g);
    CHECK(result.getNumVertices() == 3);
    CHECK(countUniqueEdges(result) == 0);
}

TEST_CASE("Prim - disconnected graph includes only connected component") {
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 3);

    Graph result = Algorithms::prim(g);
    CHECK(result.getNumVertices() == 5);
    CHECK(countUniqueEdges(result) == 2);
}

TEST_CASE("Prim - works with negative edge weights") {
    Graph g(3);
    g.addEdge(0, 1, -4);
    g.addEdge(1, 2, 5);

    Graph result = Algorithms::prim(g);
    CHECK(countUniqueEdges(result) == 2);
}

// -------------------- Kruskal --------------------

TEST_CASE("Kruskal - builds MST from general graph") {
    Graph g(4);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 3, 4);

    Graph tree = Algorithms::kruskal(g);
    CHECK(tree.getNumVertices() == 4);
    CHECK(countUniqueEdges(tree) == tree.getNumVertices() - 1);
}

TEST_CASE("Kruskal - empty graph returns empty tree") {
    Graph g(3);
    Graph result = Algorithms::kruskal(g);
    CHECK(result.getNumVertices() == 3);
    CHECK(countUniqueEdges(result) == 0);
}

TEST_CASE("Kruskal - handles disconnected graph") {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(2, 3, 2);

    Graph result = Algorithms::kruskal(g);
    CHECK(result.getNumVertices() == 5);
    CHECK(countUniqueEdges(result) == 2);
}

TEST_CASE("Kruskal - handles negative edge weights") {
    Graph g(3);
    g.addEdge(0, 1, -4);
    g.addEdge(1, 2, 3);

    Graph result = Algorithms::kruskal(g);
    CHECK(result.getNumVertices() == 3);
    CHECK(countUniqueEdges(result) == 2);
}

TEST_CASE("Kruskal - on tree returns same structure") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);

    Graph result = Algorithms::kruskal(g);
    CHECK(result.getNumVertices() == 4);
    CHECK(countUniqueEdges(result) == result.getNumVertices() - 1);
}

TEST_CASE("Kruskal - handles equal-weight edges") {
    Graph g(4);
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 2);
    g.addEdge(0, 3, 2);

    Graph result = Algorithms::kruskal(g);
    CHECK(result.getNumVertices() == 4);
    CHECK(countUniqueEdges(result) == result.getNumVertices() - 1);
}

// -------------------- Special / Edge Cases --------------------

TEST_CASE("Single node graph") {
    Graph g(1);
    CHECK_NOTHROW(Algorithms::bfs(g, 0));
    CHECK_NOTHROW(Algorithms::dfs(g, 0));
    CHECK_NOTHROW(Algorithms::dijkstra(g, 0));
}

TEST_CASE("Invalid source index throws") {
    Graph g(3);
    CHECK_THROWS(Algorithms::bfs(g, -1));
    CHECK_THROWS(Algorithms::dijkstra(g, 5));
}
