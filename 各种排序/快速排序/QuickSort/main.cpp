#include <iostream>
using namespace std;
int Partion(int *A,int p,int r)
{
    int x,i,j,temp;
    x=A[r];
    i=p-1;
    for(j=p;j<=r-1;j++)
    {
        if(A[j]<=x)
        {
        i++;
        temp=A[i];
        A[i]=A[j];
        A[j]=temp;
        }
    }
    temp=A[i+1];
    A[i+1]=A[r];
    A[r]=temp;
    return i+1;
}
void QuickSort(int *A,int p,int r)
{
    int q;
    if(p<r)
    {
        q=Partion(A,p,r);
        QuickSort(A,p,q-1);
        QuickSort(A,q+1,r);
    }
}



int main()
{
    int i;
    int a[6]={3,6,2,9,1,0};
    QuickSort(a,0,5);
    for(i=0;i<6;i++)
    {
        cout<<a[i]<<"  ";
    }
    return 0;
}
