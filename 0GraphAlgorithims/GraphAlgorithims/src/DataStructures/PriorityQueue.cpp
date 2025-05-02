#include "DataStructures/PriorityQueue.hpp"
#include <stdexcept>
#include <utility>  

namespace ds{

    PriorityQueue::PriorityQueue(int cap): capacity(cap),count(0) {
        vertices = new int[capacity];
        priorities = new int[capacity];
    }

    PriorityQueue::~PriorityQueue(){
        delete[] vertices;
        delete[] priorities;
    }

    //Insert a new vertex with a given priority
    void PriorityQueue::insert(int vertex, int priority) {
        if (capacity == count){
            throw std::overflow_error("overflow");
        }
        vertices[count] = vertex;
        priorities[count] = priority;
        bubbleUp(count);
        count++;
    }

    //Extract the vertex with the minimum priority
    int PriorityQueue::extractMin() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");
        }
    
        int result = vertices[0];
    
        //Move last to root and fix heap
        vertices[0] = vertices[count - 1];
        priorities[0] = priorities[count - 1];
        count--;
        bubbleDown(0);
        return result;
    }


    void PriorityQueue::decreaseKey(int value, int newPriority) {
        for (int i = 0; i < count; ++i) {
            if (vertices[i] == value) {
                if (newPriority >= priorities[i]) {
                    throw std::runtime_error("New priority is greater than current priority");
                }
                priorities[i] = newPriority;
                bubbleUp(i);
                return;
            }
        }
        throw std::runtime_error("Value not found");
    }
    
    // Restores the heap property by moving the element at `index` up the tree,
    // swapping it with its parent until the priority order is correct.
    void PriorityQueue::bubbleUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (priorities[index] < priorities[parent]) {
                swap(index, parent);
                index = parent;
            } else {
                break;
            }
        }
    }

    // Restores the heap property by moving the element at `index` down the tree,
    // swapping it with the smaller of its children until the priority order is correct.
    void PriorityQueue::bubbleDown(int index) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;
    
            if (left < count && priorities[left] < priorities[smallest]) {
                smallest = left;
            }
            if (right < count && priorities[right] < priorities[smallest]) {
                smallest = right;
            }
    
            if (smallest != index) {
                swap(index, smallest);
                index = smallest;
            } else {
                break;
            }
        }
    }
    
    // Doubles the capacity of the internal arrays when the heap is full,
    // allocating new memory and copying existing elements into it.
    void PriorityQueue::expand() {
        int newCap = capacity * 2;
        int* newV = new int[newCap];
        int* newPriorities = new int[newCap];
    
        for (int i = 0; i < count; ++i) {
            newV[i] = vertices[i];
            newPriorities[i] = priorities[i];
        }
    
        delete[] vertices;
        delete[] priorities;
    
        vertices = newV;
        priorities = newPriorities;
        capacity = newCap;
    }
    
    void PriorityQueue::swap(int i, int j) {
        std::swap(vertices[i], vertices[j]);
        std::swap(priorities[i], priorities[j]);
    }

    int PriorityQueue::peekMin() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty");}
        return vertices[0];
    }
    
    bool PriorityQueue::isEmpty() const {
        return count == 0;
    }
    
    int PriorityQueue::size() const {
        return count;
    }

}

