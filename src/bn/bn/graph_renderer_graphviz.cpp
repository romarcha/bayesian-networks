#include <bn/graph_renderer_graphviz.h>
#include <string>
#include <sstream>
#include <fstream>
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

namespace bn
{

bool GraphRendererGraphviz::draw(bn::Graph *graph, std::string output_path, std::string filename)
{
    //! Frist we'll generate the .dot code corresponding to the graph.
    std::string dot_code = this->get_dot(graph);
    std::string output_dot_filename = output_path+filename+".dot";
    std::ofstream out(output_dot_filename);
    out << dot_code;
    out.close();

    std::string o_arg = std::string("-o") + output_path + filename + ".pdf";
    char* args[] = {const_cast<char*>("dot"), const_cast<char*>("-Tpdf"),
    const_cast<char*>(output_dot_filename.c_str()), 
    const_cast<char*>(o_arg.c_str()) };

    const int argc = sizeof(args)/sizeof(args[0]);
    Agraph_t *g, *prev = NULL;
    GVC_t* gvc;
    
    gvc = gvContext();
    gvParseArgs(gvc, argc, args);

    while ((g = gvNextInputGraph(gvc)))
    {
        if (prev)
        {
            gvFreeLayout(gvc, prev);
            agclose(prev);
        }
            gvLayoutJobs(gvc, g);
            gvRenderJobs(gvc, g);
            prev = g;
    }
    
    return !gvFreeContext(gvc);
}

}