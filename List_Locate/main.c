#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	int freq;
	struct node *prior,*next;
}*DuList,*pNode;

void Locate(DuList L,int x)
{
	pNode p=L->next,q;
	while(p && p->data!=x)
		p=p->next;
	if(p)
	{
		p->freq++;
		q=p;
		if(p->prior)					//2 if to take out the node
			p->prior->next=p->next;
		if(p->next)
			p->next->prior=p->prior;
		p=q->prior;
		while(p!=L && q->freq>p->freq)
			p=p->prior;
		q->next = p->next;
		q->prior=p;
		if(p->next)
			p->next->prior=q;
		p->next=q;
	}
	else
		printf("Error!Not found!\n");
}

