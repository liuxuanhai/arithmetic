#include<iostream>
using namespace std;
double GetPower(double base,double exp);
bool equals(double number1,double number2);
double  Power(double base,int exponent)
{
	try
	{
		//0的负指数乘积不合法
		if(equals(base,0.0)&&exponent<0)
		{
			throw exception("参数不正确！");
		}
		unsigned int exp=(unsigned int)exponent;
		//如果指数是负数，则先转换n为正数，在计算a^n,最后求倒数
		if(exponent<0)
			exp=(unsigned int)(-exponent);
		//求base^exp,exp为正整数
		double result=GetPower(base,exp);
		//如果指数为负数则求倒数
		if(exponent<0)
			result=1/result;
		return result;
	}
	catch(exception e)
	{
		cerr<<e.what()<<endl;
	}
}
//递归实现
double Power2(double base,int exponent)
{
	try
	{
		//0的负指数乘积不合法
		if(equals(base,0.0)&&exponent<=0)
		{
			throw exception("参数不正确！");
		}
		//递归返回条件
		if(exponent==0)
			return 1;
		if(exponent==1)
			return base;
		if(exponent==-1)
			return 1/base;
		double result=Power2(base,exponent>>1);//递归计算n/2次方
		result*=result;//base的exponent次方=（base的exponent/2次方）*（base的exponent/2次方）
		if(exponent&1==1)//指数为奇数时
			result*=base;//base的exponent次方=（base的exponent/2次方）*（base的exponent/2次方）*base
		return result;
	}
	catch(exception e)
	{
		cerr<<e.what()<<endl;
	}
}
//a^n的实现
double GetPower(double base,double exp)
{
	double result=1.0;
	for(int i=0;i<exp;i++)
		result*=base;
	return result;
}
//判断两个double变量是否相等，不能用==判断，因为计算机表示小数（float和double）都有误差
bool equals(double number1,double number2)
{
	if(number1-number2>-0.00000001&&number1-number2<0.0000001)
		return true;
	else
		return false;
}
int main()
{ 
	cout<<"使用第一种方法："<<endl;
	cout<<"2^3="<<Power(2,3)<<endl;
	cout<<"0^-3="<<Power(0,-3)<<endl;
	cout<<"2^-3="<<Power(2,-3)<<endl;
	cout<<"使用第二种方法："<<endl;
	cout<<"-2^3="<<Power2(-2,3)<<endl;
	cout<<"-2^-3="<<Power2(-2,-3)<<endl;
	return 0;
}