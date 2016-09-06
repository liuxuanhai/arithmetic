#include<iostream> 
#include<queue>
using namespace std; 
struct treenode 
{ 
 	char data; 
 	treenode *lchild; 
 	treenode *rchild; 
}; 
 //先序创建二叉树 
treenode *init() 
{ 
 	char data; 
 	cout<<"please inpur a number:(#代表NULL)"<<endl; 
 	cin>>data; 
 	if(data=='#') 
 		return NULL; 
 	treenode *head=new treenode; 
 	head->data=data; 
 	head->lchild=init(); 
 	head->rchild=init(); 
 	return head; 
}
//按层次打印二叉树
void print(treenode *head)
{
	queue<treenode *>myque;
	if(head)
	{
		myque.push(head);
	}
	while(!myque.empty())
	{
		//获得队列头的数据并打印
		treenode *temp=myque.front();
		cout<<temp->data<<"	";
		myque.pop();
		if(temp->lchild)
			myque.push(temp->lchild);
		if(temp->rchild)
			myque.push(temp->rchild);
} 	}
int main()
{
	treenode *head=init();
	print(head);
	return 0;
}
