#include <iostream>
#include"graph.h"
using namespace std;


int main()
{
    //构造一个空的图
    Graph *G = new Graph;
	Edge *E;
    //输入边
    int i;
    int start, end;
    for(i = 1; i <= 14; i++)
    {
        cin>>start>>end;
        E = new Edge(start, end);
        InsertEdge(G, E);
        //无向图，要加两条边
//      E = new Edge(end, start);
//      InsertEdge(G, E);
    }
	//计算强联通分量
	Strongly_Connected_Component(G);
    return 0;
}
