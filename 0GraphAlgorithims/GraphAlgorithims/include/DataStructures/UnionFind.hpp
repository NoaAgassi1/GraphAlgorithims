#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP

#include <stdexcept>

namespace ds {

class UnionFind {
private:
    int* parent;  // parent[i] = representative of i
    int* rank;    // rank[i] = depth estimate of tree
    int size;     // number of elements

public:
    // Constructor: initialize n disjoint sets
    UnionFind(int n);

    // Destructor
    ~UnionFind();

    // Copy constructor
    UnionFind(const UnionFind& other);

    // Copy assignment
    UnionFind& operator=(const UnionFind& other);

    // Returns the representative of the set containing x (with path compression)
    int find(int x);

    // Merges the sets containing x and y using union by rank
    void unite(int x, int y);

    // Returns true if x and y are in the same set
    bool connected(int x, int y) const;

    // Returns the number of elements (optional utility)
    int getSize() const;
};

} // namespace ds

#endif // UNION_FIND_HPP
