#include <bn/graph.h>
#include <utils/csv_reader.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <queue>


namespace bn
{

Graph::Graph(unsigned int n_nodes, bool directed, bool acyclic, bool fully_connected,  VerboseLevel verbose)
    :m_directed(directed)
    ,m_acyclic(acyclic)
    ,m_verbose(verbose)
{
    // This will create a fully connected graph, it should only be used as example
    if(fully_connected)
    {
        if(m_verbose >= VERBOSE_MINIMAL)
        {
            std::cout<<"Creating fully connected graph with "<<n_nodes<<" nodes. (Edges on by default between all nodes)"<<std::endl;
        }
        
        for(unsigned int i=0; i < n_nodes; i++)
        {
            this->add_node(std::to_string(i));
        }

        //! Now add all combinations of nodes as pairs in the edges.
        for(unsigned int i=0; i < n_nodes; i++)
        {
            for(unsigned int j=0; j < n_nodes; j++)
            {
                this->add_edge(i,j);
            }
        }
    }
    else
    {
        if(m_verbose >= VERBOSE_MINIMAL)
        {
            std::cout<<"Creating graph with "<<n_nodes<<" nodes and no edges."<<std::endl;
        }
    }
}

bool Graph::populate_from_csv(std::string path)
{
    std::ifstream file(path);

    bn::CSVRow row;

    bool drop_first_line = true;
    
    unsigned int row_idx = 0;
    while(file >> row)
    {
        if(drop_first_line && row_idx == 0)
        {
            std::cout << "Dropping the first line: \n";
            std::cout << row.size() <<std::endl;
        }
        else
        {
            add_edge(std::string(row[0]),std::string(row[1]),std::stod(row[2]));
            std::cout << row[0] << "->" << row[1] << std::endl;
        }
        row_idx++;
    }

    return true;
}

bool Graph::add_node(std::string node_name)
{
    bool success = false;
    if(m_verbose >= VERBOSE_DEBUG)
    {
        std::cout<<"Adding node."<<std::endl;
    }
    //Check if node exists before adding it.
    for(unsigned int i = 0; i < get_number_of_nodes(); i++)
    {
        if(m_nodes[i]->get_name() == node_name)
        {
            std::cout<<"Node "<< node_name <<" cannot be added, because it already exists."<<std::endl;    
            return success;
        }
    }

    m_nodes.push_back(new Node(node_name));
    success = true;
    if(m_verbose >= VERBOSE_DEBUG)
    {
        std::cout<<"New number of nodes is "<<m_nodes.size()<<"."<<std::endl;
    }
    return success;
}

unsigned int Graph::get_number_of_nodes() const
{
    return m_nodes.size();
}

int Graph::get_index(Node* node_ptr)
{
    int index = -1;
    for(unsigned int node_idx = 0; node_idx < get_number_of_nodes(); node_idx++)
    {
        if(m_nodes[node_idx] == node_ptr)
        {
            index = node_idx;
            break;
        }
    }
    return index;
}

bool Graph::add_edge(unsigned int node_i, unsigned int node_j, double width)
{
    Node *parent_node = m_nodes[node_i];
    Node *child_node = m_nodes[node_j];
    
    return add_edge(parent_node,child_node, width);
}

bool Graph::add_edge(std::string node_name_i, std::string node_name_j, double width)
{
    Node *node_i = get_node(node_name_i);
    Node *node_j = get_node(node_name_j);

    //If an edge is created with a non existing node, then the node is created.
    bool reload_ptrs = false;
    if(node_i == NULL)
    {
        add_node(node_name_i);
        reload_ptrs = true;
    }
    if(node_j == NULL)
    {
        add_node(node_name_j);
        reload_ptrs = true;
    }
    if(reload_ptrs)
    {
        node_i = get_node(node_name_i);
        node_j = get_node(node_name_j);
    }

    return add_edge(node_i, node_j, width);
}

bool Graph::add_edge(bn::Node *node_parent, bn::Node *node_child, double width)
{
    bool success = false;
    if(m_verbose >= VERBOSE_DEBUG)
    {
        if(get_directed())
        {
            std::cout<<"Adding edge "<<node_parent->get_name()<<" -> "<<node_child->get_name()<<std::endl;
        }
        else
        {
            std::cout<<"Adding edge "<<node_parent->get_name()<<" - "<<node_child->get_name()<<std::endl;
        }
    }

    //First check if the edge already exists
    for(unsigned int edge_idx = 0; edge_idx < get_number_of_edges(); edge_idx++)
    {
        if(m_edges[edge_idx]->m_parent_node == node_parent && m_edges[edge_idx]->m_child_node == node_child)
        {
            std::cout<<"Error: edge between "<<node_parent->get_name()<<" and "<<node_child->get_name()<<" already exists."<<std::endl;
            return false;
        }
    }

    //First check if the edge is NOT
    for(unsigned int edge_idx = 0; edge_idx < get_number_of_blacklisted_edges(); edge_idx++)
    {
        if(m_blacklist_edges[edge_idx]->m_parent_node == node_parent && m_blacklist_edges[edge_idx]->m_child_node == node_child)
        {
            std::cout<<"Error: edge between "<<node_parent->get_name()<<" and "<<node_child->get_name()<<" is blacklisted."<<std::endl;
            return false;
        }
    }

    m_edges.push_back(new bn::Edge(node_parent,node_child,width));
    success = true;

    //! If this graph is supposed to be acyclic, but the introduction of this edge made it non acyclic.
    if(get_acyclic() && !is_acyclic())
    {
        std::cout<<"Error: cannot introduce the edge between "<<node_parent->get_name()<<" and "<<node_child->get_name()<<std::endl;
        m_edges.pop_back();
        success = false;
    }
    
    if(m_verbose >= VERBOSE_DEBUG)
    {
        std::cout<<"New number of edges is "<<m_edges.size()<<"."<<std::endl;
    }
    return success;
}

Edge* Graph::get_edge(unsigned int index)
{
    return m_edges[index];
}

unsigned int Graph::get_number_of_edges() const
{
    return m_edges.size();
}

bool Graph::add_blacklist(unsigned int node_index_i, unsigned int node_index_j, double width)
{
    Node *parent_node = m_nodes[node_index_i];
    Node *child_node = m_nodes[node_index_j];
    
    return add_blacklist(parent_node,child_node, width);
}

bool Graph::add_blacklist(std::string node_name_i, std::string node_name_j, double width)
{
    Node *node_i = get_node(node_name_i);
    Node *node_j = get_node(node_name_j);

    //If an edge is created with a non existing node, then the node is created.
    bool reload_ptrs = false;
    if(node_i == NULL)
    {
        add_node(node_name_i);
        reload_ptrs = true;
    }
    if(node_j == NULL)
    {
        add_node(node_name_j);
        reload_ptrs = true;
    }
    if(reload_ptrs)
    {
        node_i = get_node(node_name_i);
        node_j = get_node(node_name_j);
    }

    return add_blacklist(node_i, node_j, width);
}
        
bool Graph::add_blacklist(bn::Node *node_parent, bn::Node *node_child, double width)
{
    bool success = false;
    if(m_verbose >= VERBOSE_DEBUG)
    {
        if(get_directed())
        {
            std::cout<<"Adding blacklisted edge "<<node_parent->get_name()<<" -> "<<node_child->get_name()<<std::endl;
        }
        else
        {
            std::cout<<"Adding blacklisted edge"<<node_parent->get_name()<<" - "<<node_child->get_name()<<std::endl;
        }
    }

    //First check if the edge already exists
    for(unsigned int edge_idx = 0; edge_idx < get_number_of_blacklisted_edges(); edge_idx++)
    {
        if(m_blacklist_edges[edge_idx]->m_parent_node == node_parent && m_blacklist_edges[edge_idx]->m_child_node == node_child)
        {
            std::cout<<"Error: edge between "<<node_parent->get_name()<<" and "<<node_child->get_name()<<" already exists."<<std::endl;
            return false;
        }
    }


    m_blacklist_edges.push_back(new bn::Edge(node_parent,node_child,width));
    success = true;
    
    if(m_verbose >= VERBOSE_DEBUG)
    {
        std::cout<<"New number of edges is "<<m_blacklist_edges.size()<<"."<<std::endl;
    }
    return success;
}

Edge* Graph::get_blacklist_element(unsigned int index)
{
    return m_blacklist_edges[index];
}

unsigned int Graph::get_number_of_blacklisted_edges() const
{
    return m_blacklist_edges.size();
}

bool Graph::get_directed() const
{
    return m_directed;
}

bool Graph::get_acyclic() const
{
    return m_acyclic;
}

bool Graph::is_acyclic()
{
    bool is_acyclic = false;
    if (topological_order().size() > 0)
        is_acyclic = true;
    return is_acyclic;
}

Node* Graph::get_node(std::string name)
{
    Node *node = NULL;
    for(unsigned int node_idx = 0; node_idx < get_number_of_nodes(); node_idx++)
    {
        if(m_nodes[node_idx]->get_name() == name)
        {
            node = m_nodes[node_idx];
            break;
        }
    }
    return node;
}

Node* Graph::get_node(unsigned int index)
{
    return m_nodes[index];
}

std::vector<Node*> Graph::get_ancestors(std::string node_name)
{
    return get_ancestors(get_node(node_name));
}

std::vector<Node*> Graph::get_ancestors(bn::Node *node_of_interest)
{
    std::vector<Node*> ancestors;

    //First add all parents of node of interest to ancestors.
    //Get the parents
    std::vector<Node*> parents = get_parents(node_of_interest);

    //Concatenate parents vector into ancestors
    ancestors.insert(
        ancestors.end(),
        std::make_move_iterator(parents.begin()),
        std::make_move_iterator(parents.end())
    );

    for(Node* parent : parents)
    {
        //Get the ancestors for each parent
        std::vector<Node*> parent_ancestors = get_ancestors(parent);
        ancestors.insert(
            ancestors.end(),
            std::make_move_iterator(parent_ancestors.begin()),
            std::make_move_iterator(parent_ancestors.end())    
        );
    }

    //The vector ancestors probably contains many duplicates at this points
    //we'll remove the duplicates.
    sort(ancestors.begin(), ancestors.end());
    ancestors.erase(unique(ancestors.begin(), ancestors.end()), ancestors.end());

    return ancestors;
}

std::vector<Node*> Graph::get_parents(std::string node_name)
{
    return get_parents(get_node(node_name));
}

std::vector<Node*> Graph::get_parents(bn::Node *node_of_interest)
{
    if(m_verbose >= VERBOSE_DEBUG)
    {
//        std::cout<<"Getting parents of "<<node_of_interest.get_name()<<":"<<std::endl;
    }
    std::vector<Node*> parents;
    for(unsigned int edge_idx = 0; edge_idx < get_number_of_edges(); edge_idx++)
    {
        if(m_edges[edge_idx]->m_child_node == node_of_interest)
        {
            parents.push_back(m_edges[edge_idx]->m_parent_node);
            if(m_verbose >= VERBOSE_DEBUG)
            {
//                std::cout<<m_edges[edge_idx].m_parent_node->get_name()<<std::endl;
            }
        }
    }
    if(m_verbose >= VERBOSE_DEBUG)
    {
//        std::cout<<"--------------"<<std::endl;
    }
    return parents;
}

std::vector<Node*> Graph::get_children(std::string node_name)
{
    return get_children(get_node(node_name));
}

std::vector<Node*> Graph::get_children(bn::Node *node_of_interest)
{
    if(m_verbose >= VERBOSE_DEBUG)
    {
        //std::cout<<"Getting children of "<<node_of_interest.get_name()<<":"<<std::endl;
    }
    std::vector<Node*> children;
    for(unsigned int edge_idx = 0; edge_idx < get_number_of_edges(); edge_idx++)
    {
        if(m_edges[edge_idx]->m_parent_node == node_of_interest)
        {
            children.push_back(m_edges[edge_idx]->m_child_node);
            if(m_verbose >= VERBOSE_DEBUG)
            {
                //std::cout<<m_edges[edge_idx].m_child_node->get_name()<<std::endl;
            }
        }
    }
    if(m_verbose >= VERBOSE_DEBUG)
    {
        //std::cout<<"--------------"<<std::endl;
    }
    return children;
}

std::vector<Node*> Graph::get_leaf_nodes()
{
    std::vector<Node*> leafs;
    for(unsigned int node_idx = 0; node_idx < get_number_of_nodes(); node_idx++)
    {
        if(get_children(m_nodes[node_idx]).size() == 0)
        {
            leafs.push_back(m_nodes[node_idx]);
        }
    }
    return leafs;
}

std::vector<int> Graph::indegree()
{
    std::vector<int> indegrees;
    for(unsigned int node_idx = 0; node_idx < get_number_of_nodes(); node_idx++)
    {
        indegrees.push_back(get_parents(m_nodes[node_idx]).size());
    }
    return indegrees;
}

std::vector<Node*> Graph::topological_order()
{
    // std::cout << "Topological Order" <<std::endl;
    //! Create a copy of the graph, to continuously remove nodes
    //! **Used a different algorithms which doesn't need the copy of the graph.
    // Graph aux_graph = *this;

    //! The indegree of each node in the array. Each element in the indegree 
    std::vector<int> indegree = this->indegree();

    std::vector<Node*> topological_ordering;

    // A que is used to store the nodes that go into the topological ordering
    std::queue<Node*> queue;

    for(unsigned int node_idx = 0; node_idx < get_number_of_nodes(); node_idx++)
    {
        if(indegree[node_idx] == 0)
        {
            queue.push(m_nodes[node_idx]);
        }
    }
    
    while(queue.size()>0)
    {

        Node* node_ptr = queue.front();
        topological_ordering.push_back(node_ptr);
        //std::cout << "Added to ordering: "<<node_ptr->get_name() <<std::endl;
        queue.pop();

        // Descrease the degreee of all affected nodes (children of the queued)
        auto children = get_children(node_ptr);
        for(Node* child : children)
        {
            int index = get_index(child);
            if (index >= 0)
            {
                indegree[index]--;
                if(indegree[index] == 0)
                {
                    queue.push(child);
                }
            }
        }
    }

    if(topological_ordering.size() != get_number_of_nodes())
    {
        // std::cout << "DAG has a cycle" << std::endl;
        topological_ordering.clear();
    }

    return topological_ordering;
}

}
