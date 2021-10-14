add_library(
    ${LIB_BN}
    graph.cpp
    node.cpp
)

target_link_libraries(${LIB_BN} ${GRAPHVIZ_CGRAPH_LIBRARY} ${GRAPHVIZ_GVC_LIBRARY})
