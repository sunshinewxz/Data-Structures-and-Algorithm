#include <stdio.h>
#include <stdlib.h>
void arrange_Packing(int weight[],int value[],int n,int amount)
{
    float result[100]={0},allValue=0;
    int i,j,temp,num=0;
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(value[i]<value[j])
            {
                temp=value[i];
                value[i]=value[j];
                value[j]=temp;
                temp=weight[i];
                weight[i]=weight[j];
                weight[j]=temp;
            }
        }
    }

    for(i=0;i<n;i++)
    {
        printf("%d\t",weight[i]);
        printf("%d\n",value[i]);
    }
    i=0,j=0;
    //for(i=0;i<n;i++)
    //{
        while(weight[i]<=amount && i<n)
        {
            result[2*j]=weight[i];
            result[2*j+1]=value[i];
            allValue+=value[i];
            amount-=weight[i];
            num++,j++,i++;
        }
        //else break;
    //}
    if(amount>0)
        {
            printf("%d\n%d\n",weight[i],value[i]);

            result[2*j]=amount;
            result[2*j+1]=(float)amount/weight[i]*value[i];
            printf("%f\n",(float)amount/weight[i]);
            allValue+=result[2*j+1];
            num++;
        }


    /*
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
    */
    printf("The number of the packings:\t%d\n",num);
    printf("The arrangement of the packings:\n");
    for(i=0;i<num;i++)
    {
        printf("weight:%f\t value:%f\n",result[2*i],result[2*i+1]);
    }
    printf("allValue:%f\n",allValue);

}


int main()
{
    int weight[50]={0},value[50]={0};
    int n,i,amount=0;
    printf("Please enter the packing amount!\n");
    scanf("%d",&amount);
    printf("Please enter the number of the packing!\n");
    scanf("%d",&n);
    printf("Please enter the weight!\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&weight[i]);
    }
    printf("Please enter the value!\n");
    for(i=0;i<n;i++)
    {
        scanf("%d",&value[i]);
    }
    arrange_Packing(&weight[0],&value[0],n,amount);
    return 0;
}
