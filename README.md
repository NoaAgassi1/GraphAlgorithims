# Graph Algorithms Project in C++

## About the Project

This project was built to implement classic graph algorithms and supporting data structures in C++, without relying on STL containers. 
It demonstrates how these algorithms operate internally, using custom-built components for full control and understanding.

---

## What’s Implemented

### 🔹 Graph Algorithms (in `Algorithms` class under namespace `algo`)

- **BFS (Breadth-First Search)** – Explores the graph level by level using a custom `Queue`.
- **DFS (Depth-First Search)** – Recursively explores depth-first branches.
- **Dijkstra** – Computes shortest paths using `PriorityQueue`.
- **Prim** – Builds a minimum spanning tree using a greedy edge expansion.
- **Kruskal** – Builds a minimum spanning tree by sorting all edges and using `UnionFind`.

### 🔹 Custom Data Structures (in `DataStructures/`)

- `Queue` – Simple FIFO structure used by BFS.
- `Stack` – Manually implemented LIFO structure (available, though not used directly).
- `PriorityQueue` – Min-heap for Dijkstra and Prim.
- `UnionFind` – Disjoint-set structure for Kruskal’s algorithm with union by rank and path compression.

---

## Project Structure

```
GraphAlgorithims/
├── include/                # Header files
│   ├── graph.hpp
│   ├── Algorithms.hpp
│   └── DataStructures/
├── src/                    # Implementation files
│   ├── graph.cpp
│   ├── Algorithms.cpp
│   └── DataStructures/
├── tests/                  # Unit tests
├── main.cpp                # Main demonstration program
└── makefile                # Makefile with all targets
```

---


## How to Compile and Run the Project

### ➤ 1. Compile and Run the Main Program

This will compile `main.cpp` along with all required source files and run the demo of all algorithms:

```bash
make Main
```

You should see printed output showing:

- The original graph
- BFS traversal tree
- DFS traversal tree
- Dijkstra’s shortest path tree
- Prim’s minimum spanning tree (MST)
- Kruskal’s minimum spanning tree

---

### ➤ 2. Run All Unit Tests

To compile and run tests:

```bash
make test
```


---


### ➤ 3. Run with Valgrind to Check for Memory Leaks

This will run the main program under Valgrind's memory analysis:

```bash
make valgrind
```

You’ll get detailed memory usage info, and if everything is correct, you’ll see:

```
All heap blocks were freed -- no leaks are possible
```

> If you get a "command not found" error, install valgrind with:

```bash
sudo apt install valgrind
```

---

### ➤ 5. Clean All Generated Files

To remove all compiled executables and object files:

```bash
make clean
```
---

### Run Unit Tests

There are two sets of tests using the `doctest` framework:

```bash
make run-tests-algo
```
Runs the tests in `tests/test_algorithms.cpp` to verify correctness of BFS, DFS, Dijkstra, Prim, and Kruskal.

```bash
make run-tests-ds
```
Runs the tests in `tests/test_data_structures.cpp` to validate Queue, PriorityQueue, Stack, and UnionFind behavior.

---

###  Clean the Build

```bash
make clean
```
Removes all generated executables.

---

###  Memory Leak Check with Valgrind

To make sure there are no memory leaks, run:

```bash
make valgrind
```

This compiles the project and runs it with:

```bash
valgrind --leak-check=full --track-origins=yes ./graph_program
```

If Valgrind is not installed:

```bash
sudo apt install valgrind
```

---

## Sample Output (Abbreviated)

```
Original Graph:
Vertex 0: -> (v: 1, w: 2) -> (v: 2, w: 4)

BFS Tree:
Vertex 0: -> (v: 1, w: 2) -> (v: 2, w: 4)

Kruskal MST:
Vertex 0: -> (v: 1, w: 2)
Vertex 1: -> (v: 2, w: 1)
...
```

---

## Summary

This project focuses on building foundational components and understanding algorithm logic deeply. All structures were implemented from scratch and tested independently.

Developed as a hands-on, learning-focused C++ graph toolkit.
