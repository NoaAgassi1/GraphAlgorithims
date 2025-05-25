//agassinoa20@gmail.com
#include <iostream>
#include <stdexcept>
#include "graph.hpp"


namespace graph{

    Graph::Graph(int numofV) : numVertices(numofV){
        if (numVertices <= 0){
            throw std::runtime_error("Number of vertices must be positive");
        }
        adjList = new Neighbor*[numVertices];
        for (int i = 0; i < numVertices; i++){
            adjList[i] = nullptr;
        }
    }

    Graph::~Graph(){
        for (int i = 0; i < numVertices; i++){
            Neighbor *current = adjList[i];
            while (current != nullptr){
                Neighbor *temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] adjList;
    }

   
   void Graph::addEdge(int src, int dest, int weight) {
        // Check that the source and destination vertices are within valid bounds
        if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) {
            throw std::out_of_range("Invalid vertex index");
        }
         // Check if edge already exists from src to dest
        Neighbor* curr = adjList[src];
        while (curr != nullptr) {
            if (curr->vertex == dest) {
                throw std::invalid_argument("Edge already exists");
            }
            curr = curr->next;
        }
        //Create a new neighbor node for dest and add it to the front of src's list
        Neighbor* newNeighbor_d = new Neighbor{dest, weight, adjList[src]};
        adjList[src] = newNeighbor_d;
    
        //the graph is undirected, also add a node for src to dest's list
        Neighbor* newNeighbor_src = new Neighbor{src, weight, adjList[dest]};
        adjList[dest] = newNeighbor_src;
    }

    void Graph::removeSingleEdge(int from, int to){
        Neighbor *current = adjList[from];
        Neighbor *prev = nullptr;

        while (current != nullptr && current->vertex != to){
            prev = current;
            current = current->next;
        }

        if (current == nullptr) { throw std::runtime_error("Edge not found"); }

        // The edge is the first in the list
        if (prev == nullptr){
            adjList[from] = current ->next;}
        else{
            prev->next = current->next;}

        delete current;
    }

    void Graph::removeEdge(int src, int dest) {
        if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) {
            throw std::out_of_range("Invalid vertex index");
        }
        removeSingleEdge(src, dest);
        removeSingleEdge(dest, src);
    }
    
    void Graph::print_graph() const {
        std::cout << "Graph adjacency list:" << std::endl;
        for (int i = 0; i < numVertices; ++i) {
            std::cout << "Vertex " << i << ":";
    
            Neighbor* current = adjList[i];
            while (current != nullptr) {
                std::cout << " -> (v: " << current->vertex << ", w: " << current->weight << ")";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }
    
    int Graph::getNumVertices() const {
        return numVertices;
    }
    
    Neighbor** Graph::getAdjList() const {
        return adjList;
    }
    
    
}
