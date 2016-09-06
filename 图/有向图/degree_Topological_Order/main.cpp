#include <iostream>
#include <queue>
using namespace std;

#define N 10

//边结点结构
struct Edge
{
	int start;//有向图的起点
	int end;//有向图的终点
	Edge *next;//指向同一个起点的下一条边
	int type;//边的类型
	Edge(int s, int e):start(s),end(e),next(NULL){}
};
//顶点结点结构
struct Vertex
{
	int id;
	Edge *head;//指向以该顶点为起点的下一条边
	int degree;
	Vertex(int i):head(NULL),degree(0),id(i){}
};
//图结构
struct Graph
{
	Vertex *V[N+1];//N个顶点
	Graph()
	{
		int i;
		for(i = 1; i <= N; i++)
			V[i] = new Vertex(i);
	}
	~Graph()
	{
		int i;
		for(i = 1; i <= N; i++)
			delete V[i];
	}
};

queue<int> Q;
int time = 0;

//插入边
void InsertEdge(Graph *G, Edge *E)
{
	//如果没有相同起点的边
	if(G->V[E->start]->head == NULL)
		G->V[E->start]->head =E;
	//如果有，加入到链表中，递增顺序排列，便于查重
	else
	{
		//链表的插入，不解释
		Edge *e1 = G->V[E->start]->head, *e2 = e1;
		while(e1 && e1->end < E->end)
		{
			e2 = e1;
			e1 = e1->next;
		}
		if(e1 && e1->end == E->end)
			return;
		if(e1 == e2)
		{
			E->next = e1;
			G->V[E->start]->head =E;
		}
		else
		{
			e2->next = E;
			E->next = e1;
		}
		//插入边的同时，计下每个顶点的入度
		G->V[E->end]->degree++;
	}
}
//拓扑排序
void Topological(Graph *G)
{
	//队列初始化
	while(!Q.empty())
		Q.pop();
	int i;
	//将所有入度为0的点入队列
	for(i = 1; i <= N; i++)
	{
		if(G->V[i]->degree == 0)
			Q.push(i);
	}
	//队列不为空
	while(!Q.empty())
	{
		//队列首元素
		int t = Q.front();
		Q.pop();
		//输出
		cout<<char(t+'l')<<' ';
		//处理以头结点为起点的所有的边
		Edge *e = G->V[t]->head;
		while(e)
		{
			//将边的终点的入度-1
			G->V[e->end]->degree--;
			//若入度减为0，则入队列
			if(G->V[e->end]->degree == 0)
				Q.push(e->end);
			e = e->next;
		}
	}
	cout<<endl;
}

int main()
{
	//构造一个空的图
	Graph *G = new Graph;
	Edge *E;
	//输入边
	int i;
	char start, end;
	for(i = 1; i <= 14; i++)
	{
		cin>>start>>end;
		E = new Edge(start-'p', end-'p');
		InsertEdge(G, E);
		//无向图，要加两条边
//		E = new Edge(end, start);
//		InsertEdge(G, E);
	}
	//拓扑排序并输出
	Topological(G);
	return 0;
}
