#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace ds {

class Queue {
private:
    int capacity;    // Maximum number of elements
    int* arr;        // Array to store queue elements
    int front;       // Index of front element
    int rear;        // Index of last element
    int count;       // Current size of the queue

public:
    Queue(int cap = 100);   // Constructor with default capacity
    ~Queue();               // Destructor

    void enqueue(int value);
    int dequeue();
    int peek() const;
    bool isFull() const;
    bool isEmpty() const;
    int size();
};

} 

#endif 
