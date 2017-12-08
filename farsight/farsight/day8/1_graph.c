//图：邻接矩阵表示法

#include <stdio.h>
#include <stdlib.h>

#define N 5

typedef struct {
	int data[N]; 		//用来存放数据
	int matrix[N][N]; 	//用来存放邻接点之间的关系
}graph_t;

//创建N个没有关系的节点
graph_t *graph_create()
{
	int i;
	graph_t *g = (graph_t *)malloc(sizeof(graph_t)); 				//开辟图的空间

	//对顶点任意赋值
	for(i=0; i<N; i++)
	{
		g->data[i] = 2*i+1;
	}

	return g;
}
//等待用户输入图的关系(无向图)
int graph_input(graph_t *g)
{
	int i,j; 				//下标
	printf("(Vi,Vj)\n");

	while(scanf("(V%d,V%d)", &i, &j) == 2)
	{
		getchar(); 					//吃掉一个垃圾字符'\n' 			???
		g->matrix[i][j] = 1;
		g->matrix[j][i] = 1;
	}

	return 0;
}

//输出图的关系（二维数组的遍历）
int graph_output(graph_t *g)
{
	int i,j;
	printf("  V0 V1 V2 V3 V4\n");

	for(i=0; i<N; i++)
	{
		printf("V%d",i);

		for(j=0; j<N; j++)
		{
			printf(" %d ",g->matrix[i][j]);
		}
		putchar(10); 						//‘\n’
	}

	return 0;
}

int main(int argc, const char *argv[])
{

	graph_t *g = graph_create();
	graph_input(g); 			//等待用户输入图的关系
	graph_output(g);
	
	return 0;
}
