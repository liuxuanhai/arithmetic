#include <iostream>
#include <stdlib.h>
#include <math.h>
using namespace std;

struct node
{
	int start;
	int end;
	bool operator<(const node & b)const
	{
		return start < b.start;
	}
	bool operator==(const node & b)const
	{
		return (end >= b .start) && (start <= b.end);
	}
	bool operator>(const node & b)const
	{
		return start > b.start;
	}
	bool operator>=(const node & b)const
	{
		return (start < b.end)&&(start>b.start)&&(end>b.end);
	}
	bool operator<=(const node & b)const
	{
		return (start < b.start)&&(end>b.start)&&(end<b.end);
	}
};

//划分结果：0 -> a小于主元，a+1 -> b-1等于主元，b -> length_A大于主元
struct divid
{
	int a;
	int b;
};

node A[11];
int length_A = 10;

//按划分结果分三行显示
void Print(divid d)
{
	int i = 1;
	if(d.a > 0)
	{
		for(i = 1; i <= d.a; i++)
			cout<<'('<<A[i].start<<','<<A[i].end<<") ";
		cout<<endl;
		i = d.a + 1;
	}
	if(d.b > 0)
	{
		for(; i < d.b; i++)
			cout<<'('<<A[i].start<<','<<A[i].end<<") ";
		cout<<endl;
		i = d.b;
	}
	if(i <= length_A)
	{
		for(; i <= length_A; i++)
			cout<<'('<<A[i].start<<','<<A[i].end<<") ";
		cout<<endl;
	}
	cout<<endl;
}
void my_Print(divid d,int p,int r)
{
	int i = 1;
	if(d.a > 0)
	{
		for(i = p; i <= d.a; i++)
			cout<<'('<<A[i].start<<','<<A[i].end<<") ";
		cout<<endl;
		i = d.a + 1;
	}
	if(d.b > 0)
	{
		for(; i <= r; i++)
			cout<<'('<<A[i].start<<','<<A[i].end<<") ";
		cout<<endl;
		i = d.b;
	}
	if(i <= length_A)
	{
		cout<<"element is one only";
		cout<<endl;
	}
	cout<<endl;
}
//交换
void Exchange(node &a, node &b)
{
	node temp;
	temp = a;
	a = b;
	b = temp;
}
//划分是重点
divid Partition(node *A, int p, int r)
{
	//先取任意一个元素为主元
	node x = A[r];
	int i = p-1, j = r+1, k = p,kk;
	while(k <=r && k < j)
	{
        cout<<"when i="<<i<<"  " <<"j="<<j<<"  "<<"k="<<k<<"  "<<"A[k]=["<<A[k].start<<","<<A[k].end<<"]"<<endl;
        cout<<"before element is "<<x.start<<"---"<<x.end<<endl;
        for(kk=p; kk <= r; kk++)
			cout<<'('<<A[kk].start<<','<<A[kk].end<<") ";
		cout<<endl;

		//如果小于主元，交换到前面
		if(A[k] < x)
		{
			i++;
			Exchange(A[i], A[k]);
			k++;
			cout<<"go into < "<<endl;
		}
	/*	else if(A[k] <= x)
		{
		    x.end=A[k].end;
			i++;
			Exchange(A[i], A[k]);
			k++;

			cout<<"go into <= "<<endl;
		}*/
		//如果大于，交换到后面
		else if(A[k] > x)
		{
			j--;
			Exchange(A[j], A[k]);
			//这里不能k++，因为交换过来的元素也可能大于主元
			cout<<"go into > "<<endl;
		}
/*		else if(A[k] >= x)
		{
		    x.start=A[k].start;
			j--;
			Exchange(A[j], A[k]);
            cout<<"go into >= "<<endl;
		}*/
			//如果相等，不交换，但是要提取公因子
        else{
			x.end = min(x.end,A[k].end);
			x.start =max(A[k].start,x.start);
			k++;
			cout<<"go into == "<<endl;
		}
        cout<<"after element is "<<x.start<<"---"<<x.end<<endl;
        for(kk=p; kk <= r; kk++)
			cout<<'('<<A[kk].start<<','<<A[kk].end<<") ";
		cout<<endl;
	}
	//返回划分结果
	divid ret = {i, j};
	if(ret.a < p)ret.a = -1;
	if(ret.b > r)ret.b = -1;
	cout<<"when p="<<p<<"  " <<"r="<<r<<endl;
    cout<<"main element is "<<x.start<<"---"<<x.end<<endl;
	my_Print(ret,p,r);
	return ret;
}

void QuickSort(node *A, int p, int r)
{
    int i;
	if(p >= r)
		return;
	//把数组划分为三段
	divid q = Partition(A, p, r);
	//如果存在第一段，对第一段排序
	if(q.a > 0)
		QuickSort(A, p, q.a);
	//如果存在第三段，对第三段排序
	if(q.b > 0)
		QuickSort(A, q.b, r);
}

int main()
{
	int i, n;
	//init data by random
	for(i = 1; i <= length_A; i++)
	{
		A[i].start = rand() % 100;
		A[i].end = rand() % 100;
		if(A[i].start > A[i].end)
			swap(A[i].start, A[i].end);
	}
	divid d = {-1, -1};
	for(i = 1; i <= length_A; i++)
	{
	    cout<<'('<<A[i].start<<','<<A[i].end<<") ";
	}
	cout<<endl;
	//Print(d);
	cout<<"***********************"<<endl;
	//sort
	QuickSort(A, 1, length_A);
	for(i=1; i <= length_A; i++)
			cout<<'('<<A[i].start<<','<<A[i].end<<") ";
    cout<<endl;
	return 0;
}
