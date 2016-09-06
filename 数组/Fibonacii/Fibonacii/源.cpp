#include<iostream>
using namespace std;
long long Fibonacci_xunhuan(int n)
{
	if(n<0)
		throw exception("参数有误！");
	long long start[2]={0,1};
	if(n<2)
		return start[n];
	long long first=start[0];
	long long second=start[1];
	long long result=0;
	//两个下标之和为第三个数。同时两个下标后移
	for(unsigned int i=2;i<=n;i++)
	{
		result=first+second;
		first=second;
		second=result;
	}
	return result;
}
int main()
{
	cout<<Fibonacci_xunhuan(5);
	return 0;
}