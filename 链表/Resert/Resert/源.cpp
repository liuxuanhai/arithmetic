#include<iostream>
#include<stack>
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
//使用栈来实现从尾到头打印链表
void usestack(listnode *head)
{
	if(head!=NULL)
	{
		stack<int> s=stack<int>();
		listnode *temp=head->next;
		while(temp!=NULL)//循环进栈
		{
			s.push(temp->data);
			temp=temp->next;
		}
		while(s.size()!=0)//循环出栈
		{
			cout<<"  "<<s.top();
			s.pop();
		}
	}
}
//反转链表来实现逆向输出
listnode *resert(listnode *head)
{
	listnode *now=head->next;
	listnode *pre=NULL;
	listnode *newhead=NULL;
	while(now!=NULL)
	{
		listnode *next=now->next;//记录当前结点的下个结点，以便于反转指针
		if(next==NULL)//如果当前结点的指针的下个结点为空，记录当前结点后返回
			newhead=now;
		now->next=pre;//反转指针
		//指针后移
		pre=now;
		now=next;
	}
	listnode *hhead=(listnode *)malloc(sizeof(listnode));//由于第一个数为空，所以这添加一个空头
	hhead->next=newhead;
	return hhead;
}
int main()
{
	listnode *head=init();
	print(head);
	cout<<endl;
	usestack(head);
	cout<<endl;
	head=resert(head);
	print(head);
}