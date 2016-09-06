//9.3-8
/*********************************
问题：找两个有序数组的中位数

算法过程如下：

Step1：分别求出两个数组的中值midA和midB，比较midA和midB的大小

Step2：如果midA=midB，那么这个值就是这（nA+nB）个数中的中位数

Step3：如果midA < midB，A[1..Na] -> A[a+1..Na]，B[1..Nb] -> B[1..b]，递归地对两个新的数组求中位数。

Step4：如果midA > midB，A[1..Na] -> A[1..a]，B[1..Nb] -> B[b+1..Nb]，递归地对两个新的数组求中位数。

Step5：反复Step1-Step4中的递归操作，直到两个数组剩下的元素一共不超过4个，直接对这4个元素求中位数。


*************************************/
#include <iostream>
#include<stdlib.h>
using namespace std;

void Print(int *A, int s, int e)
{
	int i;
	for(i = s; i <= e; i++)
		cout<<A[i]<<' ';
	cout<<endl;
}
//最坏情况线性时间的选择
//已经出现很多次了，不解释
int Partition(int *A, int p, int r)
{
	int x = A[r], i = p-1, j;
	for(j = p; j < r; j++)
	{
		if(A[j] <= x)
		{
			i++;
			swap(A[i], A[j]);
		}
	}
	swap(A[i+1], A[r]);
	return i+1;
}
int Select(int *A, int p, int r, int i);
//对每一组从start到end进行插入排序，并返回中值
//插入排序很简单，不解释
int Insert(int *A, int start, int end, int k)
{
	int i, j;
	for(i = 2; i <= end; i++)
	{
		int t = A[i];
		for(j = i; j >= start; j--)
		{
			if(j == start)
				A[j] = t;
			else if(A[j-1] > t)
				A[j] = A[j-1];
			else
			{
				A[j] = t;
				break;
			}
		}
	}
	return A[start+k-1];
}
//根据文中的算法，找到中值的中值
int Find(int *A, int p, int r)
{
	int i, j = 0;
	int start, end, len = r - p + 1;
	int *B = new int[len/5+1];
	//每5个元素一组，长度为start到end，对每一组进行插入排序，并返回中值
	for(i = 1; i <= len; i++)
	{
		if(i % 5 == 1)
			start = i+p-1;
		if(i % 5 == 0 || i == len)
		{
			j++;
			end = i+p-1;
			//对每一组从start到end进行插入排序，并返回中值,如果是最后一组，组中元素个数可能少于5
			int ret = Insert(A, start, end, (end-start)/2+1);
			//把每一组的中值挑出来形成一个新的数组
			B[j] = ret;
		}
	}
	//对这个数组以递归调用Select()的方式寻找中值
	int ret = Select(B, 1, j, (j+1)/2);
	//delete []B;
	return ret;
}
//以f为主元的划分
int Partition2(int *A, int p, int r, int f)
{
	int i;
	//找到f的位置并让它与A[r]交换
	for(i = p; i < r; i++)
	{
		if(A[i] == f)
		{
			swap(A[i], A[r]);
			break;
		}
	}
	return Partition(A, p, r);
}
//寻找数组A[p..r]中的第i大的元素，i是从1开始计数，不是从p开始
int Select(int *A, int p, int r, int i)
{
	//如果数组中只有一个元素，则直接返回
	if(p == r)
		return A[p];
	//根据文中的算法，找到中值的中值
	int f = Find(A, p, r);
	//以这个中值为主元的划分，返回中值在整个数组A[1..len]的位置
	//因为主元是数组中的某个元素，划分好是这样的，A[p..q-1] <= f < A[q+1..r]
	int q = Partition2(A, p, r, f);
	//转换为中值在在数组A[p..r]中的位置
	int k = q - p + 1;
	//与所寻找的元素相比较
	if(i == k)
		return A[q];
	else if(i < k)
		return Select(A, p, q-1, i);
	else
		//如果主元是数组中的某个元素，后面一半要这样写
		return Select(A, q+1, r, i-k);
		//但是如果主元不是数组中的个某个元素，后面一半要改成Select(A, q, r, i-k+1)
}
int SelectMid(int *A, int start, int end)
{
	return Select(A, start, end, (end-start+1)/2+1);
}
//返回abcd中第二小的数，已经a<b,c<d
int GetRet(int a, int b, int c, int d)
{
	if(a < c)
	{
		if(c < b)
			return min(b, d);
		return c;
	}
	else
	{
		if(a < d)
			return min(b, d);
		return a;
	}
}
//算法过程
int solve(int *A, int *B, int n)
{
	int ret;
	int startA = 1, startB = 1, endA = n, endB = n;
	while(1)
	{
		if(endA == startA)
			return max(A[startA], B[startB]);
		//如果只剩下4个元素，返回4个元素中第2小的元素
		if(endA - startA == 1)
		{
			ret = GetRet(A[startA], A[endA], B[startB], B[endB]);
			break;
		}
		//分别求得A和B中的中值，这里处理的情况是A和B不是排序的
		//如果A和B是已经排序的，只需mid=A[(start+end)/2]就可以求得中值
		int midA = SelectMid(A, startA, endA);
		int midB = SelectMid(B, startB, endB);
//		cout<<midA<<' '<<midB<<endl;
//		Print(A, startA, endA);
//		Print(B, startB, endB);
		//SELECT算法包含划分的过程，所以可以直接截去不需要一半
		//去掉数组A的前一半和数组B的后一半，注意保证去掉后AB的数组元素个数相等
		if(midA == midB)
		{
			ret = midA;
			break;
		}
		//去掉A的前半和数组B的后半，注意截后两个数组的元素相等
		else if(midA < midB)
		{
			startA = startA + (endA - startA + 1) / 2;
			endB = endB - (endB - startB + 1) / 2;
		}
		//去掉B的前半和数组A的后半，注意截后两个数组的元素相等
		else
		{
			endA = endA - (endA-startA + 1) / 2;
			startB = startB + (endB - startB + 1) / 2;
		}
//		Print(A, startA, endA);
//		Print(B, startB, endB);
	}
	return ret;
}
//测试算法过程
int main()
{
	int n, i;
	while(cin>>n)
	{
		int *A = new int[n+1];
		int *B = new int[n+1];
		//生成随机数据
		for(i = 1; i <= n; i++)
		{
			A[i] = rand() % 100;
			B[i] = rand() % 100;
		}
		//打印生成的数据
		Print(A, 1, n);
		Print(B, 1, n);
		//算法过程
		int ret = solve(A, B, n);
		//输出结果
		cout<<ret<<endl;
		delete A;
		delete B;
	}
	return 0;
}
