#include<iostream>
using namespace std;
void printnumber(char *number,int n,int index);
//进行加1操作并判断是否溢出
bool Increment(char * number)
{
	bool isoverflow=false;//判断是否溢出
	int overstack=0;//进位标志
	int length=strlen(number);//字符串的长度
	for(int i=length-1;i>=0;i--)
	{
		int digit=number[i]-'0'+overstack;//获得当前位上的数字
		//如果在个位的话就进行加一
		if(i==length-1)
		{
			digit++;
		}
		//判断加一之后是否需要进位
		if(digit>=10)
		{
			//如果当前位在最高位的话，溢出
			if(i==0)
			{
				isoverflow=true;
				break;
			}
			//没有溢出时候，进位标志赋值1，当前位-=10
			else
			{
				overstack=1;
				digit-=10;
				number[i]='0'+digit;
				continue;
			}
		}
		//加1之后不需要进位，则直接跳出循环
		else
		{
			number[i]='0'+digit;
			break;
		}

	}
	return isoverflow;
}
//打印number中存的数字
void Print(char * number)
{
	bool beginprint=false;//区分是前面的0还是数字中的0，为true的话就一直打印下去
	int length=strlen(number);
	for(int i=0;i<length;i++)
	{
		if(number[i]!='0'&&(beginprint==false))//如果遇到第一个非0数则设置beginprint为true，开始打印
			beginprint=true;
		if(beginprint)
			cout<<number[i];
	}
	cout<<"  ";
}
void printtomax(int n)
{
	try
	{
		if(n<=0)
			throw exception("参数不合法！n>0");
		char *number=new char[n+1];

		memset(number,'0',n*sizeof(char));//先初始化在给最后一位赋值‘\0’
		number[n]='\0';
		while(!Increment(number))//如果number加1之后没有溢出则打印该数字
		{
			Print(number);
		}
		delete[] number;
	}
	catch(exception e)
	{
		cerr<<e.what()<<endl;
	}
}
//第二种方法实现（使用递归）
void printtomax2(int n)
{
	try
	{
		if(n<=0)
			throw exception("参数不合法");
		char *number=new char[n+1];
		number[n]='\0';
		printnumber(number,n,-1);//调用递归方法
	}
	catch(exception e)
	{
		cerr<<e.what()<<endl;
	}
}
void printnumber(char *number,int n,int index)
{
	//判断最后一位数字是否已经赋值，是则打印
	if(index==n-1)
	{
		Print(number);
		return;
	}
	//否则递归赋值，直到到达最后一位
	else
	{
		//从下一位开始，0-9依次赋值
		for(int i=0;i<10;i++)
		{
			number[index+1]='0'+i;
			
			printnumber(number,n,index+1);
		}
	}
}
int main()
{
	printtomax2(2);
	return 0;
}