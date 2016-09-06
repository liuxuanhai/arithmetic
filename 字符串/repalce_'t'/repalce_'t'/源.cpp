#include<iostream>
#include<string>
using namespace std;
//重新申请内存
string replace(const string& src,int length)
{
	if(length<0||src.empty())
	{
		return NULL;
	}
	string temp;
	for (int i = 0; i < length; i++)
	{
		if(src[i]=='\t')
		{
			temp+="    ";
		}
		else
		{
			temp+=src[i];
		}
	}
	return temp;
}
//在原字符串替换
void Replace(char src[],int length)
{
	if(src==NULL||length<0)
	{
		return;
	}
	int lastindex=0;//替换后
	int count=0;//字符的个数
	int beforeindex=length;//替换前
	for (int i = 0; i < length; i++)
	{
		if(src[i]=='\t')
			count++;
	}
	lastindex=length+3*count;
	while(lastindex>beforeindex && beforeindex>=0)
	{
		if(src[beforeindex]=='\t')
		{
			src[lastindex--]=' ';
			src[lastindex--]=' ';
			src[lastindex--]=' ';
			src[lastindex--]=' ';
		}
		else
		{
			src[lastindex--]=src[beforeindex];
		}
		beforeindex--;
	}
}
int main()
{
	char temp[20]="hello\taaa";
	Replace(temp,strlen(temp));
	cout<<temp<<endl;
	return 0;
}