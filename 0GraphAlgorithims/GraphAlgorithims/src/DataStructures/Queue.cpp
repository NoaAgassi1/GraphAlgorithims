//agassinoa20@gmail.com
#include "DataStructures/Queue.hpp"
#include "Exceptions.hpp"

namespace ds {

// Constructor: initializes queue with given capacity
Queue::Queue(int cap) : capacity(cap), front(0), rear(0), count(0) {
    arr = new int[capacity];
}

// Destructor: frees dynamically allocated array
Queue::~Queue() {
    delete[] arr;
}

// Adds an element to the rear of the queue
void Queue::enqueue(int value) {
    if (isFull()) {
        throw SimpleException("Queue overflow");
    }
    arr[rear] = value;
    rear = (rear + 1) % capacity;
    count++;
}

// Removes and returns the front element of the queue
int Queue::dequeue() {
    if (isEmpty()) {
        throw SimpleException("Queue underflow");
    }
    int value = arr[front];
    front = (front + 1) % capacity;
    count--;
    return value;
}

// Returns the front element without removing it
int Queue::peek() const {
    if (isEmpty()) {
        throw SimpleException("Queue is empty");
    }
    return arr[front];
}

// Checks if the queue is empty
bool Queue::isEmpty() const {
    return count == 0;
}

// Checks if the queue is full
bool Queue::isFull() const {
    return count == capacity;
}

// Returns the number of elements currently in the queue
int Queue::size() {
    return this->count;
}

}
