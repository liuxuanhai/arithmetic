#include<iostream>
#include<ctime>
using namespace std;

const int MAXN_LEVEL=10;

struct SNode
{
	int key;
	SNode *forword[MAXN_LEVEL];
};

struct SkipList
{
	int nowLevel; 
	SNode *head;
};



/************************************************
*������myListΪָ������ͷ����ָ��
*����:��ʼ������
*************************************************/
void InitSkipList(SkipList *& myList)
{
	 myList=new SkipList;
	 myList->nowLevel=0;
	 myList->head=new SNode;
	 for(int i=0;i<MAXN_LEVEL;i++)
		 myList->head->forword[i]=NULL;
}

/************************************************
*������myListΪָ������ͷ����ָ�룬xΪ������Ԫ�أ�countRetΪ���Ҵ���
*����:�������в���Ԫ��x
*************************************************/
bool InsertSkipList(SkipList *myList,int val)
{
	if(NULL==myList)
		return false;
	int k=myList->nowLevel;
	SNode *q,*p=myList->head;
	SNode *upDateNode[MAXN_LEVEL];
	while(k>=0)
	{
		q=p->forword[k];
		while(NULL!=q&&q->key<val)
		{
			p=q;
			q=p->forword[k];
		}
		if(NULL!=q&&q->key==val)
		     return false;
		upDateNode[k]=p;
		--k;
	}
	k=rand()%(MAXN_LEVEL-1);
	if(k>myList->nowLevel)
	{
		k=++myList->nowLevel;
		upDateNode[k]=myList->head;
	}
	p=new SNode;
	p->key=val;
	for(int i=0;i<=k;i++)
	{
		q=upDateNode[i];//qָ��ǰ��С��x��
		p->forword[i]=q->forword[i];
		q->forword[i]=p;
	}
	//for(int i=k+1;i<=myList->nowLevel;i++)
	 for(int i=k+1;i<MAXN_LEVEL;i++)
	        p->forword[i]=NULL;
	return true;
}

/************************************************
*������myListΪָ������ͷ����ָ�룬xΪ������Ԫ�أ�countRetΪ���Ҵ���
*����:�����������Ƿ����Ԫ��x
*************************************************/
SNode* FindSkipList(SkipList * myList,int val,int &countRet)
{
	if(NULL==myList)
		return NULL;

	int k=myList->nowLevel;
	SNode *q,*p=myList->head;
	while(k>=0)
	{
		q=p->forword[k];
		++countRet;
		while(NULL!=q&&q->key<val)
		{
			++countRet;
			p=q;
			q=p->forword[k];
		}
		if(NULL!=q&&q->key==val)
		    return q;
		--k;
	}
	return NULL;
}

/************************************************
*������myListΪָ������ͷ����ָ�룬xΪ��ɾ��Ԫ��
*����:ɾ��������Ԫ��x
*************************************************/
bool DeleteSkipList(SkipList * myList,int val)
{
	int tmpCountRet=0;
	SNode *ret=FindSkipList(myList,val,tmpCountRet);
	if(NULL==ret)
		return false;

	int k=myList->nowLevel;
	SNode *q,*p=myList->head;
	SNode *upDateNode[MAXN_LEVEL];

	 for(int i=0;i<MAXN_LEVEL;i++)
		upDateNode[i]=NULL;
	
	while(k>=0)
	{
		q=p->forword[k];
		while(NULL!=q&&q->key<val)
		{
			p=q;
			q=p->forword[k];
		}
		if(NULL!=q&&q->key==val)
			 upDateNode[k]=p;
		--k;
	}

	for(int i=0;i<=myList->nowLevel;i++)
	{
		q=upDateNode[i];//qָ��ǰ��С��x
		if(NULL!=q&&q->forword[i]==ret)
			q->forword[i]=ret->forword[i];
	}
	delete ret;
	return true;
}



int main()
{
	int val;
	SkipList *  myList;
	InitSkipList(myList);

	while(cin>>val)
	{
		if(!InsertSkipList(myList,val))
			cout<<val<<"����ʧ��!"<<endl;
		else cout<<val<<"����ɹ�!"<<endl;
		/*
		int countRet=0;
		if(NULL!=FindSkipList(myList,val,countRet))
			cout<<val<<"���ҳɹ�!"<<endl;
		else cout<<val<<"����ʧ��!"<<endl;
		cout<<"��������"<<countRet<<"��"<<endl;
		*/
		/*
		DeleteSkipList(myList,val);
		countRet=0;
		if(NULL!=FindSkipList(myList,val,countRet))
			cout<<val<<"���ҳɹ�!"<<endl;
		else cout<<val<<"����ʧ��!"<<endl;
		cout<<"��������"<<countRet<<"��"<<endl;
		*/

	}
	system("Pause");
}

