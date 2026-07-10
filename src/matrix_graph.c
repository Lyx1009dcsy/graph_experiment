#include "matrix_graph.h"

MatrixGraph* create_graph(void) {
    MatrixGraph* graph = (MatrixGraph*)malloc(sizeof(MatrixGraph));
    if (graph == NULL) {
        printf("内存分配失败！\n");
        return NULL;
    }
    graph->vertex_count = 0;
    for (int i = 0; i < MAX_VERTEX; i++) {
        for (int j = 0; j < MAX_VERTEX; j++) {
            graph->adjacency[i][j] = INF;
        }
        graph->adjacency[i][i] = 0;
    }
    printf("图创建成功！\n");
    return graph;
}

int add_vertex(MatrixGraph* graph, const char* name) {
    if (graph == NULL) {
        printf("图未初始化！\n");
        return -1;
    }
    if (graph->vertex_count >= MAX_VERTEX) {
        printf("顶点数量已达上限(%d)！\n", MAX_VERTEX);
        return -1;
    }
    strncpy(graph->vertices[graph->vertex_count].name, name, sizeof(graph->vertices[graph->vertex_count].name) - 1);
    graph->vertices[graph->vertex_count].name[sizeof(graph->vertices[graph->vertex_count].name) - 1] = '\0';
    int index = graph->vertex_count;
    graph->vertex_count++;
    printf("成功添加景点: %s (编号: %d)\n", name, index);
    return index;
}

int add_edge(MatrixGraph* graph, int from, int to, int weight) {
    if (graph == NULL) {
        printf("图未初始化！\n");
        return -1;
    }
    if (from < 0 || from >= graph->vertex_count || to < 0 || to >= graph->vertex_count) {
        printf("顶点编号无效！当前顶点数量: %d\n", graph->vertex_count);
        return -1;
    }
    if (weight <= 0) {
        printf("路径权重必须大于0！\n");
        return -1;
    }
    graph->adjacency[from][to] = weight;
    graph->adjacency[to][from] = weight;
    printf("成功添加路径: %s -> %s, 权重: %d\n", graph->vertices[from].name, graph->vertices[to].name, weight);
    return 0;
}

void print_matrix(MatrixGraph* graph) {
    if (graph == NULL) {
        printf("图未初始化！\n");
        return;
    }
    printf("\n邻接矩阵:\n");
    printf("    ");
    for (int i = 0; i < graph->vertex_count; i++) {
        printf("%-10s", graph->vertices[i].name);
    }
    printf("\n");
    for (int i = 0; i < graph->vertex_count; i++) {
        printf("%-10s", graph->vertices[i].name);
        for (int j = 0; j < graph->vertex_count; j++) {
            if (graph->adjacency[i][j] == INF) {
                printf("%-10s", "INF");
            } else {
                printf("%-10d", graph->adjacency[i][j]);
            }
        }
        printf("\n");
    }
}

void show_all_vertices(MatrixGraph* graph) {
    if (graph == NULL) {
        printf("图未初始化！\n");
        return;
    }
    printf("\n所有景点列表:\n");
    for (int i = 0; i < graph->vertex_count; i++) {
        printf("  [%d] %s\n", i, graph->vertices[i].name);
    }
    if (graph->vertex_count == 0) {
        printf("  (暂无景点，请先添加景点)\n");
    }
}

void free_graph(MatrixGraph* graph) {
    if (graph != NULL) {
        free(graph);
        printf("图已销毁！\n");
    }
}
