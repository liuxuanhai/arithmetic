#include<iostream>
#include<string>
using namespace std;
void replace(char *array,int length)
{
	if(array!=NULL&&length>0)//判断参数是否合法
	{
		int blankcount=0,index=0;//blankcount记录空格数，index记录数组中最后一为'\0'的下标
		while(array[index]!='\0')//统计空格数
		{
			if(array[index]==' ')
				blankcount++;
			index++;
		}
		//置换空格之后实际数组最后一位的下标
		int lastindex=index+2*blankcount;
		//判断数组容量是否合格
		if(lastindex>length)
		{
			cout<<"数组长度不够！"<<endl;
			return;
		}
		//循环将空格替换为“%20”
		while(index<lastindex&&index>=0)
		{
			if(array[index]==' ')
			{
				array[lastindex--]='0';
				array[lastindex--]='2';
				array[lastindex--]='%';
				index--;
			}
			else
			{
				array[lastindex--]=array[index--];
			}
		}
	}
}
int main()
{
	char a[100]={' ','a','b',' ',' ','c','d',' ','e','f',' '};//测试用例
	cout<<a<<endl;
	replace(a,100);
	cout<<a<<endl;
    char *b="asdasd";
	cout<<b<<endl;
	replace(b,20);
	cout<<b<<endl;
	char c[20]={' ',' '};
	cout<<c<<endl;
	replace(c,20);
	cout<<c<<endl;
	char name[20];



	cin.getline(name,20,'\n');//输入字符串包含空格的话用getline
	cout<<name<<endl;
	return 0;
}