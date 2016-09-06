#include<iostream>  
using namespace std;  
typedef struct Relation_  //关系
{  
    int first;  
    int end;  
}Re;  
typedef struct Leader_  //镇长人选
{  
    int mun;  
    int*pResult;  
}Le;  
Le GetLeader(int Sum,int M,Re*pRelation) // 参数分别为总人数。关系对数。关系链表
{  
     int i=0;  
     int*p1=new int [Sum];//biao shi zong ren ren shi de ren  
     int*p2=new int [Sum];//zi ji ren shi bie ren  
     Le mLe;  
     mLe.mun=0;  
     int*pResult=new int[Sum];  
  
     for(i=0;i<Sum;i++)  
     {  
         p1[i]=p2[i]=0;  
     }  
     for(i=0;i<M;i++)  
     {  
         if(pRelation[i].first!=pRelation[i].end)  
         {  
             p1[pRelation[i].end-1]++;  
             p2[pRelation[i].first-1]=1;  
         }  
     }  
     for(i=0;i<Sum;i++)  
     {  
         if(p2[i]!=1 && p1[i]==Sum-1)  
         {  
             pResult[mLe.mun]=i+1;  
             mLe.mun++;  
         }  
     }  
     mLe.pResult=pResult;  
     if(p1!=NULL)  
     delete []p1;  
     if(p2!=NULL)  
     delete []p2;  
     return mLe;  
}   
void GetResult()  
{  
    int T;  
    cout<<"请输入将要测试几组数据:"<<endl;  
    cin>>T;  
    int i;  
    int Sum;  
    int M;  
    int first,end;  
    for(i=0;i<T;i++)  
    {  
        cout<<"第 "<<i+1<<" 组数据："<<endl;  
        cout<<"总人数：";  
        cin>>Sum;  
        cout<<"关系对数：";  
        cin>>M;  
        cout<<"如下："<<endl;  
        Re* pRelation=new Re[M];  
        int j;  
        //for(j=0;j<Sum;j++)pRelation[j].first=pRelation[j].end=0;  
  
        for(j=0;j<M;j++)  
        {  
            cin>>first>>end;  
            pRelation[j].first=first;  
            pRelation[j].end=end;  
        }  
        cout<<"镇长："<<endl;  
        Le mLe=GetLeader(Sum,M,pRelation);  
        cout<<"候选人数："<<mLe.mun<<endl;  
        cout<<"镇长为：";  
        for(j=0;j<mLe.mun;j++)cout<<mLe.pResult[j]<<" ";  
        //cout<<endl;  
        if(mLe.pResult!=NULL)delete []mLe.pResult;  
        if(pRelation!=NULL)delete []pRelation;  
        cout<<endl;  
    }  
}  
int main()  
{  
    GetResult();  
    return 0;  
} 