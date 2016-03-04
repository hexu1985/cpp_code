#include <stdexcept>
#include <queue>
#include <cassert>
#include <thread>

#include "undirected_graph.h"
#include "node.h"
#include "link.h"

using namespace std;

bool Undirected_graph::is_vertex_in(vertex_id_type v)
{
    return (ver_lst_.find(v) != ver_lst_.end());
}

bool Undirected_graph::is_edge_in(const edge_type &e)
{
    return (link_map_.find(e) != link_map_.end()); 
}

Undirected_graph::edge_type Undirected_graph::make_edge(
    vertex_id_type v1, vertex_id_type v2)
{
    return make_tuple(v1, v2);
}

Undirected_graph::edge_type Undirected_graph::reverse_edge(const edge_type &e)
{
    vertex_id_type v1, v2;
    std::tie(v1, v2) = e;
    return make_edge(v2, v1);
}

void Undirected_graph::add_vertex(Node *node)
{
    auto id = node->id();
    if (is_vertex_in(id)) {
        throw runtime_error("vertex already in graph!");
    }

    ver_lst_[id] = vertex_type();
    node_map_[id] = node;
}

void Undirected_graph::del_vertex(Node *node)
{
    auto id = node->id();
    if (!is_vertex_in(id)) {
        throw runtime_error("vertex not in graph!");
    }

    ver_lst_.erase(id);
    node_map_.erase(id);

    // remove all edge associate with this vertex
    for (auto &v: adj_lst_[id]) {
        if (v != id) {
            adj_lst_[v].erase(id);
        }
        link_map_.erase(make_edge(id, v));
        link_map_.erase(make_edge(v, id));
    }
    adj_lst_.erase(id);
}

void Undirected_graph::add_edge(Link *link)
{
    // get vertex of link
    auto v1 = link->fromNode()->id();
    auto v2 = link->toNode()->id();
    auto e = make_edge(v1, v2);
    if (!(is_vertex_in(v1) && is_vertex_in(v2))) {
        throw runtime_error("please add vertex first!");
    }
    if (is_edge_in(e)) {  // if edge already in graph, throw exception
        throw runtime_error("edge already in graph!");
    }

    // add link to map
    link_map_[e] = link;
    link_map_[reverse_edge(e)] = link;

    // add edge to adjacency list
    adj_lst_[v1].insert(v2);
    adj_lst_[v2].insert(v1);
}

void Undirected_graph::del_edge(Link *link)
{
    // get vertex of link
    auto v1 = link->fromNode()->id();
    auto v2 = link->toNode()->id();
    auto e = make_edge(v1, v2);
    if (!is_edge_in(e)) {  // if edge not in graph, throw exception
        throw runtime_error("edge not in graph!");
    }

    // remove link from map
    link_map_.erase(e);
    link_map_.erase(reverse_edge(e));

    // remove edge from adjacency list
    adj_lst_[v1].erase(v2);
    adj_lst_[v2].erase(v1);
}

void Undirected_graph::bfs(Node *from)
{
    auto s = from->id();
    if (!is_vertex_in(s)) {
        throw runtime_error("vertex not in graph!");
    }

    for (auto &l: link_map_) {
        l.second->setColor(Qt::darkRed);
    }

    for (auto &u: ver_lst_) {
        u.second = vertex_type();
        paint_node(u);
    }

    ver_lst_[s].color = GRAY;
    ver_lst_[s].distance = 0;
    ver_lst_[s].parent = -1;
    paint_node(*ver_lst_.find(s));

    queue<vertex_id_type> q;
    q.push(s);
    while (!q.empty()) {
        auto u = q.front(); q.pop();
        for (auto v: adj_lst_[u]) {
            if (ver_lst_[v].color == WHITE) {
                ver_lst_[v].color = GRAY;
                ver_lst_[v].distance = ver_lst_[u].distance + 1;
                ver_lst_[v].parent = u;
                paint_node(*ver_lst_.find(v));
                paint_link(make_edge(u, v));
                q.push(v);
            }
        }
        ver_lst_[u].color = BLACK;
        paint_node(*ver_lst_.find(u));
    }

    node_map_[s]->setBackgroundColor(Qt::red);
}

void Undirected_graph::paint_node(const vertex_list_type::value_type &v)
{
    auto &id = v.first;
    auto &status = v.second;
    Node *node = node_map_[id];
    assert(node != NULL);

    QColor color = Qt::white;
    switch (status.color) {
    case WHITE:
        color = Qt::white;
        break;
    case GRAY:
        color = Qt::gray;
        break;
    case BLACK:
        color = Qt::black;
        break;
    default:
        assert(false);
    }
    node->setBackgroundColor(color);
}

void Undirected_graph::paint_link(const edge_type &e)
{
    Link *link = link_map_[e];
    assert(link != NULL);
    link->setColor(Qt::black, 3.0);
}

const Undirected_graph::vertex_type &Undirected_graph::get_vertex(vertex_id_type id)
{
    assert(is_vertex_in(id));
    return ver_lst_[id];
}
