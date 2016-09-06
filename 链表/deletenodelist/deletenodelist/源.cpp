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
//删除链表中的某一结点
void deletenode(listnode *head,listnode *tobedeleted)
{
	try
	{
		if(!head||!tobedeleted)
			throw  exception("参数有误！");
		//要删除的结点在链表中间
		if(tobedeleted->next!=NULL)
		{
			listnode *temp=tobedeleted->next;//获得要删除结点的下一个结点
			tobedeleted->data=temp->data;//将下一个结点的值赋给当前结点
			tobedeleted->next=temp->next;//将当前结点的next指向下一个结点的next，即删除了下一个结点
			delete temp;//释放内存
			temp=NULL;
		}
		//要删除的结点是尾结点
		else
		{
			//遍历获得要删除结点的前一个结点，将前一个结点的next值赋值为NULL
			listnode *p=head;
			while(p->next!=tobedeleted)
			
			{
				p=p->next;
			}
			p->next=tobedeleted->next;
			delete tobedeleted;
			tobedeleted=NULL;

		}
	}
	catch(exception e)
	{
		cerr<<e.what()<<endl;
	}
}
int main()
{
	listnode *head=init();
	listnode *tobedeleted=head->next->next;
	cout<<"删除前显示：";
	print(head);
	cout<<endl<<"删除后显示：";
	deletenode(head,tobedeleted);
	print(head);
	cout<<endl;
	return 0;
}