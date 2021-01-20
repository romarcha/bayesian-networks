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

        void add_node();
        void add_edge();
    public:
        std::vector<Node> m_nodes;
        std::vector<std::pair<unsigned int, unsigned int> > m_edges;
};

}

#endif /* __BN_GRAPH_H__ */
