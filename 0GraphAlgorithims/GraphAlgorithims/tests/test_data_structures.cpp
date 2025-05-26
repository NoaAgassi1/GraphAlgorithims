//agassinoa20@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Exceptions.hpp"
#include "DataStructures/Queue.hpp"
#include "DataStructures/Stack.hpp"
#include "DataStructures/PriorityQueue.hpp"
#include "DataStructures/UnionFind.hpp"

// -------------------- Queue --------------------

TEST_CASE("Queue - basic operations") {
    ds::Queue q(3);
    CHECK(q.isEmpty());
    q.enqueue(10);
    q.enqueue(20);
    CHECK(q.peek() == 10);
    CHECK(q.dequeue() == 10);
    CHECK(q.peek() == 20);
    q.dequeue();
    CHECK(q.isEmpty());
    CHECK_THROWS_AS(q.dequeue(), SimpleException);
}

TEST_CASE("Queue - wrap-around behavior") {
    ds::Queue q(3);
    q.enqueue(1);
    q.enqueue(2);
    q.dequeue();
    q.dequeue();
    q.enqueue(3);
    q.enqueue(4);
    CHECK(q.peek() == 3);
}

TEST_CASE("Queue - size tracking") {
    ds::Queue q(2);
    q.enqueue(1);
    CHECK(q.size() == 1);
    q.enqueue(2);
    CHECK(q.size() == 2);
    q.dequeue();
    CHECK(q.size() == 1);
}

// -------------------- Stack --------------------

TEST_CASE("Stack - basic operations") {
    ds::Stack s(2);
    CHECK(s.isEmpty());
    s.push(42);
    s.push(99);
    CHECK_THROWS_AS(s.push(100), SimpleException);
    CHECK(s.pop() == 99);
    CHECK(s.pop() == 42);
    CHECK_THROWS_AS(s.pop(), SimpleException);
}

TEST_CASE("Stack - top returns latest") {
    ds::Stack s(3);
    s.push(10);
    s.push(20);
    CHECK(s.top() == 20);
    s.pop();
    CHECK(s.top() == 10);
}

// -------------------- PriorityQueue --------------------

TEST_CASE("PriorityQueue - insert and extractMin") {
    ds::PriorityQueue pq(4);
    pq.insert(5, 3);
    pq.insert(7, 1);
    pq.insert(9, 2);

    CHECK(pq.extractMin() == 7);
    CHECK(pq.extractMin() == 9);
    CHECK(pq.extractMin() == 5);
    CHECK(pq.isEmpty());
}

TEST_CASE("PriorityQueue - peekMin") {
    ds::PriorityQueue pq(3);
    pq.insert(99, 10);
    CHECK(pq.peekMin() == 99);
}

TEST_CASE("PriorityQueue - decreaseKey updates priority") {
    ds::PriorityQueue pq(3);
    pq.insert(1, 10);
    pq.insert(2, 20);
    pq.decreaseKey(2, 5);
    CHECK(pq.extractMin() == 2);
}

TEST_CASE("PriorityQueue - decreaseKey to higher priority throws") {
    ds::PriorityQueue pq(2);
    pq.insert(1, 10);
    CHECK_THROWS_AS(pq.decreaseKey(1, 15), SimpleException);
}

TEST_CASE("PriorityQueue - decreaseKey on non-existing element throws") {
    ds::PriorityQueue pq(2);
    pq.insert(1, 10);
    CHECK_THROWS_AS(pq.decreaseKey(42, 5), SimpleException);
}

// -------------------- UnionFind --------------------

TEST_CASE("UnionFind - basic connectivity") {
    ds::UnionFind uf(5);
    CHECK(uf.find(0) == 0);
    CHECK_FALSE(uf.connected(0, 1));
    uf.unite(0, 1);
    CHECK(uf.connected(0, 1));
    uf.unite(1, 2);
    CHECK(uf.connected(0, 2));
    CHECK_FALSE(uf.connected(0, 3));
}

TEST_CASE("UnionFind - unite same element") {
    ds::UnionFind uf(4);
    uf.unite(1, 1);
    CHECK(uf.connected(1, 1));
}

TEST_CASE("UnionFind - find on invalid index throws") {
    ds::UnionFind uf(3);
    CHECK_THROWS_AS(uf.find(-1), SimpleException);
    CHECK_THROWS_AS(uf.find(3), SimpleException);
}

TEST_CASE("UnionFind - transitive connectivity") {
    ds::UnionFind uf(6);
    uf.unite(0, 1);
    uf.unite(1, 2);
    uf.unite(3, 4);
    uf.unite(4, 5);
    CHECK(uf.connected(0, 2));
    CHECK(uf.connected(3, 5));
    CHECK_FALSE(uf.connected(0, 3));
}
