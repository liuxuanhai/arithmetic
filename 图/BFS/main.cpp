#include <iostream>
#include "graph.h"
using namespace std;
/*
1 2
1 5
2 6
6 7
6 3
3 7
3 4
7 8
7 4
4 8
*/
int main()
{
    Link_Graph *G = new Link_Graph(8);
    int i = 0, a, b;
    for(i = 1; i <= 10; i++)
    {
        cin>>a>>b;
        G->AddDoubleEdge(a,b);
    }
    G->BFS(2);
    for(i = 1; i <= 8; i++)
        cout<<G->V[i].d<<' ';
    cout<<endl;
    int s, v;
    while(cin>>s>>v)
    {
        G->Print_Path(s, v);
        cout<<endl;
    }
    return 0;
}


/**
思考：自己的数据结构无法工作而采取别人设计的原因：
1.相邻链表是节点的一个属性，我把它划归到图的属性，建立一个节点指针数组
2.用节点的指针相互连接，导致双重指针，这使得构建相邻链表显得复杂，没有考虑到后续的应用，包括边上的权这样的拓展
即使搭建好这样的数据结构，到时候还要重建数据结构，或者强行将本属于边的属性加入节点，使信息更加冗余。


在引用的数据结构中将图分为边和节点，与节点关联的边由节点的边的头指针管理，且按照顺序排放节点之间的关联
总结：缺乏用对象的观点来看待问题的思路，其实仔细一想书中也的确按照对象来描述的




*/
