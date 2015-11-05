#include <stdio.h>
#include <stdlib.h>
void arrange_Activity(int st[],int et[],int n)
{
    int result[100]={0},i,j,temp,num=1;
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(et[i]>et[j])
            {
                temp=et[i];
                et[i]=et[j];
                et[j]=temp;
                temp=st[i];
                st[i]=st[j];
                st[j]=temp;
            }
        }
    }

    for(i=0;i<n;i++)
    {
        printf("%d\t",st[i]);
        printf("%d\n",et[i]);
    }


    result[0]=st[0];
    result[1]=et[0];
    j=0;
    for(i=1;i<n;i++)
    {
        if(st[i]>=result[2*j+1])
        {
            j++;
            result[2*j]=st[i];
            result[2*j+1]=et[i];
            num++;
        }
    }
    printf("The number of the activities:\t%d\n",num);
    printf("The arrangement of the activities:\n");
    for(i=0;i<num;i++)
    {
        printf("start time:%d\tEnd time:%d\n",result[2*i],result[2*i+1]);
    }

}


int main()
{
    int st[50]={0},et[50]={0};
    int n,i;
    printf("Please enter the number of the activities!\n");
    scanf("%d",&n);
    printf("Please enter the start time!\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&st[i]);
    }
    printf("Please enter the end time!\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&et[i]);
    }
    arrange_Activity(&st[0],&et[0],n);
    return 0;
}
