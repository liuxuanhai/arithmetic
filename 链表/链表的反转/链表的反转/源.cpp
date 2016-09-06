#include<iostream>
using namespace std;
struct listnode
{
	int data;
	listnode *next;
};
//下面所用的链表头结点都是空的
//尾插法创建链表
listnode *init()
{
	listnode *head=(listnode *)malloc(sizeof(listnode));
	head->next=NULL;
	listnode *p=head;
	cout<<"please input a number(按-1结束)"<<endl;
	int data;
	cin>>data;
	while(data!=-1)
	{
		listnode *temp=(listnode *)malloc(sizeof(listnode));
		temp->data=data;
		temp->next=p->next;
		p->next=temp;
		p=temp;
		cout<<"please input a number(按-1结束)"<<endl;
		cin>>data;
	}
	return head;
}
//打印链表
void print(listnode *head)
{
	listnode *p=head->next;
	while(p)
	{
		cout<<p->data<<"	";
		p=p->next;
	}
	cout<<endl;
}
//反转链表（使用三个指针分别指向当前结点，当前结点的前一个结点和当前结点的下一个结点）
listnode *reverselist(listnode *head)
{
	if(head==NULL)
		return NULL;
	listnode *now=head->next;//当前结点
	listnode *newhead=(listnode *)malloc(sizeof(listnode));//新结点的头指针
	newhead->next=NULL;
	//只有一个结点,头结点（空）
	if(now==NULL)
		return head;
	listnode *pre=NULL;//当前结点的前一个结点
	while(now !=NULL)
	{
		listnode *pnext=now->next;		//保存当前结点的下一个结点
		//如果当前结点的下一个结点为空，则构建新的头结点
		if(now->next==NULL)
		{
			newhead->next=now;
		}
		//将当前结点的next指向它的前一个结点
		now->next=pre;
		//pre和now指针都后移
		pre=now;
		now=pnext;
		
	}
	return newhead;
}
//递归返回条件是指针到达最后一个节点，并将它作为头结点返回，然后依次反转p，q的指向
listnode *resertlist2(listnode *p)
{
	listnode* head=NULL;
	if(p==NULL)
		return NULL;
	listnode *q=p->next;
	//只有一个结点时返回
	if(q==NULL)
		return p;
	head=resertlist2(q);
	q->next=p;
	p->next=NULL;
	return head;
}
int main()
{
	listnode *head=init();
	print(head);
	head=reverselist(head);
	print(head);
	listnode *temp=head->next;
	listnode *newhead=new listnode();
	newhead->next=resertlist2(temp);
	print(newhead);
	return 0;
}