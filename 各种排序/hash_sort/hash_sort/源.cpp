#include<iostream>
using namespace std;
void sortages(int ages[],int length)
{
	if(ages==NULL||length<=0)
		throw exception("参数有误！");
	const int large=99;
	int countage[large+1];//定义保存年龄次数的数组
	//初始化countage
	for(int i=0;i<=large;i++)
		countage[i]=0;
	//为countage赋初值
	for(int i=0;i<length;i++)
	{
		if(ages[i]<0||ages[i]>99)
			throw exception("年龄数组输入有误");
		++countage[ages[i]];//这里ages[i]就相当于hash函数，即它ages数组本身就是countage数组的地址
	}
	int index=0;//ages的下标
	//ages保存经过排序后的年龄
	for(int i=18;i<60;i++)//18-60岁的年龄
	{
		for(int j=0;j<countage[i];j++)//有几个就赋值几次
		{
			ages[index]=i;
			index++;
		}
	}
}
//打印方法
void print(int ages[],int length)
{
	for(int i=0;i<length;i++)
	{
		cout<<" "<<ages[i];
	}
}
int main()
{
	int ages[10]={18,29,34,19,54,24,32,35,55,47};
	sortages(ages,10);
	print(ages,10);
	return 0;
}