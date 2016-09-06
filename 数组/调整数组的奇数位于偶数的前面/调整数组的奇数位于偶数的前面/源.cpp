#include<iostream>
using namespace std;
//将奇数放到偶数前面的实现
void tiaozheng(int *data,unsigned int length)
{
	if(data==NULL||length<=0)
		throw exception("参数错误！");
	int *begin=data;
	int *end=data+length-1;
	//将begin的第一个偶数和end的第一个奇数交换，直到begin>=end,这时所有奇数都在偶数前面
	while(begin<end)
	{
		//begin指向的数为奇数则begin++,是偶数则跳出循环
		while(begin<end && (*begin & 0x1)==1)
			begin++;
		//end指向的数为偶数则end++,是奇数数则跳出循环
		while(begin<end && (*end & 0x1)==0)
			end--;
		//如果begin<end则交换这两个数字
		if(begin<end)
		{
			int temp=*begin;
			*begin=*end;
			*end=temp;
		}
	}
}
//判断是否是奇数的函数,奇数返回true，偶数返回false
bool isjishu(int x)
{
	if(x & 0x1==1)
		return true;
	else if(x & 0x1==0)
		return false;
}
//打印函数
void print(int *data,int length)
{
	int *begin=data;
	int count=0;
	while(count<length)
	{
		cout<<*begin<<"  ";
		begin++;
		count++;
	}
	cout<<endl;
}
//使用通用的模板解决此类问题
void tiaozheng2(int *data,unsigned int length,bool (*func)(int))
	{
	if(data==NULL||length<=0)
		throw exception("参数错误！");
	int *begin=data;
	int *end=data+length-1;
	//将begin的第一个偶数和end的第一个奇数交换，直到begin>=end,这时所有奇数都在偶数前面
	while(begin<end)
	{
		//begin指向的数为奇数则begin++,是偶数则跳出循环
		while(begin<end && func(*begin))
			begin++;
		//end指向的数为偶数则end++,是奇数数则跳出循环
		while(begin<end && !func(*end))
			end--;
		//如果begin<end则交换这两个数字
		if(begin<end)
		{
			int temp=*begin;
			*begin=*end;
			*end=temp;
		}
	}
}
int main()
{
	int data[5]={1,2,3,4,5};
	print(data,5);
	tiaozheng2(data,5,isjishu);
    print(data,5);
	return 0;
}