#include<iostream>
#include"RedBlackNode.h"
using namespace std;

class RedBlackTree
{
private:
	RedBlackNode *Root;
public:
	RedBlackTree();
	RedBlackNode *GetRoot();
	RedBlackNode *FindRB(int );
	void UpdataRBNode(int,int);
	void InsertRBNode(int);
	void InsertFixUp(RedBlackNode *);
	void LeftRotate(RedBlackNode *);
	void RightRotate(RedBlackNode *);
	void DeleteFixUp(RedBlackNode *);
	bool DeleteRBNode(int);
	void DeleteNoOrOneChildNode(RedBlackNode *,RedBlackNode *);
	void PreOrderPrint(RedBlackNode *);
	void InOrderPrint(RedBlackNode *);
	void SufOrderPrint(RedBlackNode *);
	void RotatePrint(RedBlackNode *,int);
};

RedBlackTree::RedBlackTree()
{
	Root=NULL;
}

/**********************************************************
*��������
*����ֵ����
*���ܣ����غ�������ڵ�
************************************************************/
RedBlackNode *RedBlackTree::GetRoot()
{
	return this->Root;
}

/**********************************************************
*������������ֵ
*����ֵ����
*���ܣ������½��
************************************************************/
void RedBlackTree::InsertRBNode(int tempKey)
{
	RedBlackNode *pre=NULL,*cur=this->Root;
	while(cur!=NULL)
	{
		pre=cur;
		if(cur->key>tempKey)//tempKey�嵽������
			cur=cur->leftChild;
		else cur=cur->rightChild;//�嵽������
	}
	RedBlackNode *tempNode=new RedBlackNode(tempKey);
	tempNode->parent=pre;
	if(pre==NULL)//�������Ϊ���ڵ�
	{
		this->Root=tempNode;
	}
	else if(pre->key>tempNode->key)
		pre->leftChild=tempNode;
	else pre->rightChild=tempNode;
	
	InsertFixUp(tempNode);//���ֺ��������
}

/**********************************************************
*������������ֵ
*����ֵ�����ҵ��򷵻����ڽڵ㣬���򷵻�NULL
*���ܣ������½��
************************************************************/
RedBlackNode *RedBlackTree::FindRB(int tempKey)
{
	RedBlackNode *cur=this->Root;
	while(cur!=NULL)
	{
		if(cur->key==tempKey)
			break;
		else if(cur->key>tempKey)
			cur=cur->leftChild;
		else cur=cur->rightChild;
	}
	return cur;
}

/**********************************************************
*���������޸���ֵoldKey,�޸ĺ����ֵnewKey
*����ֵ����
*���ܣ����½ڵ�Ԫ��
************************************************************/
void RedBlackTree::UpdataRBNode(int oldKey,int newKey)
{
	DeleteRBNode(oldKey);
	InsertRBNode(newKey);
}

/**********************************************************
*��������ǰ�ڵ�
*����ֵ����
*���ܣ�����
************************************************************/
void RedBlackTree::LeftRotate(RedBlackNode *tempNode)
{
	RedBlackNode *rChildNode=tempNode->rightChild;
	if(rChildNode->leftChild!=NULL)//����������������Ϊ��
		rChildNode->leftChild->parent=tempNode;
	rChildNode->parent=tempNode->parent;
	if(NULL==tempNode->parent)//��ǰ�ڵ�Ϊ���ڵ�
		this->Root=rChildNode;
	else if(tempNode==tempNode->parent->leftChild)
		tempNode->parent->leftChild=rChildNode;
	else tempNode->parent->rightChild=rChildNode;
	tempNode->parent=rChildNode;
	tempNode->rightChild=rChildNode->leftChild;
	rChildNode->leftChild=tempNode;
}

/**********************************************************
*��������ǰ�ڵ�
*����ֵ����
*���ܣ�����
************************************************************/
void RedBlackTree::RightRotate(RedBlackNode *tempNode)
{
	RedBlackNode *lChildNode=tempNode->leftChild;
	if(lChildNode->rightChild!=NULL)//����������������Ϊ��
		lChildNode->rightChild->parent=tempNode;
	lChildNode->parent=tempNode->parent;
	if(NULL==tempNode->parent)//��ǰ�ڵ�Ϊ���ڵ�
		this->Root=lChildNode;
	else if(tempNode==tempNode->parent->leftChild)
		tempNode->parent->leftChild=lChildNode;
	else tempNode->parent->rightChild=lChildNode;
	tempNode->parent=lChildNode;
	tempNode->leftChild=lChildNode->rightChild;
	lChildNode->rightChild=tempNode;
}

