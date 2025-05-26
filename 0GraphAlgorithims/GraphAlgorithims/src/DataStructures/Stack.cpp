//agassinoa20@gmail.com

#include "DataStructures/Stack.hpp"
#include "Exceptions.hpp"


namespace ds {

// Constructor: initializes stack with given capacity
Stack::Stack(int cap) : capacity(cap), topIndex(-1) {
    arr = new int[capacity];
}

// Destructor: frees the dynamically allocated array
Stack::~Stack() {
    delete[] arr;
}

// Pushes a value onto the top of the stack
void Stack::push(int value) {
    if (isFull()) {
        throw SimpleException("Stack overflow");
    }
    arr[++topIndex] = value;
}

// Removes and returns the top element of the stack
int Stack::pop() {
    if (isEmpty()) {
        throw SimpleException("Stack underflow");
    }
    return arr[topIndex--];
}

// Returns the top element without removing it
int Stack::top() const {
    if (isEmpty()) {
        throw SimpleException("Stack is empty");
    }
    return arr[topIndex];
}

// Checks if the stack is empty
bool Stack::isEmpty() const {
    return topIndex == -1;
}

// Checks if the stack is full
bool Stack::isFull() const {
    return topIndex == capacity - 1;
}

}
