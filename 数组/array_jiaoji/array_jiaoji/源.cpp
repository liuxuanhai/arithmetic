#include<iostream>
#include<iterator>
#include <algorithm>
#include<set>
using namespace std;
void jiaoji(long a[],long b[],long alength,long blength,long dongtai[])
{
	set<long> s;
	set<long>::iterator it;
	set_intersection(a,a+alength,b,b+blength,insert_iterator<set<long>>(s,s.begin()));
	copy(s.begin(),s.end(),dongtai);
}
int main()
{
	long a[4]={1,3,5,7};
	long b[4]={2,4,5,7};
	long c[4]={0};
	jiaoji(a,b,4,4,c);
	int i=0;
	while(c[i]!=0)
	{
		cout<<c[i++]<<" ";
	}
	return 0;
}