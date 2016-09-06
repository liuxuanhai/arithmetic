#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

/***************************************
*
*������ϯ���������k��Ԫ��
*
****************************************/
const int MAXN=100000+100;
const int MAXM=MAXN*20;

int tot,n,m;
int da[MAXN],sDa[MAXN];
int leftChild[MAXM],rightChild[MAXM],wei[MAXM],chairTNode[MAXM];

/**********************************
*������������Ԫ������
*���ܣ�����һ�ÿ��߶���
*����ֵ�����ظ��ڵ��±�
***********************************/
int Build(int left,int right)
{
	int id=tot++;
	wei[id]=0;
	if(left<right)
	{
		int mid=(left+right)>>1;
		leftChild[id]=Build(left,mid);
		rightChild[id]=Build(mid+1,right);
	}
	return id;
}

/**********************************
*������ǰһ���߶������ڵ㣬����λ�ã����º��ֵ
*���ܣ�������ʷ�汾����ԭ����ĳ���ڵ�
*����ֵ��������ϯ���ڵ㼴�߶������ڵ��±�
***********************************/
int Update(int root,int pos,int val)
{
	int l=1,r=m,mid,newRoot=tot++,retRoot=newRoot;
	wei[newRoot]=wei[root]+val;
	while(l<r)
	{
		mid=(l+r)>>1;
		if(pos<=mid)
		{
			//ȷ���ڵ㺢�ӽڵ�
			leftChild[newRoot]=tot++;
			rightChild[newRoot]=rightChild[root];
			//ȷ�������½ڵ��Լ���ʷ�汾
			newRoot=leftChild[newRoot];
			root=leftChild[root];
			r=mid;
		}
		else 
		{
			rightChild[newRoot]=tot++;
			leftChild[newRoot]=leftChild[root];
			newRoot=rightChild[newRoot];
			root=rightChild[root];
			l=mid+1;
		}
		wei[newRoot]=wei[root]+val;
	}
	return retRoot;
}

/**********************************
*�����������Ӧ��ϯ���ڵ��±꣬k
*���ܣ���ѯ��kСԪ��
*����ֵ�����ص�kСԪ�ض�Ӧ�±�
***********************************/
int Query(int leftRoot,int rightRoot,int k)
{
	int  l=1,r=m,mid;
	while(l<r)
	{
		mid=(l+r)>>1;
		if(wei[leftChild[leftRoot]]-wei[leftChild[rightRoot]]>=k)//��kСֵ��������
		{
			//ȷ������������
			leftRoot=leftChild[leftRoot];
			rightRoot=leftChild[rightRoot];
			r=mid;
		}
		else 
		{
			k-=wei[leftChild[leftRoot]]-wei[leftChild[rightRoot]];
			leftRoot=rightChild[leftRoot];
			rightRoot=rightChild[rightRoot];
			l=mid+1;
		}
	}
	return l;
}

int main()
{
	int q,i;
	int ql,qr,k;
	while(scanf("%d%d",&n,&q)!=EOF)
	{
		m=0;
		tot=0;
		for(i=1;i<=n;i++)
		{
			scanf("%d",&da[i]);
			sDa[i]=da[i];
		}
		sort(sDa+1,sDa+n+1);
		m=unique(sDa+1,sDa+1+n)-sDa-1;
		chairTNode[n+1]=Build(1,m);
		for(i=n;i>=1;i--)
		{
			int pos=lower_bound(sDa+1,sDa+1+m,da[i])-sDa;
			chairTNode[i]=Update(chairTNode[i+1],pos,1);
		}
		while(q--)
		{
			scanf("%d%d%d",&ql,&qr,&k);
			printf("%d\n",sDa[Query(chairTNode[ql],chairTNode[qr+1],k)]);
		}
	}
	system("pause");
	return 0;
}
