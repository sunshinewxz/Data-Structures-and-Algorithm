#include <iostream>

using namespace std;

int n,mn;
/*
分配内存，注意三维数组初始化的方法
*/
void allocateMemory(int *** &x,int rows,int cols,int z)
{
    x=new int **[rows];
    for(int i=0;i<rows;i++)
    {
        x[i]=new int *[cols];
        for(int j=0;j<cols;j++)
            x[i][j]=new int [z];
    }
}

int main()
{
    int ***p;                           //p[i][j][k]表示前k个任务能否在A用时不超过i且B用时不超过j时间内处理完成
    int m=0,i,j,k,result,temp;
    cout<<"Please enter the number of the activities:"<<endl;
    cin>>n;
    int *a=new int[n];
    int *b=new int[n];
    cout<<"Please enter the time:"<<endl;
    for(i=0;i<n;i++)                //a[i]储存A中所用时间
    {
        cin>>a[i];
        if(m<a[i])
            m=a[i];
    }

    for(i=0;i<n;i++)                //b[i]储存B中所用时间
    {
        cin>>b[i];
        if(m<b[i])
            m=b[i];
    }

    allocateMemory(p,m*n+1,m*n+1,n+1);
    for(i=0;i<=m*n;i++)
    {
        for(j=0;j<=m*n;j++)
        {
            p[i][j][0]=true;
            for(k=1;k<=n;k++)
                p[i][j][k]=false;
        }
    }

    for(k=1;k<=n;k++)
    {
        for(i=0;i<=m*n;i++)
        {
            for(j=0;j<=m*n;j++)
            {
                if(i>=a[k-1])
                    p[i][j][k]=p[i-a[k-1]][j][k-1];//前k-1个任务在A中完成
                if(j>=b[k-1])
                    p[i][j][k]=p[i][j-b[k-1]][k-1];//前k-1个任务在B中完成
            }
        }
    }
    result=m*n;
    for(i=0;i<=m*n;i++)
    {
        for(j=0;j<=m*n;j++)
        {
            if(p[i][j][n])
            {
                temp=(i>j)?i:j;
                if(temp<result)
                    result=temp;
            }
        }
    }
    cout<<"result="<<result<<endl;

    return 0;
}
