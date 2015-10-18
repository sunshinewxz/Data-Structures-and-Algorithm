#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}Node,*pNode;

typedef struct stack
{
    pNode Top;
    pNode Bottom;
}Stack,*pStack;

void InitStack(pStack ps)
{
    ps->Top=(pNode)malloc(sizeof(Node));
    if(ps->Top==NULL)
    {
        printf("¶¯Ì¬·ÖÅäÄÚ´æÊ§°Ü\n");
        exit(-1);
    }
    else
    {
        ps->Bottom=ps->Top;
        ps->Top->next=NULL;
    }
    return;
}

int Push(pStack ps,int data)
{
    pNode pNew=(pNode)malloc(sizeof(Node));
    if(pNew==NULL)
    {
        return 0;
    }
    pNew->data=data;
    pNew->next=ps->Top;
    ps->Top=pNew;
    return 1;
}

void TraverseStack(pStack ps)
{
    pNode pNew=ps->Top;
    while(pNew!=ps->Bottom)
    {
        printf("%d ",pNew->data);
        pNew=pNew->next;
    }
}

int Empty(pStack ps)
{
    if(ps->Top==ps->Bottom)
        return 1;
    else
        return 0;
}

int Pop(pStack ps)
{
    pNode pSwap=NULL;
    int pop_data;
    if(Empty(ps))
        exit(-1);
    else
    {
        pop_data=ps->Top->data;
        pSwap=ps->Top;
        ps->Top=ps->Top->next;
        free(pSwap);
        return pop_data;
    }
}

void Clear(pStack ps)
{
    pNode pNew=NULL;
    while(ps->Top!=ps->Bottom)
    {
        pNew=ps->Top;
        ps->Top=ps->Top->next;
        free(pNew);
    }
}

int main()
{
    Stack s;
    int i,n;
    int data;
    InitStack(&s);
    printf("number:");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&data);
        if(Push(&s,data))
            continue;
        else
        {
            printf("error!");
            exit(-1);
        }
    }

    TraverseStack(&s);
    printf("delete number:");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("%d",Pop(&s));
    }
    printf("Hello world!\n");
    return 0;
}
