// "Hello Bayesian Network!" example program

#include <bn/bn/graph.h>
#include <graphviz/gvc.h>
#include <iostream>

int main()
{
    std::cout << "Hello Bayesian Network" << std::endl;

    unsigned int n_nodes = 5;
    bool directed = true;
    bool acyclic = true;
    bool fully_connected = true;
    bn::VerboseLevel verbose_level = bn::VERBOSE_DEBUG;
    bn::Graph graph(n_nodes, directed, acyclic, fully_connected, verbose_level);
    graph.draw("./","hello_bn");
    return 0;
}
