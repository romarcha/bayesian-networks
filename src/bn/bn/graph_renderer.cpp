#include <bn/graph_renderer.h>
#include <bn/graph.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

namespace bn
{


std::string GraphRenderer::get_dot(bn::Graph *graph)
{
    std::string str("");
    std::stringstream dot_code(str);

    if(graph->get_directed())
    {
        dot_code << "digraph G {\n";
    }
    else
    {
        dot_code << "graph G {\n";
    }

    //Write nodes
    for(unsigned int i = 0; i < graph->get_number_of_nodes(); i++)
    {
        dot_code << "";
        dot_code << graph->get_node(i)->get_name();
        dot_code << ";\n";
    }

    //Write edges
    for(unsigned int j = 0; j < graph->get_number_of_edges(); j++)
    {
        dot_code << "";
        dot_code << graph->get_edge(j)->m_parent_node->get_name();
        if(graph->get_directed())
        {
            dot_code << "->";
        }
        else
        {
            dot_code << "-";
        }
        
        dot_code << graph->get_edge(j)->m_child_node->get_name();
        
        //Insert formatting options for edge
        dot_code << "[penwidth = "<<std::abs(graph->get_edge(j)->m_width);
        /*
        if(m_edges[j]->m_width > 0)
        {
            dot_code << " color = green";
        }
        else if (m_edges[j]->m_width < 0)
        {
            dot_code << " color = red";
        }*/

        dot_code <<"]";

        dot_code << ";\n";
    }

    dot_code << "}";

    return dot_code.str();
}

}