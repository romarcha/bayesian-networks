#include <bn/bn/edge.h>
#include <bn/bn/node.h>
#include <iostream>

namespace bn
{

Edge::Edge(Node* parent_node, Node* child_node, double width)
    :m_parent_node(parent_node)
    ,m_child_node(child_node)
    ,m_width(width)
{

}


}
