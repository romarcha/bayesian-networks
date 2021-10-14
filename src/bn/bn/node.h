#ifndef __BN_NODE_H__
#define __BN_NODE_H__

#include <string>

namespace bn
{

class Node
{
    public:
        Node(std::string name = "");

        std::string get_name();

    protected:
        std::string m_name;
};

}

#endif /* __BN_GRAPH_H__ */
