#include<iostream>
#include"SplayTreeNode.h"
using namespace std;

class SplayTree
{
private:
	SplayTreeNode *root;
	void LeftRotate(SplayTreeNode *);
	void RightRotate(SplayTreeNode *);
	void Splay(SplayTreeNode *);
	void PreOrderSTPrint(SplayTreeNode *);
	void InOrderSTPrint(SplayTreeNode *);
	void RotateSTPrint(SplayTreeNode *,int);
	void SufOrderSTPrint(SplayTreeNode *);
	void DeleteNoOrOneChildSTNode(SplayTreeNode *,SplayTreeNode *);
public:
	SplayTree();
	void InsertSplayTree(int);
	bool DeleteSplayTree(int);
	bool UpdataSplayTree(int,int);
	SplayTreeNode *FindSplayTree(int);
	void PreOrderSTPrint();
	void InOrderSTPrint();
	void RotateSTPrint();
	void SufOrderSTPrint();
};

SplayTree::SplayTree()
{
	this->root=NULL;
} 

/**************************************************************
*�������������Ľڵ�
*����ֵ����
*���ܣ�����
***************************************************************/
void SplayTree::LeftRotate(SplayTreeNode *tempSTNode)
{
	SplayTreeNode *rChild=tempSTNode->rightChild;
	if(NULL!=tempSTNode->parent)//��Ϊ���ڵ�
	{
		if(tempSTNode->parent->leftChild==tempSTNode)
			tempSTNode->parent->leftChild=rChild;
		else 
			tempSTNode->parent->rightChild=rChild;
	}
	rChild->parent=tempSTNode->parent;
	tempSTNode->parent=rChild;
	if(rChild->leftChild!=NULL)
		rChild->leftChild->parent=tempSTNode;
	tempSTNode->rightChild=rChild->leftChild;
	rChild->leftChild=tempSTNode;
	if(NULL==rChild->parent)
		this->root=rChild;
}

/**************************************************************
*�������������Ľڵ�
*����ֵ����
*���ܣ�����
***************************************************************/
void SplayTree::RightRotate(SplayTreeNode *tempSTNode)
{
	SplayTreeNode *lChild=tempSTNode->leftChild;
	if(NULL!=tempSTNode->parent)//��Ϊ���ڵ�
	{
		if(tempSTNode->parent->rightChild==tempSTNode)
			tempSTNode->parent->rightChild=lChild;
		else 
			tempSTNode->parent->leftChild=lChild;
	}
	lChild->parent=tempSTNode->parent;
	tempSTNode->parent=lChild;
	if(lChild->rightChild!=NULL)
		lChild->rightChild->parent=tempSTNode;
	tempSTNode->leftChild=lChild->rightChild;
	lChild->rightChild=tempSTNode;
	if(NULL==lChild->parent)
		this->root=lChild;
}

/**************************************************************
*����������չ�Ľڵ�
*����ֵ����
*���ܣ�����ǰ�ڵ���չ�ĸ��ڵ�
***************************************************************/
void SplayTree::Splay(SplayTreeNode *tempSTNode)
{
	while(NULL!=tempSTNode&&NULL!=tempSTNode->parent)
	{
		if(tempSTNode->parent->leftChild==tempSTNode)//���׽ڵ�����
			RightRotate(tempSTNode->parent);
		else LeftRotate(tempSTNode->parent);
	}
}

/**************************************************************
*������������Ԫ��
*����ֵ����
*���ܣ�����ǰԪ�ز�����չ��
***************************************************************/
void SplayTree::InsertSplayTree(int tempKey)
{
	SplayTreeNode *pre=NULL,*cur=this->root;
	while(cur!=NULL)
	{
		pre=cur;
		if(cur->key>tempKey)//tempKey�嵽������
			cur=cur->leftChild;
		else cur=cur->rightChild;//�嵽������
	}
	SplayTreeNode *tempSTNode=new SplayTreeNode(tempKey);
	tempSTNode->parent=pre;
	if(pre==NULL)//�������Ϊ���ڵ�
	{
		this->root=tempSTNode;
	}
	else if(pre->key>tempSTNode->key)
		pre->leftChild=tempSTNode;
	else pre->rightChild=tempSTNode;
	Splay(tempSTNode);
}

