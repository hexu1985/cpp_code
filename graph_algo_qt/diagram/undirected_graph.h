#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H

#include <tuple>
#include <map>
#include <unordered_set>
#include <unordered_map>

class Node;
class Link;

class Undirected_graph {
public:    
    typedef int vertex_id_type;

    enum vertex_color {
        WHITE, GRAY, BLACK
    };

    struct vertex_type {
        vertex_color    color;
        vertex_id_type  parent;
        int             distance; 

        vertex_type(): color(WHITE), parent(-1), distance(-1) {}
    };

    typedef std::unordered_map<vertex_id_type, std::unordered_set<vertex_id_type>> adjacency_list_type;
    typedef std::tuple<vertex_id_type, vertex_id_type> edge_type;
    typedef std::unordered_map<vertex_id_type, vertex_type> vertex_list_type;
    typedef std::unordered_map<vertex_id_type, Node *> node_map_type;
    typedef std::map<edge_type, Link *> link_map_type;

private:
    adjacency_list_type adj_lst_;
    vertex_list_type ver_lst_;
    node_map_type node_map_;
    link_map_type link_map_;

    // test if vertex in this graph
    bool is_vertex_in(vertex_id_type v);

    // test if edge in this graph
    bool is_edge_in(const edge_type &e);

    // make edge by point vertexs out 
    edge_type make_edge(vertex_id_type v1, vertex_id_type v2);

    // get reverse edge
    edge_type reverse_edge(const edge_type &e);

    // paint node
    void paint_node(const vertex_list_type::value_type &v);

    // paint link
    void paint_link(const edge_type &e);

public:
    void add_vertex(Node *node);

    void del_vertex(Node *node);

    void add_edge(Link *link);

    void del_edge(Link *link);

    // Breadth-first search
    void bfs(Node *from);

    const vertex_type &get_vertex(vertex_id_type id);
};

#endif // UNDIRECTED_GRAPH_H

