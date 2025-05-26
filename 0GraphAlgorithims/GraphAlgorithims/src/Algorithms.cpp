//agassinoa20@gmail.com
#include "Algorithms.hpp"
#include "Exceptions.hpp"
 

namespace algo {

    graph::Graph Algorithms::bfs(const graph::Graph& g, int startVertex) {
        int n = g.getNumVertices();
        if (startVertex < 0 || startVertex >= n) {
            throw SimpleException("Invalid start vertex");
        }
        graph::Graph tree(n);  // This will hold the BFS tree
        //visited array
        bool* visited = new bool[n];
        for (int i = 0; i < n; ++i) {
            visited[i] = false;
        }
        ds::Queue q(n);  // assuming constructor gets capacity
        q.enqueue(startVertex);
        visited[startVertex] = true;
        //BFS loop
        while (!q.isEmpty()) {
            int current = q.dequeue();
            // Go through all neighbors of current
            graph::Neighbor* neighbor = g.getAdjList()[current];
            while (neighbor != nullptr) {
                int v = neighbor->vertex;
                if (!visited[v]) {
                    visited[v] = true;
                    tree.addEdge(current, v, neighbor->weight); // Add edge to BFS tree
                    q.enqueue(v);
                }
                neighbor = neighbor->next;
            }
        }
    
        delete[] visited;
        return tree;
    }

    // Helper recursive function
    void dfsVisit(const graph::Graph& g, int u, bool* visited, graph::Graph& tree) {
        visited[u] = true;

        graph::Neighbor* neighbor = g.getAdjList()[u];
        while (neighbor != nullptr) {
            int v = neighbor->vertex;
            if (!visited[v]) {
                tree.addEdge(u, v, neighbor->weight);  // tree edge
                dfsVisit(g, v, visited, tree);         // recurse
            }
            neighbor = neighbor->next;
        }
    }

    graph::Graph Algorithms::dfs(const graph::Graph& g, int startVertex) {
        int n = g.getNumVertices();
        if (startVertex < 0 || startVertex >= n) {
            throw SimpleException("Invalid start vertex");
        }
        graph::Graph tree(n);
        bool* visited = new bool[n];
        for (int i = 0; i < n; ++i) {
            visited[i] = false;
        }
        dfsVisit(g, startVertex, visited, tree);

        delete[] visited;
        return tree;
    }

    
graph::Graph Algorithms::dijkstra(const graph::Graph& g, int startVertex) {
    int n = g.getNumVertices();

    // Validate input
    if (startVertex < 0 || startVertex >= n) {
        throw SimpleException("Invalid start vertex");
    }
    
     for (int u = 0; u < n; ++u) {
        graph::Neighbor* neighbor = g.getAdjList()[u];
        while (neighbor != nullptr) {
            if (neighbor->weight < 0) {
                throw SimpleException("Dijkstra cannot handle negative edge weights");
            }
            neighbor = neighbor->next;
        }
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

    ds::PriorityQueue pq(n);
    pq.insert(startVertex, 0);  // (vertex, priority)

    while (!pq.isEmpty()) {
        int u = pq.extractMin();  // vertex with smallest distance

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
                pq.insert(v, distance[v]);
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
    int n = g.getNumVertices();
    const int INF = 1000000000;

    // Arrays for tracking the MST construction
    bool* inMST = new bool[n];   // Whether vertex is already included in the MST
    int* key = new int[n];       // Minimum weight to connect vertex to MST
    int* parent = new int[n];    // From which vertex we reached this one

    // Initialization
    for (int i = 0; i < n; ++i) {
        inMST[i] = false;
        key[i] = INF;
        parent[i] = -1;
    }
    // Start from vertex 0
    key[0] = 0;
    ds::PriorityQueue pq(n);
    pq.insert(0, 0);  // (vertex, priority = weight)

    while (!pq.isEmpty()) {
        int u = pq.extractMin();

        // Skip if already processed
        if (inMST[u])
            continue;

        inMST[u] = true;
        // Traverse neighbors of u
        graph::Neighbor* neighbor = g.getAdjList()[u];
        while (neighbor != nullptr) {
            int v = neighbor->vertex;
            int weight = neighbor->weight;

            // If v is not in MST and weight is better, update it
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.insert(v, key[v]);  // insert with new lower priority
            }
            neighbor = neighbor->next;
        }
    }
    // Construct the MST graph from parent[]
    graph::Graph mst(n);
    for (int v = 1; v < n; ++v) {
        if (parent[v] != -1) {
            mst.addEdge(parent[v], v, key[v]);
        }
    }
    // Clean up
    delete[] inMST;
    delete[] key;
    delete[] parent;

    return mst;
}


struct FullEdge {
    int src, dest,weight;
};

// Bubble sort the edges array by weight (ascending)
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

    //Sort edges by weight (ascending)
    sortEdges(edges, edgeCount);

    //Initialize Union-Find to track connected components
    ds::UnionFind uf(n);
    int added = 0;

    // Step 4: Add edges to MST as long as they don't form a cycle
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




