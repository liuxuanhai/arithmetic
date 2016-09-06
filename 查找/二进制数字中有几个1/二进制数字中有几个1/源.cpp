#include<iostream>
using namespace std;
//因为一个int占4个字节（32位），从最低位开始循环32次来统计1的个数
int find(int n)
{
	int count=0;
	unsigned int temp=1;
	while(temp)
	{
		if(temp & n)
			count++;
		temp=temp<<1;//temp左移一位，二进制变成10，判断第二位是否为1
	}
	return count;
}
//一个数减一再和本身相 与运算，相当于将这个数二进制的最右边的1变为0，有多少个1就循环几次
int find2(int n)
{
	int count=0;
	while(n)
	{
		count++;
		n=(n-1) & n;//最右边的1变为0，1的个数count++
	}
	return count;
}
int main()
{
	cout<<find(2)<<endl;
	cout<<find(-2)<<endl;//负数在计算机中是以补码的形式表示，故-2表示为：2的原码取反+1且最高位为1
	cout<<find2(2)<<endl;
	cout<<find2(-2)<<endl;
	return 0;
}