/**************************************************************
*������������Ԫ��
*����ֵ�����ز���Ԫ������չ���е�λ��
*���ܣ����ҵ�ǰԪ���Ƿ�����չ��
***************************************************************/
SplayTreeNode *SplayTree::FindSplayTree(int tempKey)
{
	SplayTreeNode *cur=this->root;
	while(cur!=NULL)
	{
		if(cur->key==tempKey)
			break;
		else if(cur->key>tempKey)
			cur=cur->leftChild;
		else cur=cur->rightChild;
	}
	Splay(cur);
	return cur;
}

/**********************************************************
*������pre��ɾ���ڵ�ĸ��ڵ㣬cur��ɾ���ڵ�
*����ֵ����
*���ܣ�ɾ�����Һ�����Ϊ�յ����
************************************************************/
void SplayTree::DeleteNoOrOneChildSTNode(SplayTreeNode *pre,SplayTreeNode *cur)
{
	if(NULL==cur->leftChild&&NULL==cur->rightChild)//���Һ���Ϊ��
	{
		if(NULL==pre)
			this->root=NULL;
		else if(pre->leftChild==cur)
			pre->leftChild=NULL;
		else pre->rightChild=NULL;
		delete cur;
	}
	else if(cur->rightChild!=NULL)//����������Ϊ��
	{
		if(NULL==pre)
		{
			this->root=cur->rightChild;
			cur->rightChild->parent=NULL;
		}
		else if(pre->leftChild==cur)
		{
			pre->leftChild=cur->rightChild;
			cur->rightChild->parent=pre;
		}
		else 
		{
			pre->rightChild=cur->rightChild;
			cur->rightChild->parent=pre;
		}
		delete cur;
	}
	else if(cur->leftChild!=NULL)//����������Ϊ��
	{
		if(NULL==pre)
		{
			this->root=cur->leftChild;
			cur->leftChild->parent=NULL;
		}
		else if(pre->leftChild==cur)
		{
			pre->leftChild=cur->leftChild;
			cur->leftChild->parent=pre;
		}
		else
		{
			pre->rightChild=cur->leftChild;
			cur->leftChild->parent=pre;
		}
		delete cur;
	}
}


/**********************************************************
*��������ɾ���ڵ�Ԫ��
*����ֵ����
*���ܣ�ɾ��Ԫ��������
************************************************************/
bool SplayTree::DeleteSplayTree(int tempKey)
{
	SplayTreeNode *pre=NULL,*cur=root;
	while(cur!=NULL)//Ѱ�Ҵ�ɾ��Ԫ��
	{
		if(cur->key==tempKey)
			break;
		else
		{
			pre=cur;
			if(cur->key>tempKey)
				cur=cur->leftChild;
			else cur=cur->rightChild;
		}
	}
	if(NULL==cur)return false;
	if(NULL==cur->leftChild||NULL==cur->rightChild)
	{
		DeleteNoOrOneChildSTNode(pre,cur);
		Splay(pre);
	}
	else //������������Ϊ��
	{
		SplayTreeNode *rPre=cur,*rCur=cur->rightChild;//�ҵ���������СԪ��
		while(rCur->leftChild!=NULL)
		{
			rPre=rCur;
			rCur=rCur->leftChild;
		}
		cur->key=rCur->key;
		DeleteNoOrOneChildSTNode(rPre,rCur);
		Splay(rPre);
	}
	return true;
}

/**********************************************************
*���������޸Ľڵ�Ԫ�ء��޸ĺ��Ԫ��
*����ֵ�������޸��Ƿ�ɹ�
*���ܣ��޸ĺ���
************************************************************/
bool SplayTree::UpdataSplayTree(int oldKey,int newKey)
{
	if(DeleteSplayTree(oldKey))
	{
		InsertSplayTree(newKey);
		return true;
	}
	return false;
}

