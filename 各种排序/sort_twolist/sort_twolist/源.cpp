#include<iostream>
using namespace std;
typedef struct list
{
	int data;
	list *next;
};
list *init()
{
	list *head=new list();
	list *last=head;
	last->next=NULL;
	cout<<"请输入（按-1结束）："<<endl;
	int x;
	cin>>x;
	while(x!=-1)
	{
		list *temp=new list();
		temp->data=x;
		temp->next=NULL;
		last->next=temp;
		last=last->next;
		cout<<"请输入（按-1结束）："<<endl;
		cin>>x;
	}
	return head;
}
void print(list *head)
{
	list *p=head->next;
	while(p!=NULL)
	{
		cout<<p->data<<" ";
		p=p->next;
	}
	cout<<endl;
}
list *unio(list *p,list *q){
	list *head=new list();
	list *last=head;
	head->next=NULL;
	p=p->next;
	q=q->next;
	while(p!=NULL&&q!=NULL)
	{
		if(p->data<q->data)
		{
			last->next=p;
			p=p->next;
			last=last->next;
		}
		else
		{
			last->next=q;
			q=q->next;
			last=last->next;
		}
	}
	if(p==NULL)
	{
		last->next=q;
	}
	else if(q==NULL)
	{
		last->next=p;
	}
	return head;
}
int main()
{
	list *head=init();
	print(head);
	list *head2=init();
	print(head2);
	list *newhead=unio(head,head2);
	print(newhead);
	return 0;
}