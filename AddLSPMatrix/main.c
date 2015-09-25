#include <stdio.h>
#include <stdlib.h>
#define Row 100
#define Col 100

struct node
{
	int col;
	int value;
	struct node *next;			//本行下一个非零元素指针
}SPNode,*SPNodePtr;

SPNodePtr LSPMatrix[Row];

void createLSPMatrix(LSPMatrix s)
{
	int row,col,i,j,temp;
	printf("please enter the row and the col:\n");
	scanf("%d,%d",&row,&col);
	printf("Please enter the elements:\n");
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			scanf("%d",&temp);
			if(temp)
			{
				s[i]->col=j;
				s[i]->value=temp;
			}
		}
	}
}

void addLSPMatrix(LSPMatrix SP1,LSPMatrix SP2,LSPMatrix SP)
{
	int i,col,v;
	SPNodePtr pa,pb,s,last;
	for(i=0;i<Row;i++)										//逐行处理
	{
		SP[i]=NULL;
		pa=SP1[i];
		pb=SP2[i];
		while(pa!=NULL&&pb!=NULL)							//一行中按列从小到大处理
		{
			if(pa->col==pb->col)							//列号相等
			{
				v=pa->value+pb->value;
				col=pa->col;
				pa=pa->next;
				pb=pb->next;
			}

			else if(pa->col<pb->col)
			{
				v=pa->value;
				col=pa->col;
				pa=pa->next;
			}

			else
			{
				v=pb->value;
				col=pb->col;
				pb=pb->next;
			}

			if(v!=0)
			{
				s=(SPNodePtr)malloc(sizeof(SPNode));
				s->col=col;
				s->value=v;
				s->next=NULL;
				if(SP[i]==NULL)
					SP[i]=s;
				else
					last->next=s;
				last=s;										//last总是指向链表的最后一个结点
			}
		}

		if(pb!=NULL)										//处理剩余的项
			pa=pb;
		while(pa!=NULL)
		{
			s=(SPNodePtr)malloc(sizeof(SPNode));
			s->col=pa->col;
			s->value=pa->value;
			s->next=NULL;
			last->next=s;
			last=s;
			pa=pa->next;
		}
	}
}  

int main()
{
	SPNodePtr SP1;
	SPNodePtr SP2;
	SPNodePtr SP;
	createLSPMatrix(&SP1);
	createLSPMatrix(&SP2);

    printf("Hello world!\n");
    return 0;
}
