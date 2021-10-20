# Bayesian Networks

This project brings together several methods from the Bayesian 
Network literature, including data generation, parameter inference and
structure learning. 

We are a long way away, but this is a good start.

The code is written in C++ and can be compiled using CMake, which
automatically finds dependencies and links the libraries and executables.

## Dependencies

CMake, Eigen, GCC,

MacOS

```bash
brew install cmake
brew install graphviz
brew install eigen
```

## Compilation

MacOS

```bash
mkdir build
cd build
cmake ..
make
```

## Run Tests


## Collaboration

To discuss collaboration contact Roman Marchant roman.marchant@sydney.edu.au.
At the moment we need help with the following tasks:

### TODO

- [x] Implement function for parents and children leaf.
- [x] Implement function for detecting cycles.
- [x] Implement function that finds topological order.
- [x] Check for cycles in the graphs when adding edges (only if acyclic).
- [x] Check if edge exists before adding a new edge.
- [x] Create graph from csv adjacency matrix, or edge list in csv.
    - [x] When adding an edge using node names, create nodes if they don't exist.
    - [x] Graph is created and edges have a width, which is read from the csv file.
    - [ ] Define color based on edge value.
    - [ ] Define transparency based on uncertainty.
- [x] Check when you add a node that there is not existent node with the same name.
- [ ] Implement functions for reachable nodes and d-separation.
- [ ] Add parameters to edges.
- [ ] Assign variable types to nodes (categorical, binary or continuous).
- [ ] Evaluate Conditional Independence.
- [ ] Generate data from graph.
- [ ] Likelihood calculation from data.
- [ ] Parameter estimation
- [ ] Structure learning
    - [ ] Random search
    - [ ] Order MCMC
    - [ ] Partition MCMC

- [ ] Handle errors and output with better practices than cout.
- [ ] Write tests for:
    - [ ] Check for cycles
    - [ ] Parent, Child and Leaf functions
    - [ ] Add good nodes and good edges.
    - [ ] Add repeated edges or nodes.
    - [ ] Test all above for directed and undirected graphs.
- [ ] Conduct diagnostic tool to map running time of algorithms with specific datasets.