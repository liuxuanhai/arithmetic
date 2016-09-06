#include <iostream>
using namespace std;



class maximum_sub{
public:int low;
       int high;
       int sum;

       void set_data(int l,int h,int s){low=l;high=h;sum=s;}
};
maximum_sub* find_max_cross_subarray(int *A,int low,int mid,int high){

    int i,max_left,max_right;
    maximum_sub *p_cross;
    p_cross=new maximum_sub;
    int sum=0,left_sum=-1000,right_sum=-1000;

    for(i=mid;i>=low;i--)
    {
        sum+=A[i];
        if(sum>left_sum){
            left_sum=sum;
            max_left=i;
        }
    }
    sum=0;
    for(i=mid+1;i<=high;i++)
    {
        sum+=A[i];
        if(sum>right_sum){
            right_sum=sum;
            max_right=i;
        }
    }
    p_cross->set_data(max_left,max_right,right_sum+left_sum);
    return  p_cross;
}

maximum_sub* find_max_subarray(int *A,int low,int high){

    maximum_sub* p_left,* p_right,* p_cross;
    maximum_sub *p_base=new maximum_sub;
    int mid;

    if(low==high){
        p_base->set_data(low,high,A[low]);
        return  p_base;
    }
    else{
        mid=(low+high)/2;
        p_left   =find_max_subarray(A,low,mid);
        p_right  =find_max_subarray(A,mid+1,high);
        p_cross  =find_max_cross_subarray(A,low,mid,high);
    }
    if(((p_left->sum)>=(p_right->sum))&&((p_left->sum)>=(p_cross->sum)))
        return  p_left;
    else if(((p_right->sum)>=(p_left->sum))&&((p_right->sum)>=(p_cross->sum)))
        return  p_right;
    else return  p_cross;
}

int main()
{
    int a[7]={2,-5,3,-3,3,5,-15};
    maximum_sub* p=find_max_subarray(a,0,5);
    cout<<"the low is:"<<p->low<<"  "<<"the high is:"<<p->high<<"  "<<"the sum is:"<<p->sum;


   return 0;
}


