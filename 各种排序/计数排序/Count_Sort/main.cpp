#include <iostream>
/****************************
计数排序：
对某个范围内的数（这里是0-range）进行排序
用buckets记录比该数小的数的个数决定在output数组中的位置

********************************/
using namespace std;
void countSort(int a[], int n,int range)
{
    int output[n];             // 存储"被排序数据"的临时数组
    int i, buckets[range] ;
    for (i = 0; i < range; i++)
        buckets[i ]=0;

    // 将数据出现的次数存储在buckets[]中
    for (i = 0; i < n; i++)
        buckets[ a[i] ]++;

    // 更改buckets[i]。目的是让更改后的buckets[i]的值，是该数据在output[]中的位置。
    for (i = 1; i < range; i++)
        buckets[i] += buckets[i - 1];

    // 将数据存储到临时数组output[]中
    for (i = n - 1; i >= 0; i--)
    {
        output[buckets[ a[i]] - 1] = a[i];
        buckets[ a[i] ]--;
    }

    // 将排序好的数据赋值给a[]
    for (i = 0; i < n; i++)
        a[i] = output[i];
}

int main()
{
    int i;
    int a[] = {43, 3, 42, 48, 14, 4, 34, 7, 16};
    int ilen = (sizeof(a)) / (sizeof(a[0]));

    countSort(a,ilen,50);
    for (i=0; i<ilen; i++)
        cout << a[i] << " ";
    return 0;
}
