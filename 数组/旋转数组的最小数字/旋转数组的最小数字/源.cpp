#include<iostream>
using namespace std;
int shunxu(int* numbers,int start,int end);
int Min(int *numbers,int length) throw (exception)
{
	if(numbers==NULL||length<=0)
		throw exception("参数错误！");
	int start=0,end=length-1;//start指向前面的有序数组的的下标，end指向后面有序数组的下标
	int mid=start;//将mid初始化为start，如果是数组没有旋转不进入while循环，直接return numbers[0]
	while(true)
	{
		if(start-end==-1)//start与end相差1时候则证明start为最大的数，end为最小的数
		{
			mid=end;
			break;
		}
		mid=(start+end)/2;
		//如果numbers[mid],numbers[start],numbers[end]相等的话，需要顺序遍历
		if(numbers[mid]==numbers[start]&&numbers[mid]==numbers[end])
		{
			return shunxu(numbers,start,end);
		}
		if(numbers[mid]>=numbers[start])//此时表示最小数在mid后面
			start=mid;
		else if(numbers[mid]<=numbers[end])//此时表示最小数在mid前面
			end=mid;
	}
	return numbers[mid];
}
//顺序遍历数组找最小值
int shunxu(int* numbers,int start,int end)
{
	int min=numbers[start];
	for(int i=start+1;i<=end;i++)
	{
		if(min>numbers[i])
			min=numbers[i];
	}
	return min;
}
int main()
{
	int a[20]={1,1,1,0,1};
	cout<<Min(a,5);
	return 0;
}