#include<iostream>
using namespace std;
bool find(int *data,int rows,int columns,int key)//int *data将二维数组转化为一维数组，指向二维数组第一个数的地址
{
	bool result=false;
	if(data!=NULL&&rows>0&&columns>0)//判断参数是否合法
	{
		int row=0,column=columns-1;//从最右边开始比较
		while(row<rows&&column>=0)
		{
			if(data[row*columns+column]==key)//找到
			{
				result=true;
				break;
			}
			else if(data[row*columns+column]>key)//要查找的值小于最右边的数，除去最右边的列
			{
				column--;
			}
			else//要查找的值大于最右边的数，除去最上边的一行
				row++;
		}
	}
	return result;
}
int main()
{
	int a[4][4]={1,2,8,9,2,4,8,12,4,7,10,13,6,8,11,15};
	//int (*p)[4]=a;
	cout<<find(*a,4,4,7)<<endl;//a[4][4]是一个二维数组，而a代表指向第一个分数组的指针，基类字节为4（int所占字节数）*4（分数组中元素的个数）=16个字节，因此不能赋值给int *（4个字节），而*a,a[0],&a[0][0]都代表二维数组第一个数的地址（4个字节）
	return 0;
}