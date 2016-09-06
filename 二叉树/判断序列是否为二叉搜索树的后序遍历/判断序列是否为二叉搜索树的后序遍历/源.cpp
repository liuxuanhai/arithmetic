#include<iostream>
using namespace std;
bool isorder(int *data,int length)
{
	//判断边界条件
	if(data==NULL||length<=0)
	{
		return false;
	}
	//保存根节点值
	int root=data[length-1];
	//找到第一个大于根节点的值，往后的值都大于根节点，否则返回false
	int i=0;
	for(;i<length-1;i++)
	{
		if(root<data[i])
			break;
	}
	for(int j=i+1;j<length-1;j++)
	{
		//如果i之后的数字有一个小于根节点，则不满足后序遍历，返回false
		if(data[j]<root)
			return false;
	}
	//如果存在左子树，则递归判断左子树
	bool left=true;
	if(i>0)
	{
		left=isorder(data,i);
	}
	//如果存在右子树，递归判断右子树
	bool right=true;
	if(i<length-1)
	{
		right=isorder(data+i,length-i-1);
	}
	return left&&right;
}
int main()
{
	int data[]={5,7,6,9,11,10,8};
	cout<<"是否是二叉搜索树的后序遍历："<<(isorder(data,7)?"true":"false")<<endl;
	return 0;
}