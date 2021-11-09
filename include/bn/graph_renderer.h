#ifndef __BN_GRAPH_RENDERER_H__
#define __BN_GRAPH_RENDERER_H__

#include <string>

namespace bn
{

class Graph;

//! Abstract Graph Renderer
/* Object that maintains 
 *
 *
 */
class GraphRenderer
{
    public:
        virtual bool draw(bn::Graph *graph, std::string output_path, std::string filename) = 0;

        std::string get_dot(bn::Graph *graph);
};

}

#endif /* __BN_GRAPH_RENDERER_H__ */