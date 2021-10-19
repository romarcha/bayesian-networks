#include <bn/bn/graph.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

namespace bn
{

Graph::Graph(unsigned int n_nodes, bool directed, bool acyclic, bool fully_connected,  VerboseLevel verbose)
    :m_directed(directed)
    ,m_acyclic(acyclic)
    ,m_verbose(verbose)
{
    // This will create a fully connected graph, it should only be used as example
    if(fully_connected)
    {
        if(m_verbose >= VERBOSE_MINIMAL)
        {
            std::cout<<"Creating fully connected graph with "<<n_nodes<<" nodes. (Edges on by default between all nodes)"<<std::endl;
        }
        
        for(unsigned int i=0; i < n_nodes; i++)
        {
            this->add_node(std::to_string(i));
        }

        //! Now add all combinations of nodes as pairs in the edges.
        for(unsigned int i=0; i < n_nodes; i++)
        {
            for(unsigned int j=0; j < n_nodes; j++)
            {
                this->add_edge(i,j);
            }
        }
    }
    else
    {
        if(m_verbose >= VERBOSE_MINIMAL)
        {
            std::cout<<"Creating graph with "<<n_nodes<<" nodes and no edges."<<std::endl;
        }
    }
}

bool Graph::add_node(std::string node_name)
{
    bool success = false;
    if(m_verbose >= VERBOSE_DEBUG)
    {
        std::cout<<"Adding node."<<std::endl;
    }
    Node node(node_name);
    m_nodes.push_back(node);
    success = true;
    if(m_verbose >= VERBOSE_DEBUG)
    {
        std::cout<<"New number of nodes is "<<m_nodes.size()<<"."<<std::endl;
    }
    return success;
}

unsigned int Graph::get_number_of_nodes() const
{
    return m_nodes.size();
}

bool Graph::add_edge(unsigned int node_i, unsigned int node_j)
{
    Node &parent_node = m_nodes[node_i];
    Node &child_node = m_nodes[node_j];
    
    return add_edge(parent_node,child_node);
}

bool Graph::add_edge(std::string node_name_i, std::string node_name_j)
{


    return false;
}

bool Graph::add_edge(bn::Node &node_parent, bn::Node &node_child)
{
    bool success = false;
    if(m_verbose >= VERBOSE_DEBUG)
    {
        std::cout<<"Adding edge."<<std::endl;
    }
    // Check if edge can be added according to the definition of this graph.
    bn::Edge edge(node_parent,node_child);
    m_edges.push_back(edge);
    
    if(m_verbose >= VERBOSE_DEBUG)
    {
        std::cout<<"New number of edges is "<<m_edges.size()<<"."<<std::endl;
    }
    return success;
}

unsigned int Graph::get_number_of_edges() const
{
    return m_edges.size();
}

bool Graph::is_directed() const
{
    return m_directed;
}

bool Graph::is_acyclic() const
{
    return m_acyclic;
}

Node* Graph::get_node(std::string name)
{
    Node *node = NULL;
    for(unsigned int node_idx = 0; node_idx < get_number_of_nodes(); node_idx++)
    {
        if(m_nodes[node_idx].get_name() == name)
        {
            node = &(m_nodes[node_idx]);
            break;
        }
    }
    return node;
}

std::vector<Node*> Graph::get_parents(std::string node_name)
{
    return get_parents(*get_node(node_name));
}

std::vector<Node*> Graph::get_parents(bn::Node &node_of_interest)
{
    if(m_verbose >= VERBOSE_DEBUG)
    {
        std::cout<<"Getting parents of "<<node_of_interest.get_name()<<":"<<std::endl;
    }
    std::vector<Node*> parents;
    for(unsigned int edge_idx = 0; edge_idx < get_number_of_edges(); edge_idx++)
    {
        if(m_edges[edge_idx].m_child_node == &node_of_interest)
        {
            parents.push_back(m_edges[edge_idx].m_parent_node);
            if(m_verbose >= VERBOSE_DEBUG)
            {
                std::cout<<m_edges[edge_idx].m_parent_node->get_name()<<std::endl;
            }
        }
    }
    if(m_verbose >= VERBOSE_DEBUG)
    {
        std::cout<<"--------------"<<std::endl;
    }
    return parents;
}

std::vector<Node*> Graph::get_children(std::string node_name)
{
    return get_children(*get_node(node_name));
}

std::vector<Node*> Graph::get_children(bn::Node &node_of_interest)
{
    if(m_verbose >= VERBOSE_DEBUG)
    {
        std::cout<<"Getting children of "<<node_of_interest.get_name()<<":"<<std::endl;
    }
    std::vector<Node*> children;
    for(unsigned int edge_idx = 0; edge_idx < get_number_of_edges(); edge_idx++)
    {
        if(m_edges[edge_idx].m_parent_node == &node_of_interest)
        {
            children.push_back(m_edges[edge_idx].m_child_node);
            if(m_verbose >= VERBOSE_DEBUG)
            {
                std::cout<<m_edges[edge_idx].m_child_node->get_name()<<std::endl;
            }
        }
    }
    if(m_verbose >= VERBOSE_DEBUG)
    {
        std::cout<<"--------------"<<std::endl;
    }
    return children;
}

std::string Graph::get_dot()
{
    std::string str("");
    std::stringstream dot_code(str);

    if(is_directed())
    {
        dot_code << "digraph G {\n";
    }
    else
    {
        dot_code << "graph G {\n";
    }

    //Write nodes
    for(unsigned int i = 0; i < this->get_number_of_nodes(); i++)
    {
        dot_code << "";
        dot_code << m_nodes[i].get_name();
        dot_code << ";\n";
    }

    //Write edges
    for(unsigned int j = 0; j < this->get_number_of_edges(); j++)
    {
        dot_code << "";
        dot_code << m_edges[j].m_parent_node->get_name();
        dot_code << "->";
        dot_code << m_edges[j].m_child_node->get_name();
        dot_code << ";\n";
    }

    dot_code << "}";

    return dot_code.str();
}

bool Graph::draw(std::string output_path, std::string filename)
{
    //! Frist we'll generate the .dot code corresponding to the graph.
    std::string dot_code = this->get_dot();
    std::string output_dot_filename = output_path+filename+".dot";
    std::ofstream out(output_dot_filename);
    out << dot_code;
    out.close();

    std::string o_arg = std::string("-o") + output_path + filename + ".pdf";
    char* args[] = {const_cast<char*>("dot"), const_cast<char*>("-Tpdf"),
    const_cast<char*>(output_dot_filename.c_str()), 
    const_cast<char*>(o_arg.c_str()) };

    const int argc = sizeof(args)/sizeof(args[0]);
    Agraph_t *g, *prev = NULL;
    GVC_t* gvc;
    
    gvc = gvContext();
    gvParseArgs(gvc, argc, args);

    while ((g = gvNextInputGraph(gvc)))
    {
        if (prev)
        {
            gvFreeLayout(gvc, prev);
            agclose(prev);
        }
            gvLayoutJobs(gvc, g);
            gvRenderJobs(gvc, g);
            prev = g;
    }
    if(m_verbose >= VERBOSE_DEBUG)
    {
        std::cout<<dot_code<<std::endl;
    }
    

    return !gvFreeContext(gvc);
}

}
