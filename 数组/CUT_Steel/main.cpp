#include<iostream>
#include<stdlib.h>
using namespace std;

//采用递归的方法，每个子问题都会重复计算几遍，时间复杂度为O(2^n)
/**
@p [1-n] 价格数组
@n 钢条长度为n
*/
float Cut_rod(float *p,int n)
{
    int i;
    float q=-1.0;
    if(n==0) return 0;
    for(i=1;i<=n;i++)
        q=max(q,p[i]+Cut_rod(p,n-i));
    return q;
}
//top-down with memoization(备忘)
float Memoized_cut_rod_Aux(float *p,int n,float *r);
float Memoized_cut_rod(float *p,int n)
{
    int i;
    float *r=new float[n+1];
    for(i=0;i<=n;i++)
        r[i]=-1.0;
    return Memoized_cut_rod_Aux(p,n,r);
}

float Memoized_cut_rod_Aux(float *p,int n,float *r)
{
    int i;
    float q=-1.0;
    if(r[n]>=0)
        return r[n];
    if(n==0) return 0;
    for(i=1;i<=n;i++)
        q=max(q,p[i]+Memoized_cut_rod_Aux(p,n-i,r));
    r[n]=q;
    return q;
}
//
float Bottom_up_cut_rod(float *p,int n)
{
    int i,j;
    float q;
    float *r=new float[n+1];
    r[0]=0;
    for(j=1;j<=n;j++)
    {
        q=-1.0;
        for(i=1;i<=j;i++)
            q=max(q,p[i]+r[j-i]);
        r[j]=q;
    }
    return r[n];
}
//
float Extend_Bottom_up_cut_rod(float *p,int n)
{
    int i,j;
    float q;
    float *r=new float[n+1];
    float *s=new float[n+1];
    r[0]=0;
    for(j=1;j<=n;j++)
    {
        q=-1.0;
        for(i=1;i<=j;i++)
            q=max(q,p[i]+r[j-i]);
        r[j]=q;
        s[j]=i;
    }
    return r[n];
}

int main()
{
    float p[11]={0,1.0,5.0,8.0,9.0,10.0,17,17,20,24,30};
    float cut_max;
    cut_max=Cut_rod(p,7);
    cout<<"Cut_rod(p,7):"<<cut_max<<endl;
    cut_max=Memoized_cut_rod(p,7);
    cout<<"Memoized_cut_rod(p,7):"<<cut_max<<endl;
    cut_max=Bottom_up_cut_rod(p,7);
    cout<<"Bottom_up_cut_rod:"<<cut_max<<endl;
    return 0;
}
