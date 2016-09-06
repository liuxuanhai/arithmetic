#include<iostream>
#include <stack> 
#include <assert.h>
using namespace std;
template <typename T>
class mystack
{
public:
	//mystack();
	void mypush(const T& value);
	void mypop();
	const T& mymin();
private:
	stack<T> data,min;//data栈用来正常存储每一个进栈的数据，min栈进栈时用来存储当前最小的数据
};
//push函数的实现，data栈正常进数据，min栈进入当前栈中最小的数据
template <typename T>
void mystack<T>::mypush(const T& value)
{
	data.push(value);
	//如果min栈中没有数据或者value小于当前栈的最小数据（top），则value进入min栈
	if(min.size()==0 || value<min.top())
		min.push(value);
	//否则min栈中进入的还是原来栈的最小数据（top）
	else
		min.push(min.top());
}
//pop函数的实现，data，min栈正常弹出数据
template <typename T>
void mystack<T>::mypop()
{
	if(data.size()>0 && min.size()>0)
	{
		data.pop();
		min.pop();
	}
	else
	{
		cout<<"栈为空不能弹出数据！"<<endl;
	}
}
//min函数的实现，获得当前栈中的最小数据
template <typename T>
const T& mystack<T>::mymin()
{
	//判断条件，如果值为假则打印错误信息并终止程序
	assert(data.size()>0 && min.size()>0);
	return min.top();
}
int main()
{
	mystack<int> s;
	s.mypush(3);
	s.mypush(4);
	s.mypush(2);
	s.mypush(1);
	s.mypop();
	s.mypop();
	cout<<"此时栈中最小的元素为:"<<s.mymin()<<endl;
	return 0;
}