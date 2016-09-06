#include<iostream>
using namespace std;
struct listnode
{
	int data;
	listnode *next;
};
//使用尾插法构建链表
listnode *init()
{
	listnode *head=(listnode *)malloc(sizeof(listnode));
	head->next=NULL;
	listnode *last=head;
	int data;
	cout<<"请输入：（按-1结束链表）"<<endl;
	cin>>data;
	while(data!=-1)
	{
		listnode *temp=(listnode *)malloc(sizeof(listnode));
		temp->data=data;
		temp->next=last->next;//last的下一个为NULL
		last->next=temp;
		last=temp;
		cout<<"请输入：（按-1结束链表）"<<endl;
		cin>>data;
	}
	return head;
}
//打印链表
void print(listnode *head)
{
	listnode *temp=head->next;
	while(temp!=NULL)
	{
		cout<<"  "<<temp->data;
		temp=temp->next;
	}
}
//找到链表的第k个结点
listnode *findnumberK(listnode *head,unsigned int k)
{
	//判断参数是否正确
	if(head==NULL||k==0)
	{
		return NULL;
	}
	listnode *first=head;
	listnode *second=first;
	//第二个指针向前走k-1次
	for(int i=0;i<k-1;i++)
	{
		//判断第二个指针的next是否为空
		if(second->next!=NULL)
			second=second->next;
		//没有第k个结点
		else
			return NULL;
	}
	//两个指针循环向前走，第二个指针到达链表结尾，则第一个指针到达第k个结点
	while(second->next)
	{
		first=first->next;
		second=second->next;
	}
	return first;
}
int main()
{
	listnode *head=init();
	print(head);
	cout<<endl;
	cout<<findnumberK(head,3)->data<<endl;
	return 0;
}