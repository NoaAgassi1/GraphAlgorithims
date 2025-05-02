//agassinoa20@gmail.com
#include "DataStructures/Queue.hpp"
#include <stdexcept>

namespace ds {

//Constructor
Queue::Queue(int cap) : capacity(cap), front(0), rear(0), count(0) {
    arr = new int[capacity];
}

// Destructor
Queue::~Queue() {
    delete[] arr;
}

//Adds an element to the rear of the queue
void Queue::enqueue(int value) {
    if (isFull()) {
        throw std::overflow_error("Queue overflow");
    }
    arr[rear] = value;
    rear = (rear + 1) % capacity;
    count++;
}

//Removes and returns the front element of the queue
int Queue::dequeue() {
    if (isEmpty()) {
        throw std::underflow_error("Queue underflow");
    }
    int value = arr[front];
    front = (front + 1) % capacity;
    count--;
    return value;
}

//Returns the front element without removing it
int Queue::peek() const {
    if (isEmpty()) {
        throw std::underflow_error("Queue is empty");}
    return arr[front];
}


bool Queue::isEmpty() const {
    return count == 0;
}

bool Queue::isFull() const {
    return count == capacity;
}


int Queue::size() {
    return this->count;
}

}
