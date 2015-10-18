//哈夫曼编码和解码2015.10.17
#include <iostream>
using namespace std;

int m,s1,s2;	//m总结点个数
typedef struct{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;

typedef char* HuffmanCode;

void SelectMin(HuffmanTree HT,int nNode)
{
	int i,j,temp;
	for(i=1;i<=nNode;i++)
	{
		if(!HT[i].parent)
		{
			s1=i;
			break;
		}
	}

	for(j=i+1;j<=nNode;j++)
	{
		if(!HT[j].parent)
		{
			s2=j;
			break;
		}
	}

	for(i=1;i<=nNode;i++)
	{
		if(HT[i].weight<HT[s1].weight && (!HT[i].parent) && (s2!=i))
			s1=i;
	}
	for(j=1;j<=nNode;j++)
	{
		if(HT[j].weight<HT[s2].weight && (!HT[j].parent) && (s1!=j))
			s2=j;
	}

	if(HT[s1].weight>HT[s2].weight)
	{
		temp=s1;
		s1=s2;
		s2=temp;
	}
}

//构造哈夫曼树，求出哈夫曼编码
//HT:哈夫曼树 ； HC:指向字符的指针
void HuffmanCoding(HuffmanTree &HT,HuffmanCode *&HC,int *w,int nNode)
{
	int i,p;
	char *hfcode;
	if(nNode<1)
		return;
	m=2*nNode-1;			//哈夫曼树的结点数

	//哈夫曼树初始化
	HT=(HTNode*)malloc((m+1)*sizeof(HTNode));
	for(i=1;i<=nNode;i++)
	{
		HT[i].weight=w[i-1];
		HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
	}
	for(i=nNode+1;i<=m;i++)
	{
		HT[i].weight=0;
		HT[i].parent=0;
		HT[i].lchild=0;
		HT[i].rchild=0;
	}

	//哈夫曼树构建
	for(i=nNode+1;i<=m;i++)
	{
		SelectMin(HT,i-1);
		HT[s1].parent=i;
		HT[s2].parent=i;
		HT[i].lchild=s1;
		HT[i].rchild=s2;
		HT[i].weight=HT[s1].weight+HT[s2].weight;
	}
	hfcode=(char *)malloc((nNode+1)*sizeof(char));//叶子结点最长编码个数为nNode，因最后有'\0'，故＋1
	hfcode[nNode]='\0';
	int start;
	int c;
	for(i=1;i<=nNode;i++)
	{
		start=nNode;
		for(c=i,p=HT[c].parent;p!=0;c=p,p=HT[p].parent)
		{
			if(c==HT[p].lchild)
			{
				start--;
				hfcode[start]='0';
			}
			else if(c==HT[p].rchild)
			{
				start--;
				hfcode[start]='1';
			}
		}
		HC[i]=(char *)malloc((nNode-start+1)*sizeof(char));
		strcpy(HC[i],&hfcode[start]);
	}
	free(hfcode);
}

void HuffmanDecode(HuffmanTree HT,int w[],char code[])
{
	char *ch=code;
	int i;
	while(*ch!='\0')
	{
		for(i=m;HT[i].lchild!=0 && HT[i].rchild!=0;)
		{
			if(*ch=='0')
				i=HT[i].lchild;
			else if(*ch=='1')
				i=HT[i].rchild;
			++ch;
		}
		cout<<w[i-1]<<" ";
	}
}

int main()
{
	HuffmanTree HT=NULL;
	HuffmanCode *HC;
	int nNode,*w,i;
	char CodeStr[20]={0};
	cout<<"number of the leaf node:"<<endl;
	cin>>nNode;
	HC=(HuffmanCode *)malloc(nNode*sizeof(HuffmanCode));
	w=(int *)malloc(nNode*sizeof(int));
	cout<<"all nodes' weight:"<<endl;
	for(i=0;i<nNode;i++)
	{
		cin>>w[i];
	}
	HuffmanCoding(HT,HC,w,nNode);
	cout<<"HuffmanCoding"<<endl;
	for(i=1;i<=nNode;i++)
	{
		cout<<i<<"("<<w[i-1]<<"):"<<HC[i]<<endl;
		strcat(CodeStr,HC[nNode-i+1]);
	}
	cout<<"Decode("<<CodeStr<<"):"<<endl;
	HuffmanDecode(HT,w,CodeStr);
	return 0;
}












