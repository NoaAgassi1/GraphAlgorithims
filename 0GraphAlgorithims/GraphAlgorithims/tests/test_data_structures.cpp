#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "DataStructures/Queue.hpp"
#include "DataStructures/Stack.hpp"
#include "DataStructures/PriorityQueue.hpp"
#include "DataStructures/UnionFind.hpp"

// -------------------- Queue --------------------
TEST_CASE("Queue basic operations") {
    ds::Queue q(3);
    CHECK(q.isEmpty());
    q.enqueue(10);
    q.enqueue(20);
    CHECK(q.peek() == 10);
    CHECK(q.dequeue() == 10);
    CHECK(q.peek() == 20);
    q.dequeue();
    CHECK(q.isEmpty());
    CHECK_THROWS_AS(q.dequeue(), std::underflow_error);
}

// -------------------- Stack --------------------
TEST_CASE("Stack basic operations") {
    ds::Stack s(2);
    CHECK(s.isEmpty());
    s.push(42);
    s.push(99);
    CHECK_THROWS_AS(s.push(100), std::overflow_error);
    CHECK(s.pop() == 99);
    CHECK(s.pop() == 42);
    CHECK_THROWS_AS(s.pop(), std::underflow_error);
}

// -------------------- PriorityQueue --------------------
TEST_CASE("PriorityQueue insert and extractMin") {
    ds::PriorityQueue pq(4);
    pq.insert(5, 3);  // value 5, priority 3
    pq.insert(7, 1);
    pq.insert(9, 2);

    CHECK(pq.extractMin() == 7);  // priority 1
    CHECK(pq.extractMin() == 9);  // priority 2
    CHECK(pq.extractMin() == 5);  // priority 3
    CHECK(pq.isEmpty());
}

TEST_CASE("PriorityQueue peekMin") {
    ds::PriorityQueue pq(3);
    pq.insert(99, 10);
    CHECK(pq.peekMin() == 99);
}

// -------------------- UnionFind --------------------
TEST_CASE("UnionFind basic connectivity") {
    ds::UnionFind uf(5);
    CHECK(uf.find(0) == 0);
    CHECK(uf.connected(0, 1) == false);
    uf.unite(0, 1);
    CHECK(uf.connected(0, 1));
    uf.unite(1, 2);
    CHECK(uf.connected(0, 2));
    CHECK(!uf.connected(0, 3));
}
