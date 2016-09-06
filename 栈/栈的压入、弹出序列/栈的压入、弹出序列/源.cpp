#include<iostream>
#include<stack>
using namespace std;
bool isorder(const int *push,const int * pop,int length)
{
	if(push!=NULL && pop!=NULL && length>0)
	{
		bool result=false;
		const int *newpush=push;
		const int *newpop=pop;
		stack<int> data;
		while(newpop-pop<length)
		{
			//如果栈为空或者栈的最上面不等于要弹出的数，则入栈
			if(data.size()==0||*newpop!=data.top())
			{
				data.push(*newpush);
				newpush++;
				//最后一个数已经进栈
				if(newpush-push>=length)
				{
					//如果栈的最上面不等于要弹出的数，而此时最后一个数已经进栈,证明不是出栈序列
					if(*newpop!=data.top())
						break;
				}
			}
			else{
				//如果要弹出的数字和栈顶元素一致，则栈弹出
				data.pop();
				newpop++;
			}
		}
		//如果栈为空并且弹出序列到达末尾，则证明是出栈序列
		if(newpop-pop==length && data.size()==0)
			result=true;
		return result;
	}
}
int main()
{
	int a[5]={1,2,3,4,5};
	int b[5]={4,5,3,2,1};
	int c[5]={4,3,5,1,2};
	cout<<isorder(a,b,5)<<endl;
	cout<<isorder(a,c,5)<<endl;
	return 0;
}