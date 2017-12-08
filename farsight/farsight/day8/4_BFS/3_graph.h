#ifndef _GRAPH_H_
#define _GRAPH_H_

//图：邻接矩阵表示法

#include <stdio.h>
#include <stdlib.h>

#define N 9

typedef struct {
	int data[N]; 		//用来存放数据
	int matrix[N][N]; 	//用来存放邻接点之间的关系
}graph_t;

//创建N个没有关系的节点
graph_t *graph_create();

//等待用户输入图的关系(无向图)
int graph_input(graph_t *g);

#endif


