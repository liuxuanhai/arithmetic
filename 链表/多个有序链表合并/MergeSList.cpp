#include<iostream>
#include<ctime>
using namespace std;

struct SNode
{
	int key;
	SNode *next;
};

class SList
{
private :
	SNode *head;
public:
	SList();
	void insertSort(int);
	void insertSort(SList &);
	void merge(SList &);
	void print();
};

SList::SList()
{
	head=new SNode;
	head->next=NULL;
}

void SList::insertSort(int tmpKey)
{
	SNode *p=new SNode;
	p->key=tmpKey;
	p->next=NULL;
	SNode *pre=NULL,*cur=head->next;
	while(cur!=NULL)
	{
		if(cur->key>=tmpKey)
		break;
		pre=cur;
		cur=cur->next;
	}
	if(NULL==pre)
	{
		p->next=head->next;
		head->next=p;
	}
	else 
	{
		pre->next=p;
		p->next=cur;
	}
}

void SList::merge(SList &tempSList)
{
	SNode *p,*q,*com;
	com=head;
	p=head->next;
	q=tempSList.head->next;
	while(p!=NULL&&q!=NULL)
	{
		if(p->key<q->key)
		{
			com->next=p;
			p=p->next;
		}
		else
		{
			com->next=q;
			q=q->next;
		}
		com=com->next;
	}
	if(q!=NULL)
		com->next=q;
	if(p!=NULL)
		com->next=p;
}

void SList::print()
{
	SNode *p=head->next;
	while(p!=NULL)
	{
		cout<<p->key<<"  ";
		p=p->next;
	}
	cout<<endl;
}

int mergeSort(SList tArray[],int tLeft,int tRight)
{
	if(tLeft==tRight)
		return tLeft;
	int mid=(tLeft+tRight)>>1;
	int l=mergeSort(tArray,tLeft,mid);
	int r=mergeSort(tArray,mid+1,tRight);
	tArray[l].merge(tArray[r]);
	return l;
}

int main()
{
	int n=10,i,j=0;
	SList *mySList=new SList[n];
	while(j<n)
	{
		i=0;
	 while(i++<n)
	 {
		mySList[j].insertSort(rand()%100);
	 }
	  mySList[j].print();
	  j++;
	}
	mergeSort(mySList,0,9);
	mySList[0].print();
	system("pause");
	return 0;
}