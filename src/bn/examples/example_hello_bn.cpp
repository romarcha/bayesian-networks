// "Hello Bayesian Network!" example program

#include <bn/bn/graph.h>
#include <graphviz/gvc.h>
#include <iostream>

int main()
{
    std::cout << "Hello Bayesian Network" << std::endl;

    unsigned int n_nodes = 0;
    bool directed = true;
    bool acyclic = true;
    bool fully_connected = false;
    bn::VerboseLevel verbose_level = bn::VERBOSE_DEBUG;
    bn::Graph graph(n_nodes, directed, acyclic, fully_connected, verbose_level);
    graph.add_node("A");
    graph.add_node("B");
    graph.add_node("C");
    graph.add_node("D");
    graph.add_edge(0,1);
    graph.add_edge(3,2);
    graph.add_edge(2,1);
    graph.add_edge(3,1);
    graph.get_parents("A");
    graph.get_children("A");
    graph.get_parents("B");
    graph.get_children("B");
    graph.get_parents("C");
    graph.get_children("C");
    graph.get_parents("D");
    graph.get_children("D");
    graph.draw("./","hello_bn");
    return 0;
}
