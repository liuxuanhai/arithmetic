
#include<iostream>
#include"minheap.h"
using namespace std;

class Node
{
    public:int key;
    bool operator<(const Node & b)const
	{
		return key < b.key;
	}
};

void create_nodearr(Node *node,int *key,int length)
{
    int i;
    for(i=0;i<length;i++)
        node[i].key=key[i];
}
int main()
{
    Node *p=new Node[7];
    int key[7]={3,6,1,8,5,32,23};
    create_nodearr(p,key,7);
    Minheap<Node> *mheap=new Minheap<Node>(p,0,7);
    mheap->Bulid_min_heap();
    mheap->print();
    p=mheap->Find(23);
    cout<<p->key<<endl;
    return 0;
}

