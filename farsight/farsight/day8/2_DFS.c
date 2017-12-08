//深度优先搜索

#include <stdio.h>
#include <stdlib.h>

#define N 9

typedef struct {
	int data[N]; 		//用来存放数据
	int matrix[N][N]; 	//用来存放邻接点之间的关系
}graph_t;

int sign[N]; 			//标志位

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

//找V的邻接点
int find_next(graph_t *g, int v)
{
	int i;

	for(i=0; i<N; i++)
	{
		if(g->matrix[v][i] == 1 && sign[i] == 0)
		{
			return i;
		}
	}
	
	return -1; 						//没有不被标记的邻接点
}

//深度优先搜索
int graph_DFS(graph_t *g, int v)
{
	int i;

	printf("V%d:%d\n",v, g->data[v]); 		//V下标：数值
	sign[v] = 1; 							//标志位置1

	i = find_next(g,v);
	
	while(i >= 0) 		//为真：有邻接点
	{
		graph_DFS(g,i);
		i = find_next(g,v);
	}

	return 0;
}


int main(int argc, const char *argv[])
{

	graph_t *g = graph_create();
	graph_input(g); 			//等待用户输入图的关系
	graph_DFS(g,0);
	
	return 0;
}
