### CPP-Workshop : AVL Tree, Stack, and Apartment Search Utility in C++

This project is a comprehensive implementation exercise for C++ programming, focusing on data structures, algorithm efficiency, and leveraging STL features. Developed as part of the Hebrew University of Jerusalem's Computer Science and Engineering curriculum, it introduces advanced programming techniques while solving practical problems like apartment searching.

---

### Project Features

#### 1. **Apartment Class**
The `Apartment` class represents an apartment with spatial coordinates and supports the following features:
- **Constructor**: Initialize an apartment with x and y coordinates.
- **Comparison Operators**: Define `<`, `>`, and `==` for sorting and equality checks, based on the distance to a fixed reference point.
- **Getters**: Retrieve x and y coordinates.
- **Stream Operator**: Overloads `<<` for formatted output of coordinates `(x, y)`.

#### 2. **Stack Implementation**
A custom stack structure supports efficient storage and retrieval of `Apartment` objects. Key features include:
- **Constructors**: Initialize an empty stack or populate it from a vector of apartment coordinates.
- **Core Methods**:
  - `push`: Add an apartment to the top of the stack.
  - `pop`: Remove the top element (throws an exception for an empty stack).
  - `top`: Retrieve the top element without removing it.
  - `size`: Return the stack size.
  - `empty`: Check if the stack is empty.
- **Iterator Support**: Enables traversing stack elements from top to bottom using a forward iterator.

#### 3. **AVL Tree Implementation**
The `AVL` tree is a self-balancing binary search tree optimized for efficient search operations. Features include:
- **Constructors**:
  - Default constructor for an empty tree.
  - Copy constructor and a constructor to populate the tree from a vector of apartment coordinates.
- **Core Operations**:
  - `insert`: Add a new apartment, maintaining AVL balance.
  - `erase`: Remove an apartment, rebalancing the tree as necessary.
- **Traversal Support**: Implements a `preorder` iterator for navigating the tree nodes.
- **Binary Search**: Perform O(h) searches for a specific apartment, where `h` is the tree height.

#### 4. **Generic Search Function**
A template function `find` allows searching through any container supporting input iterators. This generic implementation demonstrates flexibility in algorithm design.

#### 5. **Performance Comparison**
The project includes benchmarking to compare insertion and search times across:
- A stack structure.
- The AVL tree.
- An unordered set (`std::unordered_set`).

Performance metrics for three datasets (100, 1,000, and 10,000 apartments) are measured and recorded.

---

### Key Implementation Highlights

1. **Memory Management**:
   - Compliant with C memory management principles (`malloc`, `free`).
   - Adheres to the Rule of Three for copy constructors, destructors, and assignment operators.
   
2. **Error Handling**:
   - Robust exception management using informative error messages for stack operations (`out_of_range`).

3. **STL and Custom Solutions**:
   - Avoids pre-defined STL structures like `std::vector` in key implementations, promoting deeper understanding.

4. **AVL Balance Maintenance**:
   - Implements single and double rotations to correct imbalance after insertions or deletions.

---

### Files Included
- **Core Implementation**:
  - `Apartment.h` and `Apartment.cpp`
  - `Stack.h` and `Stack.cpp`
  - `AVL.h` and `AVL.cpp`
  - `Find.h` (generic search function)
- **Bonus Performance Evaluation**:
  - `Bonus.cpp` and `RESULTS`

---

### How to Run
1. Clone the repository.
2. Compile using the provided `Makefile`:  
   ```bash
   make ex6
   ```
3. Run the binary with command-line arguments as specified in the bonus exercise.

---

### Learning Outcomes
- Understanding AVL trees, balancing techniques, and traversal methods.
- Custom stack implementation with iterator support.
- Utilizing STL for generic algorithms and performance comparisons.
- Exception handling and robust memory management in C++.
