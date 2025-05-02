//agassinoa20@gmail.com
#include "DataStructures/UnionFind.hpp"
#include <stdexcept>

namespace ds {

// Constructor: initialize n elements, each in its own set
UnionFind::UnionFind(int n) : size(n) {
    if (n <= 0) {
        throw std::runtime_error("Size must be positive");
    }

    parent = new int[n];
    rank = new int[n];
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

// Destructor: release allocated memory
UnionFind::~UnionFind() {
    delete[] parent;
    delete[] rank;
}

// Copy constructor: deep copy
UnionFind::UnionFind(const UnionFind& other) : size(other.size) {
    parent = new int[size];
    rank = new int[size];
    for (int i = 0; i < size; ++i) {
        parent[i] = other.parent[i];
        rank[i] = other.rank[i];
    }
}

// Copy assignment operator: deep copy with cleanup
UnionFind& UnionFind::operator=(const UnionFind& other) {
    if (this == &other) {
        return *this;
    }

    delete[] parent;
    delete[] rank;

    size = other.size;
    parent = new int[size];
    rank = new int[size];
    for (int i = 0; i < size; ++i) {
        parent[i] = other.parent[i];
        rank[i] = other.rank[i];
    }

    return *this;
}

// Find with path compression
int UnionFind::find(int x) {
    if (x < 0 || x >= size) {
        throw std::runtime_error("Invalid element index");
    }
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

// Union by rank
void UnionFind::unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY)
        return;

    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

// Check if x and y are in the same set
bool UnionFind::connected(int x, int y) const {
    return parent[x] == parent[y] || const_cast<UnionFind*>(this)->find(x) == const_cast<UnionFind*>(this)->find(y);
}

// getter for size
int UnionFind::getSize() const {
    return size;
}

}
