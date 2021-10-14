#ifndef __BN_GRAPH_H__
#define __BN_GRAPH_H__

#include <vector>
#include <bn/bn/node.h>

namespace bn
{

//! Verbose Level
/* Allows you to print different messages
 * for different debugging levels.
 * E.g. 0 is quiet, 1 is minimal, 2 is debug
 */
enum VerboseLevel
{
    VERBOSE_QUIET,
    VERBOSE_MINIMAL,
    VERBOSE_DEBUG
};

class Graph
{
    public:
        Graph();

        Graph(unsigned int n_nodes, bool fully_connected=false, bool directed=true, VerboseLevel verbose=VERBOSE_DEBUG);

        void add_node(std::string node_name);

        unsigned int get_number_of_nodes() const;

        void add_edge(unsigned int node_i, unsigned int node_j);

        unsigned int get_number_of_edges() const;

        bool is_directed() const;

        void set_directed(bool directed);

        std::string get_dot();

        bool draw(std::string output_path, std::string filename);
    protected:
        std::vector<Node> m_nodes;
        std::vector<std::pair<unsigned int, unsigned int> > m_edges;

        bool m_directed;

        //! Verbose Level
        VerboseLevel m_verbose;
};

}

#endif /* __BN_GRAPH_H__ */
