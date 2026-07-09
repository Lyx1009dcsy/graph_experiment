#include "matrix_graph.h"

/**
 * @brief 创建一个新的图
 * 
 * 动态分配内存创建图结构，并初始化邻接矩阵：
 * - 对角线元素设为0（表示顶点到自身的距离为0）
 * - 非对角线元素设为INF（表示初始时顶点之间无直接路径）
 * 
 * @return MatrixGraph* 返回创建的图指针，失败返回 NULL
 */
MatrixGraph* create_graph(void) {
    /* 动态分配图结构内存 */
    MatrixGraph* graph = (MatrixGraph*)malloc(sizeof(MatrixGraph));
    
    /* 检查内存分配是否成功 */
    if (graph == NULL) {
        printf("内存分配失败！\n");
        return NULL;
    }
    
    /* 初始化顶点数量为0 */
    graph->vertex_count = 0;
    
    /* 初始化邻接矩阵 */
    for (int i = 0; i < MAX_VERTEX; i++) {
        for (int j = 0; j < MAX_VERTEX; j++) {
            /* 初始时所有路径设为无穷大（无路径） */
            graph->adjacency[i][j] = INF;
        }
        /* 对角线设为0（自身到自身） */
        graph->adjacency[i][i] = 0;
    }
    
    printf("图创建成功！\n");
    return graph;
}

/**
 * @brief 向图中添加一个新景点（顶点）
 * 
 * 将景点名称复制到顶点数组中，并增加顶点计数。
 * 顶点编号从0开始递增，最大支持 MAX_VERTEX 个顶点。
 * 
 * @param graph 图指针
 * @param name 景点名称
 * @return int 返回新添加顶点的编号（从0开始），失败返回 -1
 */
int add_vertex(MatrixGraph* graph, const char* name) {
    /* 参数有效性检查 */
    if (graph == NULL) {
        printf("图未初始化！\n");
        return -1;
    }
    
    /* 检查顶点数量是否达到上限 */
    if (graph->vertex_count >= MAX_VERTEX) {
        printf("顶点数量已达上限(%d)！\n", MAX_VERTEX);
        return -1;
    }
    
    /* 将景点名称复制到顶点数组中 */
    strncpy(graph->vertices[graph->vertex_count].name, 
            name, 
            sizeof(graph->vertices[graph->vertex_count].name) - 1);
    
    /* 确保字符串以'\0'结尾，防止缓冲区溢出 */
    graph->vertices[graph->vertex_count].name[sizeof(graph->vertices[graph->vertex_count].name) - 1] = '\0';
    
    /* 返回新添加顶点的编号，然后递增计数 */
    int index = graph->vertex_count;
    graph->vertex_count++;
    
    printf("成功添加景点: %s (编号: %d)\n", name, index);
    return index;
}

/**
 * @brief 向图中添加一条路径（边）及其权重
 * 
 * 在邻接矩阵中设置两点之间的路径权重。
 * 本实现为无向图，因此会同时设置 from->to 和 to->from 的权重。
 * 
 * @param graph 图指针
 * @param from 起点顶点编号
 * @param to 终点顶点编号
 * @param weight 路径权重（必须为正整数）
 * @return int 成功返回0，失败返回 -1
 */
int add_edge(MatrixGraph* graph, int from, int to, int weight) {
    /* 参数有效性检查 */
    if (graph == NULL) {
        printf("图未初始化！\n");
        return -1;
    }
    
    /* 检查顶点编号是否在有效范围内 */
    if (from < 0 || from >= graph->vertex_count || 
        to < 0 || to >= graph->vertex_count) {
        printf("顶点编号无效！当前顶点数量: %d\n", graph->vertex_count);
        return -1;
    }
    
    /* 检查路径权重是否为正整数 */
    if (weight <= 0) {
        printf("路径权重必须大于0！\n");
        return -1;
    }
    
    /* 设置邻接矩阵值（无向图，双向设置） */
    graph->adjacency[from][to] = weight;
    graph->adjacency[to][from] = weight;
    
    /* 输出成功信息 */
    printf("成功添加路径: %s -> %s, 权重: %d\n", 
           graph->vertices[from].name, 
           graph->vertices[to].name, 
           weight);
    
    return 0;
}

/**
 * @brief 打印邻接矩阵
 * 
 * 以表格形式输出邻接矩阵，包含行和列的景点名称标签。
 * INF 表示两点之间无直接路径。
 * 
 * @param graph 图指针
 */
void print_matrix(MatrixGraph* graph) {
    /* 参数有效性检查 */
    if (graph == NULL) {
        printf("图未初始化！\n");
        return;
    }
    
    /* 输出矩阵标题 */
    printf("\n邻接矩阵:\n");
    
    /* 输出列标题（景点名称） */
    printf("    ");
    for (int i = 0; i < graph->vertex_count; i++) {
        printf("%-10s", graph->vertices[i].name);
    }
    printf("\n");
    
    /* 输出矩阵内容 */
    for (int i = 0; i < graph->vertex_count; i++) {
        /* 输出行标题（景点名称） */
        printf("%-10s", graph->vertices[i].name);
        
        /* 输出该行的所有权重值 */
        for (int j = 0; j < graph->vertex_count; j++) {
            if (graph->adjacency[i][j] == INF) {
                /* 无路径时输出INF */
                printf("%-10s", "INF");
            } else {
                /* 有路径时输出权重值 */
                printf("%-10d", graph->adjacency[i][j]);
            }
        }
        printf("\n");
    }
}

/**
 * @brief 展示图中所有景点及其编号
 * 
 * 按编号顺序列出所有已添加的景点。
 * 
 * @param graph 图指针
 */
void show_all_vertices(MatrixGraph* graph) {
    /* 参数有效性检查 */
    if (graph == NULL) {
        printf("图未初始化！\n");
        return;
    }
    
    /* 输出标题 */
    printf("\n所有景点列表:\n");
    
    /* 遍历顶点数组，输出每个景点的编号和名称 */
    for (int i = 0; i < graph->vertex_count; i++) {
        printf("  [%d] %s\n", i, graph->vertices[i].name);
    }
    
    /* 若没有景点，输出提示信息 */
    if (graph->vertex_count == 0) {
        printf("  (暂无景点，请先添加景点)\n");
    }
}

/**
 * @brief 释放图占用的内存
 * 
 * 释放之前通过 create_graph() 分配的内存空间。
 * 
 * @param graph 图指针
 */
void free_graph(MatrixGraph* graph) {
    if (graph != NULL) {
        free(graph);
        printf("图已销毁！\n");
    }
}
