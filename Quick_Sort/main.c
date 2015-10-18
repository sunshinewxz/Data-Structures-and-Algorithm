#include <stdio.h>
#include <stdlib.h>

int quick_divide(int* sort,int i,int j)
{
    sort[0]=sort[i];
    while(i<j)
    {
        while(i<j&&sort[0]<=sort[j])
            j--;
        if(i<j)
        {
            sort[i]=sort[j];
            i++;
        }
        while(i<j&&sort[i]<=sort[0])
            i++;
        if(i<j)
        {
            sort[j]=sort[i];
            j--;
        }
    }
    sort[i]=sort[0];
    return i;
}


void quick_sort(int* sort,int i,int j)
{
    int flag;
    while(i<j)
    {
        flag=quick_divide(sort,i,j);
        quick_sort(sort,i,flag-1);
        quick_sort(sort,flag+1,j);
    }
    for(i=1;i<6;i++)
        printf("%d;",sort[i]);

}

int main()
{
    int sort[6]={0,5,2,3,1,4};
    int i=1,j=5;
    for(i=1;i<6;i++)
        printf("%d;",sort[i]);
    printf("\n");
    quick_sort(sort,i,j);
    for(i=1;i<6;i++)
        printf("%d;",sort[i]);

    return 0;
}
