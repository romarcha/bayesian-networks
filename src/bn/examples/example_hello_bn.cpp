// "Hello Bayesian Network!" example program
//

#include <bn/bn/graph.h>
#include <graphviz/gvc.h>
#include <iostream>

int main()
{
    std::cout << "Hello Bayesian Network" << std::endl;
    bool fully_connected = false;
    unsigned int n_nodes = 20;
    bn::Graph graph(n_nodes, fully_connected);
    return 0;
}