/**********************************************************
*��������ǰ�������ڵ�
*����ֵ����
*���ܣ�ǰ��������������
************************************************************/
void SplayTree::PreOrderSTPrint(SplayTreeNode *tempSTNode)
{
	if(NULL==tempSTNode)
		return ;
	cout<<tempSTNode->key<<"    ";
	PreOrderSTPrint(tempSTNode->leftChild);
	PreOrderSTPrint(tempSTNode->rightChild);
}
void SplayTree::PreOrderSTPrint()
{
	PreOrderSTPrint(this->root);
}

/**********************************************************
*��������ǰ�������ڵ�
*����ֵ����
*���ܣ�����������������
************************************************************/
void SplayTree::InOrderSTPrint(SplayTreeNode *tempSTNode)
{
	if(NULL==tempSTNode)
		return ;
	InOrderSTPrint(tempSTNode->leftChild);
	cout<<tempSTNode->key<<"   ";
	InOrderSTPrint(tempSTNode->rightChild);
}
void SplayTree::InOrderSTPrint()
{
	InOrderSTPrint(this->root);
}

/**********************************************************
*��������ǰ�������ڵ�
*����ֵ����
*���ܣ�������������������
************************************************************/
void SplayTree::SufOrderSTPrint(SplayTreeNode *tempSTNode)
{
	if(NULL==tempSTNode)
		return ;
	SufOrderSTPrint(tempSTNode->leftChild);
	SufOrderSTPrint(tempSTNode->rightChild);
	cout<<tempSTNode->key<<"    ";
}
void SplayTree::SufOrderSTPrint()
{
	SufOrderSTPrint(this->root);
}

/**********************************************************
*��������ǰ�������ڵ㣬��������
*����ֵ����
*���ܣ���ת��ӡ��չ��
************************************************************/
void SplayTree::RotateSTPrint(SplayTreeNode *tempSTNode,int tempColumn)
{
	if(NULL==tempSTNode)
		return ;
	RotateSTPrint(tempSTNode->leftChild,tempColumn+1);
	for(int i=0;i<tempColumn;i++)
		cout<<"    ";
	cout<<"---"<<tempSTNode->key<<endl;
	RotateSTPrint(tempSTNode->rightChild,tempColumn+1);
}
void SplayTree::RotateSTPrint()
{
	RotateSTPrint(this->root,0);
}


void Menu()
{
	int val,choice,newVal;
	SplayTree mySplayTree;
	while(true)
	{
	do
	{
	cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
	cout<<"       1.����"<<endl;
	cout<<"       2.ɾ��"<<endl;
	cout<<"       3.�޸�"<<endl;
	cout<<"       4.����"<<endl;
	cout<<"       5.��ʾ"<<endl;
	cout<<"       6.����"<<endl;
	cout<<"���������ѡ��[ ]\b\b";
	cin>>choice; 
	}while(choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5&&choice!=6);
	if(1==choice)
	{
		cin>>val;
		mySplayTree.InsertSplayTree(val);
	}
	else if(2==choice)
	{
		cin>>val;
		if(mySplayTree.DeleteSplayTree(val))
			cout<<"ɾ���ɹ�!"<<endl;
		else cout<<"ɾ��ʧ��!"<<endl;
	}
	else if(3==choice)
	{
		cin>>val>>newVal;
		if(mySplayTree.UpdataSplayTree(val,newVal))
			cout<<"�޸ĳɹ�!"<<endl;
		else cout<<"�޸�ʧ��!"<<endl;
	}
	else if(4==choice)
	{
		cin>>val;
		if(NULL!=mySplayTree.FindSplayTree(val))
			cout<<"���ҳɹ�!"<<endl;
		else cout<<"����ʧ��!"<<endl;
	}
	else if(5==choice)
	{
		cout<<endl<<"*****************************"<<endl;
	cout<<endl<<"==========ǰ��=============="<<endl;
	mySplayTree.PreOrderSTPrint();
	cout<<endl<<"==========����================"<<endl;
	mySplayTree.InOrderSTPrint();
	cout<<endl<<"==========����==============="<<endl;
	mySplayTree.SufOrderSTPrint();
	cout<<endl<<"==========�Գ�+��ת==============="<<endl;
	mySplayTree.RotateSTPrint();
	cout<<endl<<"*****************************"<<endl;
	}
	else return ;
	}
}


int main()
{
	while(true)
		 Menu();
	system("pause");
	return 0;
}