/**********************************************************
*��������ǰ����ڵ�
*����ֵ����
*���ܣ��ڲ���ڵ����Ե������ֺ��������
************************************************************/
void RedBlackTree::InsertFixUp(RedBlackNode *tempNode)
{
	RedBlackNode *parTempNode=tempNode->parent,*ancleTempNode;
	while(parTempNode!=NULL&&RED==parTempNode->color)//���ڵ㲻Ϊ����Ϊ��ɫ
	{
		if(parTempNode->parent!=NULL)
		{
			if(parTempNode->parent->leftChild==parTempNode)
			{
				ancleTempNode=parTempNode->parent->rightChild;
				if(ancleTempNode!=NULL&&RED==ancleTempNode->color)//����ڵ�Ϊ��ɫ
				{
					parTempNode->color=BLACK;
					ancleTempNode->color=BLACK;
					parTempNode->parent->color=RED;
					tempNode=parTempNode->parent;//ָ��үү�ڵ�
					parTempNode=tempNode->parent;
				}
				else 
				{
					if(tempNode==parTempNode->rightChild)
					{
						LeftRotate(parTempNode);
						tempNode=tempNode->leftChild;
						parTempNode=tempNode->parent;
					}
					parTempNode->color=BLACK;
					parTempNode->parent->color=RED;
					RightRotate(parTempNode->parent);
					break;
				}
			}
			else 
			{
				ancleTempNode=parTempNode->parent->leftChild;
				if(ancleTempNode!=NULL&&RED==ancleTempNode->color)//����ڵ�Ϊ��ɫ
				{
					parTempNode->color=BLACK;
					ancleTempNode->color=BLACK;
					parTempNode->parent->color=RED;
					tempNode=parTempNode->parent;//ָ��үү�ڵ�
					parTempNode=tempNode->parent;
				}
				else{
					if(tempNode==parTempNode->leftChild)
					{
						RightRotate(parTempNode);
						tempNode=tempNode->rightChild;
						parTempNode=tempNode->parent;
					}
					parTempNode->color=BLACK;
					parTempNode->parent->color=RED;
					LeftRotate(parTempNode->parent);
					break;
				}
			}
		}
		else break;
	}
	this->Root->color=BLACK;
}

