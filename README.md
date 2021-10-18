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

- Check for cycles in the graphs when adding edges (only if acyclic)
- Check if edge exists before adding a new edge
- Assign parameters to edges
- Assign variably types to nodes (categorical, binary or continuous)
- Evaluate Conditional Independence
- Generate data from graph
- Likelihood calculation from data
- Parameter estimation
- Structure learning
    - Random search
    - Order MCMC
    - Partition MCMC