#include <stdio.h>
#include <stdlib.h>

//打印结果
void show(int list[],int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("%d",list[i]);
    }
    printf("\n");
}

//交换数组元素位置
void swap(int *num_a,int *num_b)
{
    int temp=*num_b;
    *num_b=*num_a;
    *num_a=temp;
}

//双向冒泡
void BidBubbleSort(int list[],int n)
{
    int low,high,flag,i;
    low=0;
    high=n-1;
    while(low<high)
    {
        flag=0;
        for(i=low;i<high;i++)
        {
            if(list[i]>list[i+1])
            {
                swap(&list[i],&list[i+1]);
                flag=1;
            }
        }
        if(!flag)
            break;
        high--;
        for(i=high;i>low;i--)
        {
            if(list[i]<list[i-1])
                swap(&list[i],&list[i-1]);
        }
        low++;
    }
}

int main()
{
    int i,n;
    int list[100]={0};
    printf("Please enter the number:\n");
    scanf("%d",&n);
    printf("Please enter the elements:\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&list[i]);
    }
    show(list,n);
    BidBubbleSort(list,n);
    show(list,n);
    //printf("Hello world!\n");
    return 0;
}
