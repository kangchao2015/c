//图：邻接矩阵表示法

#include "3_graph.h"
#include "1_link_queue.h"

int sign[N];

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

//广度优先
//标记：入队时标记
int graph_BFS(graph_t *g, data_t v)
{
	int i;
	linkqueue_t *queue = linkqueue_create();
	linkqueue_input(queue, v);
	sign[v] = 1;

	while(!linkqueue_is_empty(queue)) 							//循环执行出队访问，入队标记
	{
		v = linkqueue_output(queue);
		printf("V%d:%d\n",v , g->data[v]);

		for(i=0; i<N; i++)
		{
			if(g->matrix[v][i] == 1 && sign[i] == 0)
			{
				linkqueue_input(queue, i);
				sign[i] = 1;
			}
		}
	}

	return 0;
}


int main(int argc, const char *argv[])
{

	graph_t *g = graph_create();
	graph_input(g); 			//等待用户输入图的关系
	graph_BFS(g,0);
	
	return 0;
}
