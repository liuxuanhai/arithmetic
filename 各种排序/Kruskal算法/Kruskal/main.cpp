#include <iostream>
#include <algorithm>
#include "UnionFindSet.h"
using namespace std;

#define N 14
#define M 9
//边
struct Edge
{
	int start;//起点
	int end;//终点
	int len;//长度
};
//用于排序
bool cmp(Edge a, Edge b)
{
	return a.len < b.len;
}
Edge e[N+1];
//Kruskal算法
void Mst_Kruskal()
{
    int i;
	//使用不相交集合数据结构为每个顶点创建一个集合
	UFS ufs(M);
	//根据可权值的非递减排序
	sort(e+1, e+N+1, cmp);
	//检查每条边
	for(i = 1; i <= N; i++)
	{
		int u = e[i].start, v = e[i].end, l = e[i].len;
		//端点u,v是否属于同一棵树，如果形成一个回路，则放弃
		//若不属于同一棵树
		if(ufs.Find_Set(u) != ufs.Find_Set(v))
		{
			//把边加入到集合中
			cout<<u<<' '<<v<<' '<<l<<endl;
			//对两棵树的顶点进行合并
			ufs.Union(u, v);
		}
	}
}
/*
1 2 4
1 8 8
2 3 8
2 8 11
3 4 7
3 9 2
3 6 4
4 5 9
4 6 14
5 6 10
6 7 2
7 9 6
7 8 1
8 9 7
*/
int main()
{
	int i;
	for(i = 1; i <= N; i++)
		cin>>e[i].start>>e[i].end>>e[i].len;
	cout<<"MST:"<<endl;
	Mst_Kruskal();
	return 0;
}
