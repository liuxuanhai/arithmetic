#include<iostream>
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
//先序递归遍历二叉树
void print(treenode *head)
{
	if(head)
	{
		cout<<head->data<<"	";
		print(head->lchild);
		print(head->rchild);
	}
}
//转换二叉树（镜像）
void change(treenode *head)
{
	if(head==NULL)
		return;
	if(head->lchild==NULL && head->rchild==NULL)
		return;
	//交换该结点的左右结点
	treenode *temp=head->lchild;
	head->lchild=head->rchild;
	head->rchild=temp;
	//递归左子树
	if(head->lchild)
		change(head->lchild);
	//递归右子树
	if(head->rchild)
		change(head->rchild);
}
int main()
{
	treenode *head=init();
	print(head);
	cout<<endl;
	change(head);
	print(head);
	cout<<endl;
	return 0;
}