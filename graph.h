
// dhruvil
// Wed 05 Jun 2019 11:56:44 PM IST
// graph.h

#if !defined(GRAPH_H)
#define GRAPH_H 1

#include "matrix.h"

typedef struct _graph {
    matrix adj_mat;

    long long no_vertex;
    long long no_edge;

    bool has_loops;
    bool is_directed;
    bool multiple_edges;
    bool is_simple;
} graph;

// Graph constructor
void graph_ctor(graph *gph);

// Graph destructor
void graph_dtor(graph *gph);

// Graph initializer
void graph_init(graph *gph);

// Graph print
void graph_print(graph *gph);

// Graph pretty print
void graph_pprint(graph *gph);

#endif // GRAPH_H
