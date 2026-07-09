#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 最大顶点数量限制 */
#define MAX_VERTEX 20

/* 无穷大，表示两点之间无直接路径 */
#define INF 99999

/* 顶点结构体，用于存储景点信息 */
typedef struct {
    char name[50];  /* 景点名称 */
} Vertex;

/* 图结构体，基于邻接矩阵实现 */
typedef struct {
    Vertex vertices[MAX_VERTEX];     /* 顶点数组，存储所有景点 */
    int adjacency[MAX_VERTEX][MAX_VERTEX];  /* 邻接矩阵，存储路径权重 */
    int vertex_count;                /* 当前顶点数量 */
} MatrixGraph;

/**
 * @brief 创建一个新的图
 * 
 * @return MatrixGraph* 返回创建的图指针，失败返回 NULL
 * 
 * @note 图创建时会初始化邻接矩阵，对角线设为0（自身到自身），其余设为INF（无路径）
 */
MatrixGraph* create_graph(void);

/**
 * @brief 向图中添加一个新景点（顶点）
 * 
 * @param graph 图指针
 * @param name 景点名称
 * @return int 返回新添加顶点的编号（从0开始），失败返回 -1
 * 
 * @note 顶点编号从0开始递增，最大支持 MAX_VERTEX 个顶点
 */
int add_vertex(MatrixGraph* graph, const char* name);

/**
 * @brief 向图中添加一条路径（边）及其权重
 * 
 * @param graph 图指针
 * @param from 起点顶点编号
 * @param to 终点顶点编号
 * @param weight 路径权重（必须为正整数）
 * @return int 成功返回0，失败返回 -1
 * 
 * @note 本实现为无向图，添加路径时会同时设置 from->to 和 to->from 的权重
 */
int add_edge(MatrixGraph* graph, int from, int to, int weight);

/**
 * @brief 打印邻接矩阵
 * 
 * @param graph 图指针
 * 
 * @note 矩阵中INF表示两点之间无直接路径，0表示自身到自身
 */
void print_matrix(MatrixGraph* graph);

/**
 * @brief 展示图中所有景点及其编号
 * 
 * @param graph 图指针
 */
void show_all_vertices(MatrixGraph* graph);

/**
 * @brief 释放图占用的内存
 * 
 * @param graph 图指针
 */
void free_graph(MatrixGraph* graph);

#endif
