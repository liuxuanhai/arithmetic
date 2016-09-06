#include<iostream>
#include<stack>
using namespace std;
template<typename T> class squeue
{
public :
	squeue(){
	}
	~squeue(){}
	void append(const T& node);
	T deletedata();
private:
	stack<T> stack1;
	stack<T> stack2;
};
//实现进队列
template<typename T>
void squeue<T>::append(const T& node)
{
	stack1.push(node);
}
//实现出队列
template<typename T>
T squeue<T>::deletedata()
{
	if(stack2.size()<=0)//首先判断s2是否含有数据
	{
		while (stack1.size()>0)
		{
			T &temp=stack1.top();
			stack1.pop();
			stack2.push(temp);
		}

	}
	if(stack2.size()==0)
		throw exception("队列已满！");
	T &t=stack2.top();
	stack2.pop();
	return t;
}
int main()
{
	squeue<int> s;
	s.append(1);
	s.append(2);
	s.append(3);
	s.append(4);
	cout<<s.deletedata()<<endl;
	cout<<s.deletedata()<<endl;
	cout<<s.deletedata()<<endl;
	cout<<s.deletedata()<<endl;
	return 0;
}