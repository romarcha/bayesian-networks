#ifndef __BN_GRAPH_H__
#define __BN_GRAPH_H__

#include <vector>
#include <bn/bn/node.h>
#include <bn/bn/edge.h>

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
        Graph(unsigned int n_nodes, bool directed=true, bool acyclic = true, bool fully_connected=false, VerboseLevel verbose=VERBOSE_DEBUG);

        bool add_node(std::string node_name);

        unsigned int get_number_of_nodes() const;

        //!    
        /* Check if edge can be added according to the definition of this graph.
         The most trivial way is by checking if the introduction of the new edge introduces a cycle
         is to create a copy of the graph, add the edge to the copied graph and check for cycles
         Another possibility, to avoid the copy (useful for large graphs) is to add the edge
         to this graph, and then, if cycles are found remove the edge.
         This function will report success or failure and will also report error of failure
         (e.g. which cycles become present) */
        bool add_edge(unsigned int node_index_i, unsigned int node_index_j);
        bool add_edge(std::string node_name_i, std::string node_name_j);
        bool add_edge(bn::Node &node_i, bn::Node &node_j);

        unsigned int get_number_of_edges() const;

        bool is_directed() const;

        bool is_acyclic() const;



        std::string get_dot();

        bool draw(std::string output_path, std::string filename);

    protected:
        std::vector<Node> m_nodes;
        std::vector<Edge> m_edges;

        bool m_directed;

        bool m_acyclic;

        //! Verbose Level
        VerboseLevel m_verbose;

    private:
        Graph(){};
};

}

#endif /* __BN_GRAPH_H__ */
