//agassinoa20@gmail.com
#ifndef STACK_HPP
#define STACK_HPP

namespace ds
{
    class Stack
    {
    private:
        int *arr;
        int capacity;
        int topIndex;
    public:
        Stack(int cap = 100);  // Constructor
        ~Stack(); // Destructor

        void push(int value);  // Push element to the top
        int pop(); // Remove and return the top element
        int top() const; // Return the top element without removing
        bool isEmpty() const;  // Check if stack is empty
        bool isFull() const;   // Check if stack is full
    };
    
    
} // namespace ds

#endif