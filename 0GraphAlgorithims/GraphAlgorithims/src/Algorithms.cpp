#include "Algorithms.hpp"
#include <iostream>  
enum State { UNDISCOVERED, DISCOVERED, PROCESSED };

namespace algo {

    graph::Graph Algorithms::bfs(const graph::Graph& original, int source) {
        int vertexCount = original.getNumVertices();
    
        if (source < 0 || source >= vertexCount) {
            throw std::runtime_error("Source vertex is out of range");
        }
    
        graph::Graph bfsTree(vertexCount);
        State* state = new State[vertexCount];
    
        for (int i = 0; i < vertexCount; ++i) {
            state[i] = UNDISCOVERED;
        }
    
        ds::Queue queue(vertexCount);
        queue.enqueue(source);
        state[source] = DISCOVERED;
    
        while (!queue.isEmpty()) {
            int current = queue.dequeue();
            graph::Neighbor* neighbor = original.getAdjList()[current];
    
            while (neighbor != nullptr) {
                int target = neighbor->vertex;
    
                if (state[target] == UNDISCOVERED) {
                    state[target] = DISCOVERED;
                    bfsTree.addEdge(current, target, neighbor->weight);
                    queue.enqueue(target);
                }
    
                neighbor = neighbor->next;
            }
    
            state[current] = PROCESSED;
        }
    
        delete[] state;
        return bfsTree;
    }
    
    

    void dfsRecursive(const graph::Graph& graph, int current, State* state, graph::Graph& tree) {
        state[current] = DISCOVERED;

        graph::Neighbor* adj = graph.getAdjList()[current];
        while (adj != nullptr) {
            int next = adj->vertex;
            if (state[next] == UNDISCOVERED) {
                tree.addEdge(current, next, adj->weight);
                dfsRecursive(graph, next, state, tree);
            }
            adj = adj->next;
        }

        state[current] = PROCESSED;
    }

    graph::Graph Algorithms::dfs(const graph::Graph& input, int start) {
        int totalVertices = input.getNumVertices();

        if (start < 0 || start >= totalVertices) {
            throw std::runtime_error("Invalid start vertex for DFS");
        }

        graph::Graph dfsTree(totalVertices);
        State* state = new State[totalVertices];

        for (int i = 0; i < totalVertices; ++i) {
            state[i] = UNDISCOVERED;
        }

        dfsRecursive(input, start, state, dfsTree);

        delete[] state;
        return dfsTree;
    }



    
graph::Graph Algorithms::dijkstra(const graph::Graph& g, int startVertex) {
    int n = g.getNumVertices();

    // Validate input
    if (startVertex < 0 || startVertex >= n) {
        throw std::runtime_error("Invalid start vertex");
    }
    const int INF = 100000000;
    // distance[i]: shortest known distance from startVertex to i
    // parent[i]: previous vertex on shortest path to i
    // processed[i]: whether i was finalized
    int* distance = new int[n];
    int* parent = new int[n];
    bool* processed = new bool[n];

    for (int i = 0; i < n; ++i) {
        distance[i] = INF;
        parent[i] = -1;
        processed[i] = false;
    }

    distance[startVertex] = 0;

    ds::PriorityQueue q(n);
    q.insert(startVertex, 0);  // (vertex, priority)

    while (!q.isEmpty()) {
        int u = q.extractMin();  // vertex with smallest distance

        // Skip if already processed
        if (processed[u])
            continue;
        processed[u] = true;
        // Traverse neighbors
        graph::Neighbor* neighbor = g.getAdjList()[u];
        while (neighbor != nullptr) {
            int v = neighbor->vertex;
            int weight = neighbor->weight;

            if (!processed[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u;
                q.insert(v, distance[v]);
            }

            neighbor = neighbor->next;
        }
    }

    // Build shortest path tree using parent[]
    graph::Graph shortestPaths(n);
    for (int v = 0; v < n; ++v) {
        if (parent[v] != -1) {
            int weight = distance[v] - distance[parent[v]];
            shortestPaths.addEdge(parent[v], v, weight);
        }
    }

    delete[] distance;
    delete[] parent;
    delete[] processed;

    return shortestPaths;
}

graph::Graph Algorithms::prim(const graph::Graph& g) {
    const int V = g.getNumVertices();
    const int INF = 1000000000;

    // This will store the resulting MST
    graph::Graph mst(V);

    // Arrays to track vertex states
    int* cost = new int[V];        // Minimum edge weight to reach each vertex
    int* source = new int[V];      // From which vertex we reached the current one
    bool* added = new bool[V];     // Whether a vertex is already included in the MST

    // Initialization
    int i = 0;
    while (i < V) {
        cost[i] = INF;
        source[i] = -1;
        added[i] = false;
        ++i;
    }

    // Start from vertex 0
    cost[0] = 0;
    ds::PriorityQueue queue(V);
    queue.insert(0, 0);  // Insert with priority = 0

    while (!queue.isEmpty()) {
        int curr = queue.extractMin();

        if (added[curr])
            continue;

        added[curr] = true;

        // If this is not the first vertex, add the edge to MST
        if (source[curr] != -1) {
            mst.addEdge(source[curr], curr, cost[curr]);
        }

        // Traverse all neighbors of the current vertex
        graph::Neighbor* ptr = g.getAdjList()[curr];
        while (ptr != nullptr) {
            int neighbor = ptr->vertex;
            int weight = ptr->weight;

            // If neighbor is not in MST and edge is lighter, update it
            if (!added[neighbor] && weight < cost[neighbor]) {
                cost[neighbor] = weight;
                source[neighbor] = curr;
                queue.insert(neighbor, weight);
            }

            ptr = ptr->next;
        }
    }

    // Clean up dynamic memory
    delete[] cost;
    delete[] source;
    delete[] added;

    return mst;
}



struct FullEdge {
    int src, dest,weight;
};

// Bubble sort the edges array by weight
void sortEdges(FullEdge* edges, int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (edges[j].weight > edges[j + 1].weight) {
                FullEdge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}


graph::Graph Algorithms::kruskal(const graph::Graph& g){

    int n = g.getNumVertices();
    graph::Graph mst(n);  // This will hold the resulting MST

    //Collect all edges into an array
    int maxEdges = n * (n - 1) / 2; // Upper bound for undirected edges
    FullEdge* edges = new FullEdge[maxEdges];
    int edgeCount = 0;

    for (int u = 0; u < n; ++u) {
        graph::Neighbor* neighbor = g.getAdjList()[u];
        while (neighbor != nullptr) {
            int v = neighbor->vertex;
            int weight = neighbor->weight;

            if (u < v) { // To avoid adding the same undirected edge twice
                edges[edgeCount++] = {u, v, weight};
            }
            neighbor = neighbor->next;
        }
    }
    sortEdges(edges, edgeCount);

    //Initialize Union-Find to track connected components
    ds::UnionFind uf(n);
    int added = 0;

    //Add edges to MST as long as they don't form a cycle
    for (int i = 0; i < edgeCount && added < n - 1; ++i) {
        int u = edges[i].src;
        int v = edges[i].dest;

        if (uf.find(u) != uf.find(v)) {
            uf.unite(u, v);
            mst.addEdge(u, v, edges[i].weight);
            added++;
        }
    }
    delete[] edges;
    return mst;
}




}




