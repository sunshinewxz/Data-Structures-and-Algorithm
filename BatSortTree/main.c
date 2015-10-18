#include <stdio.h>
#include <stdlib.h>
typedef struct bi_sort_tree
{
	int key;
	struct bi_sort_tree *lchild,*rchild;
}BiTreeNode,*BiTreePtr;

BiTreePtr bi_insert(BiTreePtr bt,int add)
{
	BiTreePtr node,temp,child;
	if(bt==NULL)
	{
		bt=(BiTreePtr)malloc(sizeof(BiTreeNode));
		bt->key=add;
		bt->lchild=NULL;
		bt->rchild=NULL;
		return bt;
	}
	node=bt;
	while(node!=NULL)
	{
		if(node->key == add)
			return bt;
        else
        {
            temp=node;
            if(node->key > add)
                node=node->lchild;
            else
                node=node->rchild;
        }
	}
	child=(BiTreePtr)malloc(sizeof(BiTreeNode));
	child->key=add;
	child->lchild=NULL;
	child->rchild=NULL;
	if(temp->key > child->key)
		temp->lchild=child;
	else
		temp->rchild=child;

    return bt;

}

int bi_search(BiTreePtr bt,int key)
{
    while(bt!=NULL)
    {
        if(bt->key==key)
            return 1;
        if(bt->key>key)
            return bi_search(bt->lchild,key);
        else
            return bi_search(bt->rchild,key);
    }
    return 0;
}

void bi_delete(BiTreePtr bt,int key)
{
	BiTreePtr node=NULL,subs,pre;
	node=bt;
	if(bt==NULL)
		return;
	while((node!=NULL) && (node->key!=key))
	{
		pre=node;
		if(node->key > key)
			node=node->lchild;
		else
			node=node->rchild;
	}
	if(node==NULL)
	{
		printf("Wrong number!\n");
		return;
	}
	if((node->lchild==NULL) || (node->rchild==NULL))
	{
		if(pre->lchild==node)
		{
			pre->lchild=((node->lchild==NULL)?node->rchild:node->lchild);
		}
		else
		{
			pre->rchild=((node->lchild==NULL)?node->rchild:node->lchild);
		}
	}
	else
	{
		subs=node->lchild;
		while((subs->rchild)!=NULL)
		{
			pre=subs;
			subs=subs->rchild;
		}
		node->key=subs->key;
		if(node->lchild==subs)
			node->lchild=subs->lchild;
		else
			pre->rchild=subs->lchild;
	}

}

void bi_print(BiTreePtr bt)
{
	BiTreePtr p;
	p=bt;
	if(p!=NULL)
	{
		bi_print(p->lchild);
		printf("%d ",p->key);
		bi_print(p->rchild);
	}
}

int main()
{
	int i,flag,num;
	int a[5]={1,3,5,9,6};
	BiTreePtr bt=NULL,root;
	for(i=0;i<5;i++)
	{
		bt=bi_insert(bt,a[i]);
	}
	root=bt;
	bi_print(root);
	printf("\nFind Number:");
	scanf("%d",&num);
	flag=bi_search(bt,num);
	if(flag!=0)
        printf("%d :Yes!\n",num);
    else
        printf("%d :No!\n",num);
    root=bt;
    bi_delete(bt,3);
    bi_print(root);
    printf("\n");
	return 0;
}
