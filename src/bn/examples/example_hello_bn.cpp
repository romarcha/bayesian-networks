// "Hello Bayesian Network!" example program

#include <bn/bn/graph.h>
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
    graph.add_node("A");
    graph.add_node("B");
    graph.add_node("C");
    graph.add_node("D");
    graph.add_node("E");
    graph.add_node("F");
    graph.add_node("G");
    graph.add_node("H");
    graph.add_edge("A","B");
    graph.add_edge("D","B");
    graph.add_edge("C","B");
    graph.add_edge("D","C");
    graph.add_edge("A","E");
    graph.add_edge("A","G");
    graph.add_edge("E","H");
    graph.add_edge("G","H");
    graph.add_edge("D","H");
    graph.add_edge("H","C");
    graph.add_edge("D","A");
    graph.add_edge("D","A");
    graph.add_edge("E","D");
    graph.draw("./","hello_bn");
    auto order = graph.topological_order();
    if(graph.is_acyclic())
    {
        std::cout<<"Graph is a DAG!, with topological order:"<<std::endl;
        for(bn::Node* node : order)
        {
            std::cout<<node->get_name();
        }
        std::cout<<std::endl;
    }
    else
    {
        std::cout<<"Graph has cycles."<<std::endl;
    }
    return 0;
}
