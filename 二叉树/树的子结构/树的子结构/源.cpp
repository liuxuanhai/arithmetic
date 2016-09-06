#include<iostream>
using namespace std;

struct treenode
{
	char data;
	treenode *lchild;
	treenode *rchild;
};
bool issame(treenode *head1,treenode *head2);
//先序构建二叉树（递归）
treenode *init()
{
	treenode *head=new treenode;
	char data;
	cout<<"please input a number of node<按#结束>"<<endl;
	cin>>data;
	if(data=='#')
		return NULL;
	else
	{
		head->data=data;
		head->lchild=init();
		head->rchild=init();
	}
	return head;
}
//先序打印二叉树
void preorderprint(treenode *head)
{
	if(head)
	{
		cout<<head->data<<"	";
		preorderprint(head->lchild);
		preorderprint(head->rchild);
	}
}
//判断第二个树是否为第一个树的子结构
bool contains(treenode *head1,treenode *head2)
{
	bool result=false;
	//空树是任何树的子结构
	if(head2==NULL)
		return true;
	if(head1!=NULL)
	{
		//如果两个结点相等，则继续判断他们的子树是否相等
		if(head1->data==head2->data)
			result=issame(head1,head2);
		//如果不是子树，递归判断左子树
		if(!result)
			result=contains(head1->lchild,head2);
		//如果不是子树，递归判断右子树
		if(!result)
			result=contains(head2->rchild,head2);
	}
	return result;
}
//递归判断两个结点的子树是否也相同
bool issame(treenode *head1,treenode *head2)
{
	//如果第二个结点为空，则返回true
	if(head2==NULL)
		return true;
	//第一个节点为空，则返回false
	if(head1==NULL)
		return false;
	//如果两个结点都不为空并且他们不相等，返回false
	if(head1->data!=head2->data)
		return false;
	//两个结点相等则递归判断他们左右子树的结点是否相等
	return issame(head1->lchild,head2->lchild)&&issame(head1->rchild,head2->rchild);
}
int main()
{
	treenode *head1=init();
	preorderprint(head1);
	cout<<endl;
	treenode *head2=init();
	preorderprint(head2);
	cout<<endl;
	cout<<"是否包含："<<contains(head1,head2);
	return 0;
}