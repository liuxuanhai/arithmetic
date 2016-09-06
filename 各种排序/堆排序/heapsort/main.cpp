#include <iostream>
using namespace std;
#define Parent(i) (i/2)
#define Left(i) (2*i)
#define Right(i) (2*i+1)

//这个函数假定left(i) right(i)都满足堆的性质
void Max_heapify(int *A,int i,int A_heaplen)
{
    int l,r,largest,temp;
    l=Left(i);
    r=Right(i);
    if(l<A_heaplen&&A[l]>A[i])
        largest=l;
    else largest=i;
    if(r<A_heaplen&&A[r]>A[largest])
        largest=r;
    if(largest!=i)
    {
        temp=A[i];
        A[i]=A[largest];
        A[largest]=temp;
        Max_heapify(A,largest,A_heaplen);
    }
}

void Bulid_max_heap(int *A,int A_length)
{
    int i,A_heaplen;
    A_heaplen=A_length;
    for(i=A_heaplen/2;i>=0;i--)
        Max_heapify(A,i,A_heaplen);
}

void HeapSort(int *A,int A_length)
{
    int i,temp,A_heaplen=A_length;
    Bulid_max_heap(A,A_length);

    for(i=A_length-1;i>=1;i--)
    {
        temp=A[0];
        A[0]=A[i];
        A[i]=temp;
        A_heaplen--;
        Max_heapify(A,0,A_heaplen);
    }
}
int main()
{
    int j;
    int a[6]={3,6,2,9,1,0};
    HeapSort(a,6);
    for(j=0;j<6;j++)
    {
        cout<<a[j]<<"  ";
    }
    return 0;
}
