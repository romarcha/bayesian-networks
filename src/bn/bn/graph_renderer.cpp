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

    // Get ancestors of BMI
    std::vector<Node*> ancestors = graph->get_ancestors("\"BMI\"");

    //Write nodes
    for(unsigned int i = 0; i < graph->get_number_of_nodes(); i++)
    {
        dot_code << "";
        dot_code << graph->get_node(i)->get_name();
        if(graph->get_node(i)->get_name() == "\"BMI\"")
        {
            dot_code << " [style = filled, shape = diamond, color = \"#FE610030\"";
            dot_code <<"]";
        }
        if(std::find(ancestors.begin(), ancestors.end(), graph->get_node(i)) != ancestors.end())
        {
            dot_code << " [style = filled, color = \"#FE610060\"";
            dot_code <<"]";            
        }
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
        double width = 0;
        if (std::abs(graph->get_edge(j)->m_width) > 2)
        {
            width = 2;
        }
        else if (std::abs(graph->get_edge(j)->m_width) < 1)
        {
            width = 1;
        }
        else
        {
            width = std::abs(graph->get_edge(j)->m_width);
        }

        dot_code << "[penwidth = "<< width;
        
        if(graph->get_edge(j)->m_width > 0)
        {
            dot_code << ", arrowhead = open";
        }
        else if (graph->get_edge(j)->m_width < 0)
        {
            dot_code << ", arrowhead = tee";
        }

        if(graph->get_edge(j)->m_width > 0)
        {
            dot_code << ", color = \"#648FFF\"";
        }
        else if (graph->get_edge(j)->m_width < 0)
        {
            dot_code << ", color = \"#FE6100\"";
        }

        dot_code <<"]";

        dot_code << ";\n";
    }

    dot_code << "}";

    return dot_code.str();
}

}