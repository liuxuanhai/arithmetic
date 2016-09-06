/**
Bellman-Ford算法的迭代松弛操作，实际上就是按顶点距离s的层次，逐层生成这棵最短路径树的过程。
在对每条边进行第1遍松弛的时候，生成了从s出发，层次至多为1的那些树枝。
也就是说，找到了与s至多有1条边相联的那些顶点的最短路径；
对每条边进行第2遍松弛的时候，生成了第2层次的树枝，就是说找到了经过2条边相连的那些顶点的最短路径……。
因为最短路径最多只包含|v|-1 条边，所以，只需要循环|v|-1 次。

*/
#include <iostream>
using namespace std;

#define N 5   //点
#define M 10  //边
//边结点结构
struct Edge
{
    int start;//有向图的起点
    int end;//有向图的终点
	int value;
};
//顶点属性
struct Vertex
{
	int d;//与的源点的距离
	int p;//在最短路径树中的父结点
};
Vertex V[N+1];//顶点集合
Edge E[M+1];//边集合
//初始化
void Initialize_Single_Source(int s)
{
	int i;
	for(i = 1; i <= N; i++)
	{
		V[i].d = 0x7fffffff;
		V[i].p = -1;
	}
	V[s].d = 0;
}
//松弛技术
void Relax(int u, int v, int w)
{
	if(V[u].d != 0x7fffffff && V[v].d > V[u].d + w)
	{
		V[v].d = V[u].d + w;
		V[v].p = u;
	}
}
//输出每个顶点的属性
void Print()
{
	int i;
	for(i = 1; i <= N; i++)
		cout<<V[i].d<<' ';
	cout<<endl;
	for(i = 1; i <= N; i++)
		cout<<V[i].p<<' ';
	cout<<endl;
}
//Bellman_Ford算法
bool Bellman_Ford(int s)
{
	int i, j;
	//初始化
	Initialize_Single_Source(s);
	//对图的边进行|V|-1遍操作
	for (i = 1; i < N; i++)
	{
		cout<<"第"<<i<<"轮："<<endl;
		//依次对每条边进行松弛操作
		for(j = 1; j <= M; j++)
		{
			Relax(E[j].start, E[j].end, E[j].value);
		}
		//输出每一轮松弛后的结果
		Print();
	}
	//对负权回路进行检查
	for(j = 1; j <= M; j++)
	{
		if(V[E[j].end].d > V[E[j].start].d + E[j].value)
			return false;
	}
	return true;
}
/*
2 3 5
2 5 8
2 4 -4
3 2 -2
5 3 -3
5 4 9
4 3 7
4 1 2
1 2 6
1 5 7
*/
int main()
{
	int i;
	//输入边
	for(i = 1; i <= M; i++)
		cin>>E[i].start>>E[i].end>>E[i].value;
	//Bellman_Ford算法
	Bellman_Ford(1);
	return 0;
}
