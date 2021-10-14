#include <bn/bn/node.h>
#include <iostream>

namespace bn
{

Node::Node(std::string name)
    :m_name(name)
{
    std::cout<<"Created Node"<<std::endl;
}

std::string Node::get_name()
{
    return m_name;
}   

}
