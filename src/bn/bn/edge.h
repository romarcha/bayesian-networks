#ifndef __BN_EDGE_H__
#define __BN_EDGE_H__

#include <string>

namespace bn
{

class Node;

class Edge
{
    public:
        Edge(Node* parent_node, Node* child_node, double width = 1.0);

    public:
        Node* m_parent_node;
        Node* m_child_node;

        double m_width;
};

}

#endif /* __BN_EDGE_H__ */