/**********************************************************
*������pre��ɾ���ڵ�ĸ��ڵ㣬cur��ɾ���ڵ�
*����ֵ����
*���ܣ�ɾ�����Һ�����Ϊ�յ����
************************************************************/
void RedBlackTree::DeleteNoOrOneChildNode(RedBlackNode *pre,RedBlackNode *cur)
{
	if(NULL==cur->leftChild&&NULL==cur->rightChild)//���Һ���Ϊ��
	{
		if(NULL==pre)
			Root=NULL;
		else if(pre->leftChild==cur)
			pre->leftChild=NULL;
		else pre->rightChild=NULL;
		delete cur;
	}
	else if(cur->rightChild!=NULL)//����������Ϊ��
	{
		if(NULL==pre)
		{
			Root=cur->rightChild;
			Root->parent=NULL;
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
			Root=cur->leftChild;
			Root->parent=NULL;
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
*���������ϵ�ƽ�����
*����ֵ����
*���ܣ�ɾ��Ԫ�غ��ƽ��
************************************************************/
void RedBlackTree::DeleteFixUp(RedBlackNode *tempNode)
{
	if(RED==tempNode->color)
		InsertFixUp(tempNode);
}

/**********************************************************
*��������ɾ���ڵ�Ԫ��ֵ
*����ֵ����
*���ܣ�ɾ��ĳԪ��ֵ
************************************************************/
bool RedBlackTree::DeleteRBNode(int tempKey)
{
	RedBlackNode *pre=NULL,*cur=Root;
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
	RedBlackNode *tempChild;
	bool tempColor;
	if(NULL==cur->leftChild||NULL==cur->rightChild)
	{
		if(NULL==cur->leftChild)//�Һ��Ӵ���
			tempChild=cur->rightChild;
		else tempChild=cur->leftChild;
		tempColor=cur->color;
		DeleteNoOrOneChildNode(pre,cur);
		if(tempChild!=NULL&&BLACK==tempColor)
			DeleteFixUp(tempChild);
	}
	else //������������Ϊ��
	{
		RedBlackNode *rPre=cur,*rCur=cur->rightChild;//�ҵ���������СԪ��
		while(rCur->leftChild!=NULL)
		{
			rPre=rCur;
			rCur=rCur->leftChild;
		}
		cur->key=rCur->key;
		tempChild=rCur->rightChild;//�϶�������
		tempColor=rCur->color;
		DeleteNoOrOneChildNode(rPre,rCur);
		if(tempChild!=NULL&&BLACK==tempColor)
			DeleteFixUp(tempChild);
	}
	
}

/**********************************************************
*��������ǰ�������ڵ�
*����ֵ����
*���ܣ�ǰ����������
************************************************************/
void RedBlackTree::PreOrderPrint(RedBlackNode *tempRoot)
{
	if(NULL==tempRoot)
		return ;
	cout<<"("<<tempRoot->key<<",";
	if(tempRoot->color)
		cout<<"�죩  ";
	else cout<<"��)  ";
	PreOrderPrint(tempRoot->leftChild);
	PreOrderPrint(tempRoot->rightChild);
}

/**********************************************************
*��������ǰ�������ڵ�
*����ֵ����
*���ܣ�������������
************************************************************/
void RedBlackTree::InOrderPrint(RedBlackNode *tempRoot)
{
	if(NULL==tempRoot)
		return ;
	InOrderPrint(tempRoot->leftChild);
	cout<<"("<<tempRoot->key<<",";
	if(tempRoot->color)
		cout<<"�죩  ";
	else cout<<"��)  ";
	InOrderPrint(tempRoot->rightChild);
}

/**********************************************************
*��������ǰ�������ڵ�
*����ֵ����
*���ܣ�������������
************************************************************/
void RedBlackTree::SufOrderPrint(RedBlackNode *tempRoot)
{
	if(NULL==tempRoot)
		return ;
	SufOrderPrint(tempRoot->leftChild);
	SufOrderPrint(tempRoot->rightChild);
	cout<<"("<<tempRoot->key<<",";
	if(tempRoot->color)
		cout<<"�죩  ";
	else cout<<"��)  ";
}

/**********************************************************
*��������ǰ�������ڵ㣬��������
*����ֵ����
*���ܣ���ת��ӡ���������
************************************************************/
void RedBlackTree::RotatePrint(RedBlackNode *tempRoot,int tempColumn)
{
	if(NULL==tempRoot)
		return ;
	RotatePrint(tempRoot->leftChild,tempColumn+1);
	for(int i=0;i<tempColumn;i++)
		cout<<"    ";
	cout<<"("<<tempRoot->key<<",";
	if(tempRoot->color)
		cout<<"�죩";
	else cout<<"��)";
	cout<<endl;
	RotatePrint(tempRoot->rightChild,tempColumn+1);
}

int main()
{
	int val;
	while(true)
	{
		RedBlackTree myRedBlackTree;
		while(cin>>val)
		{
			if(val==0)break;
			myRedBlackTree.InsertRBNode(val);
		}
		cout<<endl<<"*****************************"<<endl;
		cout<<endl<<"=============ǰ��============="<<endl;
		myRedBlackTree.PreOrderPrint(myRedBlackTree.GetRoot());
		cout<<endl<<"=============����============="<<endl;
		myRedBlackTree.InOrderPrint(myRedBlackTree.GetRoot());
		cout<<endl<<"==============����============="<<endl;
		myRedBlackTree.SufOrderPrint(myRedBlackTree.GetRoot());
		cout<<endl<<"==============�Գ�+˳ʱ����ת============="<<endl;
		myRedBlackTree.RotatePrint(myRedBlackTree.GetRoot(),0);
		cout<<endl<<"============================="<<endl;
		cout<<"*****************************"<<endl;
		while(cin>>val)
		{
			if(!val)break;
			myRedBlackTree.DeleteRBNode(val);
			cout<<endl<<"*****************************"<<endl;
			cout<<endl<<"=============ǰ��============="<<endl;
			myRedBlackTree.PreOrderPrint(myRedBlackTree.GetRoot());
			cout<<endl<<"=============����============="<<endl;
			myRedBlackTree.InOrderPrint(myRedBlackTree.GetRoot());
			cout<<endl<<"==============����============="<<endl;
			myRedBlackTree.SufOrderPrint(myRedBlackTree.GetRoot());
			cout<<endl<<"==============�Գ�+˳ʱ����ת============="<<endl;
			myRedBlackTree.RotatePrint(myRedBlackTree.GetRoot(),0);
			cout<<endl<<"============================="<<endl;
			cout<<"*****************************"<<endl;
		}
	}
	system("pause");
	return 0;
}