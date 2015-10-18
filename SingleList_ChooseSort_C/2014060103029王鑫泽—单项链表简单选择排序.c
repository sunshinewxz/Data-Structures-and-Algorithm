#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *next;
}node,*pNode;

//建立单链表
pNode create_list(int n)
{
    int i;
    pNode head,p,temp;
    head=(pNode)malloc(sizeof(node));
    head->next=NULL;
    temp=head;
    for(i=0;i<n;i++)
    {
        p=(pNode)malloc(sizeof(node));
        p->next=NULL;
        printf("Please enter the data:");
        scanf("%d",&p->value);
        temp->next=p;
        temp=p;
    }
    return head;
}

//打印单链表
void print_list(pNode head)
{
    pNode p=head->next;
    while(p)
    {
        printf("%d;",p->value);
        p=p->next;
    }
    printf("\n");
}

//获得从指针p开始链表中记录的最小值
pNode getminkey(pNode p)
{
    pNode minp;
    minp=p;
    while(p->next)
    {
        if((minp->value)>(p->next->value))
        {
            minp=p->next;
        }
        p=p->next;
    }
    return minp;
}

//选择排序
void selectsort(pNode head)
{
    pNode j;
    pNode i=head->next;
    int temp;
    for(;i->next!=NULL;i=i->next)
    {
        j=getminkey(i);
        if(i->value!=j->value)
        {
            temp=i->value;
            i->value=j->value;
            j->value=temp;
        }
    }
}

int main()
{
    pNode temp,head;
    head=create_list(10);
    print_list(head);
    selectsort(head);
    print_list(head);
    //getch();
    //printf("Hello world!\n");
    return 0;
}
