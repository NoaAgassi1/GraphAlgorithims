//agassinoa20@gmail.com
#ifndef GRAPH_HPP
#define GRAPH_HPP

namespace graph{

    struct Neighbor {
        int vertex;         
        int weight;         
        Neighbor* next;     
    };

    class Graph{
    private:
        int numVertices;
        Neighbor **adjList;

    public:
        Graph(int numofV);
        ~Graph();
        void addEdge(int src, int dest, int weight = 1);
        void removeSingleEdge(int from, int to);
        void removeEdge(int src, int dest);
        void print_graph() const;
        int getNumVertices() const;
        Neighbor** getAdjList() const;

    };

    }

#endif
