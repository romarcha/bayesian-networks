#ifndef __BN_GRAPH_H__
#define __BN_GRAPH_H__

#include <vector>
#include <bn/bn/node.h>

namespace bn
{

class Graph
{
    public:
        Graph();
        Graph(unsigned int n_nodes, bool fully_connected=true);
        void add_node();
        void add_edge(unsigned int node_i, unsigned int node_j);
    
        void draw(std::string output_path);
    public:
        std::vector<Node> m_nodes;
        std::vector<std::pair<unsigned int, unsigned int> > m_edges;
};

}

#endif /* __BN_GRAPH_H__ */
