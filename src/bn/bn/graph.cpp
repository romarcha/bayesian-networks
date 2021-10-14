#include <bn/bn/graph.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

namespace bn
{

Graph::Graph()
{
    std::cout<<"Created Empty Graph"<<std::endl;
}

Graph::Graph(unsigned int n_nodes, bool fully_connected, bool directed, VerboseLevel verbose)
    :m_directed(directed)
    ,m_verbose(verbose)
{
    // This will create a fully connected graph
    if(fully_connected)
    {
        if(m_verbose > VERBOSE_MINIMAL)
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
        if(m_verbose > VERBOSE_MINIMAL)
        {
            std::cout<<"Creating graph with "<<n_nodes<<" nodes and no edges."<<std::endl;
        }
    }
}

void Graph::add_node(std::string node_name)
{
    std::cout<<"Adding node."<<std::endl;
    Node node(node_name);
    m_nodes.push_back(node);
    std::cout<<"New number of nodes is "<<m_nodes.size()<<"."<<std::endl;
}

unsigned int Graph::get_number_of_nodes() const
{
    return m_nodes.size();
}

void Graph::add_edge(unsigned int node_i, unsigned int node_j)
{
    std::cout<<"Adding edge."<<std::endl;
    std::pair<unsigned int, unsigned int> edge = std::make_pair(node_i,node_j);
    m_edges.push_back(edge);
    std::cout<<"New number of edges is "<<m_edges.size()<<"."<<std::endl;
}

unsigned int Graph::get_number_of_edges() const
{
    return m_edges.size();
}

bool Graph::is_directed() const
{
    return m_directed;
}

void Graph::set_directed(bool directed)
{
    m_directed = directed;
}

std::string Graph::get_dot()
{
    std::string str("");
    std::stringstream dot_code(str);

    if(is_directed())
    {
        dot_code << "digraph G {\n";
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
        dot_code << m_edges[j].first;
        dot_code << "->";
        dot_code << m_edges[j].second;
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

    std::cout<<dot_code<<std::endl;

    return !gvFreeContext(gvc);
}

}
