#include <bn/bn/graph.h>
#include <iostream>

namespace bn
{

Graph::Graph()
{
    std::cout<<"Created Empty Graph"<<std::endl;
}

Graph::Graph(unsigned int n_nodes, bool fully_connected)
{
    if(fully_connected)
    {
        std::cout<<"Creating fully connected graph with "<<n_nodes<<" nodes. (Edges on by default between all nodes)"<<std::endl;
        for(unsigned int i=0; i < n_nodes; i++)
        {
            this->add_node();
        }
        //! Now add all combinations of nodes as pairs in the edges.
        for(unsigned int i=0; i < n_nodes; i++)
        {
            for(unsigned int j=0; j < n_nodes; j++)
            {
                //Only one pair of connections between nodes not two (kind of like the superior diagonal of a connetivity matrix)
                if(j>=i)
                {
                    this->add_edge(i,j);
                }
            }
        }
    }
    else
    {
        std::cout<<"Creating graph with "<<n_nodes<<" nodes and no edges."<<std::endl;

    }
}

void Graph::add_node()
{
    std::cout<<"Adding node."<<std::endl;
    Node node;
    m_nodes.push_back(node);
    std::cout<<"New number of nodes is "<<m_nodes.size()<<"."<<std::endl;
}

void Graph::add_edge(unsigned int node_i, unsigned int node_j)
{
    std::cout<<"Adding edge."<<std::endl;
    std::pair<unsigned int, unsigned int> edge = std::make_pair(node_i,node_j);
    m_edges.push_back(edge);
    std::cout<<"New number of edges is "<<m_edges.size()<<"."<<std::endl;
}

void Graph::draw(std::string output_path)
{
    
}

}
