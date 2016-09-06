#include <iostream>
#include <limits.h>
using namespace std;

enum colour{
    WHITE,
    GRAY,
    BLACK
};


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
class Vertex
{
public:
	char id;
	int key;
	Edge *head;

	Vertex *p;

	//判断是否在堆中
	bool In_queue;


    bool operator<(const Vertex & b)const
	{
		return key < b.key;
	}

};
//图结构
class Graph
{
public:
	Vertex *V;//N个顶点
	int num_v;
    Graph();
    Graph(int **matrix,int n){
        int i,j;
        num_v=n;
        V=new Vertex[num_v+1];
        for(i=1;i<=num_v;i++)
        {
            V[i].id='a'+i-1;
            V[i].key=INT_MAX;
            V[i].p=NULL;
            V[i].In_queue=1;
            V[i].head=NULL;
        }
        cout<<"go into matrix"<<endl;
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                if(matrix[i][j]!=0) InsertEdge(new Edge(i,j));
    }
private:
	//插入边
	void InsertEdge(Edge *E);



};
Graph::Graph()
{
    char fir_v,con='[';
    int i,start;
    cout<<"first Vertex id is(eg:a or i):";
    cin>>fir_v;
    cout<<"the number of Vertex:";
    cin>>num_v;
    V=new Vertex[num_v+1];
    for(i=1;i<=num_v;i++)
    {
        V[i].id=fir_v+i-1;
        V[i].key=INT_MAX;
        V[i].p=NULL;
        V[i].In_queue=1;
    }
    cout<<"Now input the edge id connected with the first char"<<endl;
    cout<<"if none input ';'"<<endl;
    for(i=0;i<num_v;i++)
    {
        start=i+1;
        cout<<"connected with "<<char(fir_v+i)<<":";
        cin>>con;
        while(con!=';')
        {
            cin>>con;
            InsertEdge(new Edge(start,(con-'a'+1)));
        }
        con='[';
    }
}

//插入边
void Graph::InsertEdge(Edge *E)
{
    	//如果没有相同起点的边
	if(V[E->start].head == NULL)
		V[E->start].head =E;
	//如果有，加入到链表中，递增顺序排列，便于查重
	else
	{
		//链表的插入，不解释
		Edge *e1 = V[E->start].head, *e2 = e1;
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
			V[E->start].head =E;
		}
		else
		{
			e2->next = E;
			E->next = e1;
		}
	}
}


