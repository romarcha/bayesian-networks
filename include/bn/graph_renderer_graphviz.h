#ifndef __BN_GRAPH_RENDERER_GRAPHVIZ_H__
#define __BN_GRAPH_RENDERER_GRAPHVIZ_H__

#include <vector>
#include <bn/graph_renderer.h>

namespace bn
{

class GraphRendererGraphviz
    : public GraphRenderer
{
    public:
        bool draw(bn::Graph *graph, std::string output_path, std::string filename);
};

}

#endif /* __BN_GRAPH_RENDERER_H__ */