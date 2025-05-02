//agassinoa20@gmail.com
#include "DataStructures/Stack.hpp"
#include <stdexcept>

namespace ds {

//Constructor
Stack::Stack(int cap) : capacity(cap), topIndex(-1) {
    arr = new int[capacity];
}

//Destructor
Stack::~Stack() {
    delete[] arr;
}

void Stack::push(int value) {
    if (isFull()) {
        throw std::overflow_error("Stack overflow");
    }
    arr[++topIndex] = value;
}

int Stack::pop() {
    if (isEmpty()) {
        throw std::underflow_error("Stack underflow");
    }
    return arr[topIndex--];
}

int Stack::top() const {
    if (isEmpty()) {
        throw std::underflow_error("Stack is empty");
    }
    return arr[topIndex];
}

bool Stack::isEmpty() const {
    return topIndex == -1;
}

bool Stack::isFull() const {
    return topIndex == capacity - 1;
}

}
