#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX 20
#define INF 99999

typedef struct {
    char name[50];
} Vertex;

typedef struct {
    Vertex vertices[MAX_VERTEX];
    int adjacency[MAX_VERTEX][MAX_VERTEX];
    int vertex_count;
} MatrixGraph;

MatrixGraph* create_graph(void);
int add_vertex(MatrixGraph* graph, const char* name);
int add_edge(MatrixGraph* graph, int from, int to, int weight);
void print_matrix(MatrixGraph* graph);
void show_all_vertices(MatrixGraph* graph);
void free_graph(MatrixGraph* graph);

#endif
