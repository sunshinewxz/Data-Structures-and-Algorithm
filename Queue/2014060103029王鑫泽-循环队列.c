#include <stdio.h>
#include <stdlib.h>
//作业：循环队列

int Queue[100]={0},num=0,front=-1,rear=-1;

int print()
{
    int i,j;
    i=front;
    j=rear;
    if(num==0)
        printf("Empty!\n");
    else
    {
        while(i!=j)
        {
            i=(i+1)%100;
            printf("%d;",Queue[i]);
        }
        printf("\n");
    }

    return 0;
}

int main()
{
    int temp,i=0,j=0,a;
    printf("Please enter your command:\n");
    scanf("%d",&temp);
    while(temp!=0)
    {
        if(temp>0)              //Command: add to the queue
        {
            if((front==rear)&&num!=0)       //the queue is full
                printf("Overflow!\n");
            else
            {
                rear=(rear+1)%100;
                Queue[rear]=temp;
                num++;
                print();
            }
        }

        else if(temp==-1)                   //Command: delete the elements
        {
            if((front==rear)&&num==0)           //the queue is empty
                printf("ERROR: the queue is empty!\n");
            else
            {
                front=(front+1)%100;
                num--;
                print();
            }
        }

        else
        {
            printf("Invalid Input!\n");
        }

        scanf("%d",&temp);
    }
    printf("The input has been over,the queue is:\n");
    printf("Queue: ");
    print();

    return 0;
}
