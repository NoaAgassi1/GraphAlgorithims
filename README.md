# Graph Algorithms in C++

##  Project Overview

This project implements several fundamental graph algorithms in C++ using an object-oriented approach. The algorithms include:

- Breadth-First Search (BFS)
- Depth-First Search (DFS)
- Dijkstra's Shortest Path Algorithm
- Prim's Minimum Spanning Tree (MST)
- Kruskal's MST

The project uses custom-built data structures (Queue, PriorityQueue, UnionFind) and emphasizes modular design with reusable components.

---

##  Directory Structure

```
GraphAlgorithims/
├── include/                # Header files
│   ├── Algorithms.hpp
│   ├── graph.hpp
│   └── DataStructures/     # Queue, PriorityQueue, UnionFind headers
├── src/                    # Source files
│   ├── Algorithms.cpp
│   ├── graph.cpp
│   └── DataStructures/     # Corresponding implementations
├── tests/                  # Unit tests using doctest
│   ├── test_algorithms.cpp
│   └── test_data_structures.cpp
├── main.cpp                # Demo for running all algorithms
└── makefile                # Compilation and run targets
```

---

## Build & Run Instructions

### Compilation
To build the main executable and run all algorithm demonstrations:

```bash
make run
```

### Run Unit Tests

To run all tests (using doctest framework):

```bash
make run-tests-algo      # Tests for Algorithms
make run-tests-ds        # Tests for Data Structures
```

###  Clean Project

To remove all compiled files:

```bash
make clean
```

---

##  Algorithms Implemented

- **BFS:** Traverses the graph layer by layer, producing a BFS tree.
- **DFS:** Explores as deep as possible before backtracking, resulting in a DFS tree.
- **Dijkstra:** Computes shortest paths from a source to all other nodes using a priority queue.
- **Prim:** Constructs a minimum spanning tree starting from vertex 0, using a greedy approach.
- **Kruskal:** Constructs a minimum spanning tree using edge sorting and Union-Find for cycle detection.

All algorithms operate on an adjacency list representation of the graph.

---

##  Testing

The project uses the [doctest](https://github.com/doctest/doctest) testing framework. Test files are located in the `tests/` folder and include coverage for:

- Correctness of each algorithm
- Valid and invalid graph structures
- Queue and PriorityQueue behavior
- Union-Find operations

---

##  Authors

Developed by Noa Agassi.  
Based on guidelines provided in the course assignment.

---

##  Notes

- The code avoids use of STL containers like `std::priority_queue` in favor of manually implemented structures.
- The project is intended for educational purposes in a university-level C++ course.
