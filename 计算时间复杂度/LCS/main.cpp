#include<iostream>
#include<stdlib.h>
using namespace std;

//运行时间是O(m*n)
void LCS_length(int *X,int *Y,int X_length,int Y_length,int **b,int **c)
{
    int i,j;



    for(i=0;i<=X_length;i++)
       c[i][0]=0;
    for(j=0;j<=Y_length;j++)
       c[0][j]=0;

    for(i=1;i<=X_length;i++)
        for(j=1;j<=Y_length;j++)
        {
            if(X[i-1]==Y[j-1]){
                c[i][j]=c[i-1][j-1]+1;
                b[i][j]=0;
            }
            else if(c[i-1][j]>=c[i][j-1])
            {
                c[i][j]=c[i-1][j];
                b[i][j]=1;
            }
            else{
                c[i][j]=c[i][j-1];
                b[i][j]=2;
            }
        }


}
//运行时间是O(m+n)
void Get_LCS(int **b,int *X,int i,int j,int *LCS,int *LCS_len){

    if(i==0||j==0){}
    else{
        if(b[i][j]==0)
        {
            *LCS=X[i-1];
            LCS=LCS+1;
            *LCS_len=*LCS_len+1;
            Get_LCS(b,X,i-1,j-1,LCS,LCS_len);
        }
        else if(b[i][j]==1) Get_LCS(b,X,i-1,j,LCS,LCS_len);
        else Get_LCS(b,X,i,j-1,LCS,LCS_len);
    }
}


int main()
{
    int **b,**c,i,j;
    int *X,*Y;
    int x1[]={3,5,9,2,6};
    int y1[]={4,9,3,2,1,6};
    X=x1;Y=y1;
    int X_length=5,Y_length=6,LCS_l=0;
    int *LCS_len=&LCS_l;

    int max_length=(X_length>Y_length)?X_length:Y_length;
    int *LCS=new int[max_length];
    b  = (int **) malloc(sizeof(int *) * (X_length+1));
    for (j=0;j<=X_length;j++){
    b[j] = (int *) malloc(sizeof(int) * (Y_length+1));
    }
    c  = (int **) malloc(sizeof(int *) * (X_length+1));
    for (j=0;j<=X_length;j++){
    c[j] = (int *) malloc(sizeof(int) * (Y_length+1));
    }

    LCS_length(X,Y,X_length,Y_length,b,c);
    cout<<"end of LCS_length"<<endl;

    Get_LCS(b,X,X_length,Y_length,LCS,LCS_len);
    for(i=*LCS_len-1;i>=0;i--)
        cout<<*(LCS+i)<<"  ";
    cout<<endl;
    return 0;
}
