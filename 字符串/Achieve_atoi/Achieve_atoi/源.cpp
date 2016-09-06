#include<iostream>
using namespace std;
//函数说明
//atoi()会扫描参数s字符串，跳过前面的空格字符，直到遇上数字或正负符号才开始做转换，而再 遇到非数字或字符串结束时('/0')才结束转换，并将结果返回。
//返回值：返回转换后的整型数。
int atoi(const char *s)
{
	int i=0,flag=1,result=0;
	while(isspace(s[i]))
		i++;
	if(s[i]=='-')
	{
		flag=-1;
		i++;
	}
	while(isdigit(s[i]))
	{
		result=result*10+(s[i]-'0');
		i++;
	}
	result*=flag;
	return result;
}
int main()
{
	char s[]="    -123";
	int res=atoi(s);
	cout<<res<<endl;
	return 0;
}   