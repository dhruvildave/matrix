
// dhruvil
// Wed 05 Jun 2019 11:57:05 PM IST
// graph.c

#include "graph.h"

// Graph constructor
void graph_ctor(graph *gph) {
    gph->has_loops = -1;
    gph->is_directed = -1;
    gph->no_edge = -1;
    gph->no_vertex = -1;
    gph->multiple_edges = -1;

    mat_ctor(&gph->adj_mat);
}

// Graph destructor
void graph_dtor(graph *gph) {
    gph->has_loops = -1;
    gph->is_directed = -1;
    gph->no_edge = -1;
    gph->no_vertex = -1;
    gph->multiple_edges = -1;

    mat_dtor(&gph->adj_mat);
}

// Graph initializer
void graph_init(graph *gph) {
    char buf[BUFSIZ] = {0};
    char *rptr = buf;
    char *eptr = NULL;
    const int NUMBASE = 10;

    printf("Enter the number of vertex: ");
    fgets(buf, BUFSIZ, stdin);
    rptr = buf;
    gph->no_vertex = gph->adj_mat.row = gph->adj_mat.col =
        strtoll(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);

    gph->no_edge = gph->multiple_edges = gph->has_loops = 0;
    printf("Is the graph directed? (0 / 1) : ");
    fgets(buf, BUFSIZ, stdin);
    rptr = buf;
    gph->is_directed = strtol(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);

    if (gph->no_vertex > 0) {
        mat_alloc(&gph->adj_mat);
    }

    if (gph->no_vertex > 0) {
        printf("Enter list of space seperated vertex\n");
        printf("Enter -1 -1 to end the input:\n");
    }

    if (gph->is_directed == 1) {
        for (long long i = 0; fgets(buf, BUFSIZ, stdin); ++i) {
            rptr = buf;
            long long r = strtoll(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);
            long long c = strtoll(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);
            if (r == -1 && c == -1) {
                break;
            }

            if (r >= 0 && c >= 0 && r < gph->no_vertex && c < gph->no_vertex) {
                gph->adj_mat.mat[r][c]++;
                gph->no_edge++;

                if (gph->multiple_edges == 0 && gph->adj_mat.mat[r][c] > 1) {
                    gph->multiple_edges = 1; // checks for multiple edges
                }

                if (gph->has_loops == 0 && r == c &&
                    gph->adj_mat.mat[r][c] > 0) {
                    gph->has_loops = 1; // checks for loops
                }
            }
        }
    } else if (gph->is_directed == 0) {
        for (long long i = 0; fgets(buf, BUFSIZ, stdin); ++i) {
            rptr = buf;
            long long r = strtoll(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);
            long long c = strtoll(strtok_r(rptr, " ", &rptr), &eptr, NUMBASE);
            if (r == -1 && c == -1) {
                break;
            }

            if (r >= 0 && c >= 0 && r < gph->no_vertex && c < gph->no_vertex) {
                gph->adj_mat.mat[r][c]++;
                gph->adj_mat.mat[c][r]++;
                gph->no_edge++;

                if (gph->multiple_edges == 0 && (gph->adj_mat.mat[r][c] > 1 ||
                                                 gph->adj_mat.mat[c][r] > 1)) {
                    gph->multiple_edges = 1; // checks for multiple edges
                }

                if (gph->has_loops == 0 && r == c &&
                    gph->adj_mat.mat[r][c] > 0) {
                    gph->has_loops = 1; // checks for loops
                }
            }
        }
    }
}

// Graph print
void graph_print(graph *gph) { mat_print(&gph->adj_mat); }

// Graph pretty print
void graph_pprint(graph *gph) { mat_pprint(&gph->adj_mat); }
