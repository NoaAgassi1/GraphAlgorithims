//agassinoa20@gmail.com

#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

namespace ds {

class PriorityQueue {
private:
    int* vertices;       // values (or vertex IDs)
    int* priorities;   // corresponding priorities
    int capacity;    // max capacity of heap
    int count;       // current number of elements

    void bubbleUp(int index);     // restore heap upwards
    void bubbleDown(int index);   // restore heap downwards
    void expand();                // resize when full
    void swap(int i, int j);      // swap both arrays

public:
    PriorityQueue(int cap = 100);
    ~PriorityQueue();
    void decreaseKey(int value, int newPriority);
    void insert(int value, int prio);   // insert element with priority
    int extractMin();                   // remove and return element with smallest priority
    bool isEmpty() const;
    int peekMin() const;                // see minimum without removing
    int size() const;
};

} // namespace ds

#endif // PRIORITY_QUEUE_HPP
