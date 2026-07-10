#include "matrix_graph.h"
#include <windows.h>

void clear_input_buffer(void) {
    while (getchar() != '\n');
}

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

int main(void) {
    MatrixGraph* graph = NULL;
    int choice = 0;
    
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    printf("欢迎使用景区路径规划系统！\n");
    printf("请先创建图，然后进行其他操作。\n");
    
    while (choice != 6) {
        print_menu();
        
        if (scanf("%d", &choice) != 1) {
            printf("输入无效，请输入数字！\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        
        switch (choice) {
            case 1: {
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
                if (graph == NULL) {
                    printf("请先创建图！\n");
                    break;
                }
                char name[50];
                printf("请输入景点名称: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                if (strlen(name) == 0) {
                    printf("景点名称不能为空！\n");
                    break;
                }
                add_vertex(graph, name);
                break;
            }
            case 3: {
                if (graph == NULL) {
                    printf("请先创建图！\n");
                    break;
                }
                if (graph->vertex_count < 2) {
                    printf("请先添加至少2个景点！\n");
                    break;
                }
                show_all_vertices(graph);
                
                int from, to, weight;
                
                printf("\n请输入起点编号: ");
                if (scanf("%d", &from) != 1) {
                    printf("输入无效，请输入数字！\n");
                    clear_input_buffer();
                    break;
                }
                
                printf("请输入终点编号: ");
                if (scanf("%d", &to) != 1) {
                    printf("输入无效，请输入数字！\n");
                    clear_input_buffer();
                    break;
                }
                
                printf("请输入路径权重(正整数): ");
                if (scanf("%d", &weight) != 1) {
                    printf("输入无效，请输入数字！\n");
                    clear_input_buffer();
                    break;
                }
                clear_input_buffer();
                
                add_edge(graph, from, to, weight);
                break;
            }
            case 4: {
                if (graph == NULL) {
                    printf("请先创建图！\n");
                    break;
                }
                print_matrix(graph);
                break;
            }
            case 5: {
                if (graph == NULL) {
                    printf("请先创建图！\n");
                    break;
                }
                show_all_vertices(graph);
                break;
            }
            case 6: {
                printf("感谢使用景区路径规划系统！\n");
                if (graph != NULL) {
                    free_graph(graph);
                }
                break;
            }
            default: {
                printf("无效的选择，请输入1-6之间的数字！\n");
                break;
            }
        }
        
        if (choice != 6) {
            printf("\n按任意键继续...");
            getchar();
        }
    }
    
    return 0;
}
