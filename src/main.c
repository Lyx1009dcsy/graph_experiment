#include "matrix_graph.h"
#include <windows.h>

/**
 * @brief 清空输入缓冲区
 * 
 * 清除 scanf 或 fgets 后留在缓冲区中的多余字符，
 * 防止后续输入操作读取到错误的数据。
 */
void clear_input_buffer(void) {
    while (getchar() != '\n');
}

/**
 * @brief 打印系统主菜单
 * 
 * 显示景区路径规划系统的所有功能选项，供用户选择操作。
 */
void print_menu(void) {
    printf("\n=================== 景区路径规划系统 ===================\n");
    printf("                    基于邻接矩阵实现\n");
    printf("========================================================\n");
    printf("  [1] 创建图\n");
    printf("  [2] 添加景点\n");
    printf("  [3] 添加路径权重\n");
    printf("  [4] 打印邻接矩阵\n");
    printf("  [5] 展示全部景点\n");
    printf("  [6] 退出系统\n");
    printf("========================================================\n");
    printf("请输入您的选择 (1-6): ");
}

/**
 * @brief 主函数
 * 
 * 景区路径规划系统的入口函数，实现控制台菜单交互逻辑。
 * 用户可以通过菜单操作创建图、添加景点、添加路径权重、
 * 打印邻接矩阵、展示全部景点等功能。
 * 
 * @return int 程序退出码，0表示正常退出
 */
int main(void) {
    MatrixGraph* graph = NULL;  /* 图指针，初始化为NULL */
    int choice = 0;             /* 用户选择的菜单选项 */
    
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    printf("欢迎使用景区路径规划系统！\n");
    printf("请先创建图，然后进行其他操作。\n");
    
    /* 主循环，直到用户选择退出 */
    while (choice != 6) {
        print_menu();
        
        /* 读取用户输入，检查输入有效性 */
        if (scanf("%d", &choice) != 1) {
            printf("输入无效，请输入数字！\n");
            clear_input_buffer();  /* 清空缓冲区，防止死循环 */
            continue;
        }
        clear_input_buffer();  /* 清除换行符 */
        
        /* 根据用户选择执行相应操作 */
        switch (choice) {
            case 1: {
                /* 创建图 */
                if (graph != NULL) {
                    printf("图已存在，是否重新创建？(y/n): ");
                    char confirm;
                    scanf("%c", &confirm);
                    clear_input_buffer();
                    if (confirm != 'y' && confirm != 'Y') {
                        printf("操作取消。\n");
                        break;
                    }
                    free_graph(graph);
                }
                graph = create_graph();
                break;
            }
            case 2: {
                /* 添加景点 */
                if (graph == NULL) {
                    printf("请先创建图！\n");
                    break;
                }
                char name[50];
                printf("请输入景点名称: ");
                fgets(name, sizeof(name), stdin);
                /* 移除末尾的换行符 */
                name[strcspn(name, "\n")] = '\0';
                /* 检查名称是否为空 */
                if (strlen(name) == 0) {
                    printf("景点名称不能为空！\n");
                    break;
                }
                add_vertex(graph, name);
                break;
            }
            case 3: {
                /* 添加路径权重 */
                if (graph == NULL) {
                    printf("请先创建图！\n");
                    break;
                }
                if (graph->vertex_count < 2) {
                    printf("请先添加至少2个景点！\n");
                    break;
                }
                /* 显示所有景点供用户选择 */
                show_all_vertices(graph);
                
                int from, to, weight;
                
                /* 读取起点编号 */
                printf("\n请输入起点编号: ");
                if (scanf("%d", &from) != 1) {
                    printf("输入无效，请输入数字！\n");
                    clear_input_buffer();
                    break;
                }
                
                /* 读取终点编号 */
                printf("请输入终点编号: ");
                if (scanf("%d", &to) != 1) {
                    printf("输入无效，请输入数字！\n");
                    clear_input_buffer();
                    break;
                }
                
                /* 读取路径权重 */
                printf("请输入路径权重(正整数): ");
                if (scanf("%d", &weight) != 1) {
                    printf("输入无效，请输入数字！\n");
                    clear_input_buffer();
                    break;
                }
                clear_input_buffer();
                
                /* 添加路径 */
                add_edge(graph, from, to, weight);
                break;
            }
            case 4: {
                /* 打印邻接矩阵 */
                if (graph == NULL) {
                    printf("请先创建图！\n");
                    break;
                }
                print_matrix(graph);
                break;
            }
            case 5: {
                /* 展示全部景点 */
                if (graph == NULL) {
                    printf("请先创建图！\n");
                    break;
                }
                show_all_vertices(graph);
                break;
            }
            case 6: {
                /* 退出系统 */
                printf("感谢使用景区路径规划系统！\n");
                if (graph != NULL) {
                    free_graph(graph);
                }
                break;
            }
            default: {
                /* 无效选择 */
                printf("无效的选择，请输入1-6之间的数字！\n");
                break;
            }
        }
        
        /* 退出前暂停，让用户查看结果 */
        if (choice != 6) {
            printf("\n按任意键继续...");
            getchar();
        }
    }
    
    return 0;
}
