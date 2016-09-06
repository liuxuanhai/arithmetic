#include<iostream>
#include<vector>
#define SPACE ' '
using namespace std;
void str_reserve(char *str)
{
	vector<char> vec;//用来存储翻转后的字符串
	char *head=str;
	char *last=str+strlen(str)-1;
	char *q=last;
	while(q!=head)//判断是否到达头结点
	{
		while(*q!=SPACE && q!=head)
		{
			q--;
		}
		if(q==head)
			break;
		char *temp=q+1;
		while(temp!=last)
		{
			vec.push_back(*temp++);
		}
		vec.push_back(*last);
		vec.push_back(SPACE);
		//指针移动到空格前一个的单词尾部
		q--;
		last=q;
	}
	//要将前面的单词也存入vec中
	while(last!=q)
	{
		vec.push_back(*q++);
	}
	vec.push_back(*last);
	//将vec中存的反转单词重新存入原来的字符串
	vector<char>::iterator it;
	head=str;
	for(it=vec.begin();it!=vec.end();it++)
	{
		*head++ = (*it);
	}
}
int main()
{
	char str[]="tom is cat";
	str_reserve(str);
	cout<<str<<endl;
	return 0;
}