#include<iostream>
using namespace std;
struct Treenode
{
	int data;
	Treenode *lchild;
	Treenode *rchild;
};
//重建二叉树：递归构建
Treenode *build(int *first,int *second,int length)
{
	//判断参数是否合法
	if(first==NULL||second==NULL||length<=0)
		return NULL;
	int rootvalue=first[0];
	Treenode *root=new Treenode();
	root->data=rootvalue;
	root->lchild=root->rchild=NULL;
	//只有一个结点时返回
	if(length==1)
	{
		if(first[0]==second[0])
			return root;
		else
			throw exception("input error!");//抛出异常，C#中是throw new exception();
	}
	//多个结点时候递归
	else
	{
		int i=0;
		//在中序遍历中找到root结点
		while(i<length&&second[i]!=rootvalue)
			i++;
		if(i==length)
			throw exception("input error!!");
		//递归左子树，i左边的序列
		if(i>0)
		{
			root->lchild=build(first+1,second,i);
		}
		//递归右子树，i右边的序列
		if(i<length-1)
		{
			root->rchild=build(first+i+1,second+i+1,length-i-1);
		}
	}
	return root;
}
//按照中序打印二叉树
void print(Treenode *root)
{
	if(root)
	{
		print(root->lchild);
	    cout<<root->data<<endl;
		print(root->rchild);
	}
}
int main()
{
	try
	{
		int a[10]={1,2,4,7,3,5,6,8};
		int b[10]={4,7,2,1,5,3,8,6};
		Treenode *root=build(a,b,8);
		print(root);
	}
	catch(const exception &e)
	{
		cerr<<e.what()<<endl;//cerr用来输出异常
	}
}
