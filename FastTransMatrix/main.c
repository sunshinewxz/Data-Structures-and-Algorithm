#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100

struct Triple_Item
{
	int row,col;
	int value;
};

struct Triple_Table
{
	struct Triple_Item data[MAXSIZE];				//存储非零元素的一维数组，包含行列数三项
	int mu,nu,tu;							//稀疏矩阵总行数，总列数，非零元素个数
};								//三元组表的存储类型

int createTriple_Table(struct Triple_Table *A)
{
	int temp,row,col,num;
	printf("Please enter the number of the row and the col:\n");
	scanf("%d,%d",&A->mu,&A->nu);

	printf("Please enter the elements:\n");							//按行输入
	num=0;
	for(row=0;row<A->mu;row++)
	{
		for(col=0;col<A->nu;col++)
		{
			scanf("%d",&temp);
			if(temp)
			{
				A->data[num].row=row;
				A->data[num].col=col;
				A->data[num].value=temp;
				num++;
			}
		}
		A->tu=num;
	}

	return 0;
}

void show(struct Triple_Table *A)
{
	int i;
	for(i=0;i<A->tu;i++)
		printf("%d ",A->data[i].value);
    printf("\n");
}

void FastTransMatrix(struct Triple_Table *a,struct Triple_Table *b)				//a，b是矩阵的三元组表，将a转置为b
{
	int i,j,k;
	int num[a->nu],copt[a->nu];
	b->mu=a->nu;
	b->nu=a->mu;
	b->tu=a->tu;
	if(a->tu>0)
	{
		for(i=0;i<a->nu;i++)
			num[i]=0;
		for(i=0;i<a->tu;i++)
		{
			j=a->data[i].col;
			num[j]++;
		}

		copt[0]=0;
		for(i=1;i<a->nu;i++)
			copt[i]=copt[i-1]+num[i-1];
		for(i=0;i<a->tu;i++)
		{
			j=a->data[i].col;
			k=copt[j];
			b->data[k].row = a->data[i].col;
			b->data[k].col = a->data[i].row;
			b->data[k].value = a->data[i].value;
			copt[j]++;
		}
	}
	show(&*b);
}



int main()
{
	struct Triple_Table A;
	struct Triple_Table B;
	createTriple_Table(&A);
	FastTransMatrix(&A,&B);
	show(&B);
    return 0;
}
