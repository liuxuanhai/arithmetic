
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include"graph.h"
#include"minheap.h"
using namespace std;
#define NUM_V 9
int **matrix;



//Ëã·¨µ¼ÂÛ3nd  P368
void matrix_init()
{
    int i,j;
    for(i=0;i<=NUM_V;i++)
        for(j=0;j<=NUM_V;j++)
            matrix[i][j]=0;
    matrix[1][2]=4;matrix[1][8]=8;
    matrix[2][1]=4;matrix[2][8]=11;matrix[2][3]=8;
    matrix[3][2]=8;matrix[3][9]=2;matrix[3][6]=4;matrix[3][4]=7;
    matrix[4][3]=7;matrix[4][6]=14;matrix[4][5]=9;
    matrix[5][4]=9;matrix[5][6]=10;
    matrix[6][5]=10;matrix[6][4]=14;matrix[6][3]=4;matrix[6][7]=2;
    matrix[7][6]=2;matrix[7][9]=6;matrix[7][8]=1;
    matrix[8][7]=1;matrix[8][9]=7;matrix[8][1]=8;matrix[8][2]=11;
    matrix[9][8]=7;matrix[9][3]=2;matrix[9][7]=6;
}
int main()
{
    Vertex *u,*v;
    Edge *u_adj;
    int i,j;

    matrix  = (int **) malloc(sizeof(int *) * (NUM_V+1));
    for(j=0;j<=NUM_V;j++){
    matrix[j] = (int *) malloc(sizeof(int) * (NUM_V+1));
    }
    matrix_init();

    Graph *g=new Graph(matrix,9);

    Minheap<Vertex> *mheap=new Minheap<Vertex>(g->V,1,g->num_v);
    mheap->heap[0].key=0;

    while(mheap->heaplen!=0)
    {
        u=mheap->Extract_Min();
        u_adj=u->head;
        while(u_adj!=NULL)
        {
            v=mheap->Find_id(u_adj->end+'a'-1);
            if(v!=NULL&&matrix[u_adj->start][u_adj->end]<v->key)
            {
                v->p=u;
                v->key=matrix[u_adj->start][u_adj->end];
            }
            u_adj=u_adj->next;
        }
        mheap->Bulid_min_heap();
    }
    mheap->heaplen=NUM_V;
    mheap->print();

    return 0;
}

