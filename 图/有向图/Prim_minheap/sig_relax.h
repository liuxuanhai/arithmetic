#include<iostream>
#include<limits>
#include"graph.h"

void Initialize_single_source(Graph *g,Vertex *s)
{
    int i;
    for(i=1;i<=g->num_v;i++)
    {
        g->V[i].d=INT_MAX;
        G->v[i].p=NULL;
    }
    s->d=0;
}

void Relax(Vertex *u,Vertex *v,int **weight)
{
    int new_weight;
    if(u->d!=INT_MAX)
    {
        new_weight=u->d+weight[u->id][v->id];
        if(v->d>new_weight)
        {
            v->d=new_weight;
            v->p=u;
        }
    }

}



