// Example program for reading CSV file into bayesian network

#include <bn/graph.h>
#include <bn/graph_renderer_graphviz.h>
#include <iostream>

int main()
{
    std::cout << "Reading CSV file containing edges in a Bayesian Network" << std::endl;

    unsigned int n_nodes = 0;
    bool directed = true;
    bool acyclic = true;
    bool fully_connected = false;
    bn::VerboseLevel verbose_level = bn::VERBOSE_DEBUG;
    bn::Graph graph(n_nodes, directed, acyclic, fully_connected, verbose_level);
    graph.populate_from_csv("../../src/bn/examples/example_graph.csv");

    bn::GraphRendererGraphviz renderer;
    renderer.draw(&graph, "./","bn_from_csv");
    //graph.draw("./","bn_from_csv");
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
