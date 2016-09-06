#include<iostream>
using namespace std;
//执行一次顺时针打印的函数，需要四个步骤，但每一步都不是必须的，有可能只需要几步
void subprint(int **data,int rows,int columns,int start)
{
	int endx=columns-1-start;
	int endy=rows-1-start;
	//第一步，从左到右打印,这一步必须执行
	for(int i=start;i<=endx;i++)
	{
		int number=data[start][i];
		cout<<"	"<<number;
	}
	//第二步，从上到下打印，条件是至少包含两行
	for(int i=start+1;i<=endy;i++)
	{
		cout<<"	"<<data[i][endx];
	}
	//第三步，从右向左打印，条件是至少包含两行两列
	for(int i=endx-1;i>=start;--i)
	{
		cout<<"	"<<data[endy][i];
	}
	//第四步，从下到上打印，条件是至少包含两行三列
	for(int i=endy-1;i>=start+1;--i)
	{
		cout<<"	"<<data[i][start];
	}
}
//函数实现
void print(int **data,int rows,int columns)
{
	try
	{
		if(data==NULL||rows<=0||columns<=0)
			throw new exception("参数错误！");
		int start=0;
		//一次顺时针打印的条件是rows>2*start && columns>2*start
		while(rows>2*start && columns>2*start)
		{
			subprint(data,rows,columns,start);
			start++;
		}
	}
	catch(exception e)
	{
		cerr<<e.what()<<endl;
	}
}
int main()
{
	int data[4][4]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	int *p[4];//指针数组，实际是一个数组，数组中每一个元素是一个指针
	//给指针数组赋值
	for(int i=0;i<4;i++)
	{
		p[i]=data[i];
	}
	print(p,4,4);

	////数组指针，实际是指向数组的指针，是一个指针
	//int (*p2)[4];//p2是指向 有4个元素的数组 的指针
	////数组指针的初始化
	//p2=data;//data为0行分数组的地址，将他赋值给p2指针，并且data==&data[0]成立，将&data[0]赋值给p2也是一样的
	//p2=&data[0];

	return 0;
}