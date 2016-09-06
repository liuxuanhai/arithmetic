#include <iostream>
#include <queue>
using namespace std;

#define N 100
enum Ver_colour{
WHITE,
GRAY,
BLACK
};


queue<int> Q;
struct Vertex;
struct Edge
{
    int start;
    int end;
    int value;
    Edge *next;
    Edge(int s, int e, int v):start(s),end(e),value(v),next(NULL){}
};
struct Vertex
{
    int color;
    int d;
    int f;
    int Pie;
    Edge *head;
    Vertex():head(NULL),color(WHITE),d(0x7fffffff),Pie(0){};
};
class Link_Graph
{
public:
    int n;
    int time;
    Vertex *V;
    Link_Graph(int num):n(num)
    {
        V = new Vertex[n+1];
    }
    ~Link_Graph(){delete []V;}
    void AddSingleEdge(int start, int end, int value = 1)
    {
        Edge *NewEdge = new Edge(start, end, value);
        if(V[start].head == NULL || V[start].head->end > end)   //如果顶点的邻接链表为空或者邻接链表中起始相连顶点大于新的邻接顶点
        {
            NewEdge->next = V[start].head;                      //就将新的边插入到邻接链表的头部
            V[start].head = NewEdge;
        }
        else
        {
            Edge *e = V[start].head, *pre = e;
            while(e != NULL && e->end < end)
            {
                pre = e;
                e = e->next;
            }
            if(e && e->end == end)
            {
                delete NewEdge;
                return;
            }
            NewEdge->next = e;
            pre->next = NewEdge;
        }

        /**
        Edge *pre;
        Edge *e = V[start].head;
        if(e==NULL)
        {
            NewEdge->next = V[start].head;
            V[start].head = NewEdge;
            return ;
        }
        while(e!=NULL&&e->end<end)
        {
            pre=e;
            e=e->next;
        }
        if(e && e->end == end)
        {
            delete NewEdge;
            return;
        }
        NewEdge->next = e;
        pre->next = NewEdge;
        */
    }
    void AddDoubleEdge(int a, int b, int value = 1)
    {
        AddSingleEdge(a, b, value);
        AddSingleEdge(b, a, value);
    }
    void DeleteSingleEdge(int start, int end)
    {
        Edge *e = V[start].head, *pre = e;
        while(e && e->end < end)
        {
            pre = e;
            e = e->next;
        }
        if(e == NULL || e->end > end) return;
        if(e == V[start].head)
            V[start].head = e->next;
        else
            pre->next = e->next;
        delete e;
    }
    void DeleteDoubleEdge(int a, int b)
    {
        DeleteSingleEdge(a, b);
        DeleteSingleEdge(b, a);
    }
    //22.2
    //广度优先搜索
    void BFS(int s);
    //广度优先树
    void Print_Path(int s, int v);

    void DFS();
    void DFS_visit(int i);

};

void Link_Graph::BFS(int s)
{
    int i;
    for(i = 1; i <= n; i++)
    {
        V[i].color = WHITE;
        V[i].d = 0x7fffffff;
        V[i].Pie = 0;
    }
    V[s].color = GRAY;
    V[s].d = 0;
    V[s].Pie = 0;
    while(!Q.empty())Q.pop();
    Q.push(s);
    while(!Q.empty())
    {
        int u, v;
        u = Q.front();Q.pop();
        Edge *e = V[u].head;
        while(e)
        {
            v = e->end;
            if(V[v].color == WHITE)
            {
                V[v].color = GRAY;
                V[v].d = V[u].d + 1;
                V[v].Pie = u;
                Q.push(v);
            }
            e = e->next;
        }
        V[u].color = BLACK;
    }
}

void Link_Graph::Print_Path(int s, int v)
{
    BFS(s);
    if(v == s)
        cout<<s<<' ';
    else
    {
        if(V[v].Pie == 0)
            cout<<"no path from "<<s<<" to "<<v<<" exists.";
        else
        {
            Print_Path(s, V[v].Pie);
            cout<<v<<' ';
        }
    }
}


void Link_Graph::DFS()
{
    int i;
    for(i=1;i<=n;i++)
    {
        V[i].colour=WHITE;
        V[i].Pie=0;
    }
    time=0;
    for(i=1;i<=n;i++)
    {
        if(V[i].colour==WHITE)
            DFS_visit(i);
    }
}

void Link_Graph::DFS_visit(int i)
{
    time=time+1;
    V[i].d=time;
    V[i].colour=GRAY;
    Edge *u=V[i].head;
    while(u)
    {
        if(V[u.end])==WHITE)
        {
            V[u.end].Pie=i;
            DFS_visit(u.end);
        }
        u=u->next;
    }
    V[i].colour=BLACK;
    time=time+1;
    V[i].f=time;
}
