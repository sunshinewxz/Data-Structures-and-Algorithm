#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 30

//���������Ľṹ���ʾ��ʽ
typedef struct BiTreeNode
{
    int data;
    struct BiTreeNode *lchild,*rchild;
}BiTreeNode,*BiTree;

//���õݹ鷽����������������ǰ���������
BiTree Create()
{
    int data;
    scanf("%d",&data);
    getchar();      //�Ե��ո��
    if(data==-1)
        return NULL;
    else
    {
        BiTree bitree=(BiTree)malloc(sizeof(BiTreeNode));
        if(bitree==NULL)
            return NULL;
        bitree->data=data;
        bitree->lchild=Create();
        bitree->rchild=Create();
        return bitree;
    }
}

//���еĽṹ���ʾ��ʽ
typedef struct queueelem
{
    BiTree b[MAXSIZE];
    int front,rear;
}Queue;

//��α���������

void LevelOrder(BiTree bt)
{
    Queue q;
    //BiTree m;
    if(bt==NULL)
        return;
    q.front=-1;
    q.rear=0;
    q.b[q.rear]=bt;
    while(q.rear!=q.front)
    {
        q.front=q.front+1;
        printf("%d ",q.b[q.front]->data);
        if(q.b[q.front]->lchild!=NULL)
        {
            q.rear=q.rear+1;
            q.b[q.rear]=q.b[q.front]->lchild;
        }
        if(q.b[q.front]->rchild!=NULL)
        {
            q.rear=q.rear+1;
            q.b[q.rear]=q.b[q.front]->rchild;
        }
    }
}


//ǰ��ݹ����
void PreOrder(BiTree bt)
{
    if(bt!=NULL)
    {
        printf("%d ",bt->data);
        PreOrder(bt->lchild);
        PreOrder(bt->rchild);
    }
}

//����ݹ����
void InOrder(BiTree bt)
{
    if(bt!=NULL)
    {
        InOrder(bt->lchild);
        printf("%d ",bt->data);
        InOrder(bt->rchild);
    }
}

//����ݹ����
void PostOrder(BiTree bt)
{
    if(bt!=NULL)
    {
        PostOrder(bt->lchild);
        PostOrder(bt->rchild);
        printf("%d ",bt->data);
    }
}

//ջ�Ľṹ���ʾ��ʽ
typedef struct stackelem
{
    BiTree a[MAXSIZE];
    int top;
}Stack;


//ջ��ǰ������ǵݹ�ʵ��
void PreOrder_Stack(BiTree bt)
{
    BiTree p;
    Stack st;
    st.top=-1;
    if(bt==NULL)
        return;
    else
    {
        st.top++;
        st.a[st.top]=bt;
        while(st.top!=-1)      //ջ�ǿ�
        {
            p=st.a[st.top];
            st.top--;
            printf("%d ",p->data);
            if(p->rchild!=NULL)             //�Һ�����ջ
            {
                st.top++;
                st.a[st.top]=p->rchild;
            }
            if(p->lchild!=NULL)             //������ջ
            {
                st.top++;
                st.a[st.top]=p->lchild;
            }
        }
    }
}

//ջ����������ǵݹ�ʵ��
void InOrder_Stack(BiTree bt)
{
    BiTree p,q;
    Stack st;
    st.top=-1;
    if(bt==NULL)
        return;
    else
    {
        while(bt!=NULL)             //���������ӽ�ջ
        {
            st.top++;
            st.a[st.top]=bt;
            bt=bt->lchild;
        }
        while(st.top!=-1)
        {
            p=st.a[st.top];
            st.top--;
            printf("%d ",p->data);
            while(p->rchild!=NULL)
            {
                st.top++;
                st.a[st.top]=p->rchild;
                q=p->rchild;
                while(q->lchild!=NULL)
                {
                    st.top++;
                    st.a[st.top]=q->lchild;
                    q=q->lchild;
                }
                break;
            }
        }
    }
}

//ջ�ĺ�������ǵݹ�ʵ��
void PostOrder_Stack(BiTree bt)
{
    Stack st;
    st.top=-1;
    BiTree t;
    do
    {
        while(bt!=NULL)
        {
            st.top++;
            st.a[st.top]=bt;
            bt=bt->lchild;
        }
        t=NULL;
        while(st.top!=-1)
        {
            bt=st.a[st.top];
            if(bt->rchild==t)           //t:NULL�򱻷��ʹ�
            {
                printf("%d ",bt->data);
                st.top--;
                t=bt;
            }
            else
            {
                bt=bt->rchild;
                break;
            }
        }
    }while(st.top!=-1);
}


//�ݹ�ʵ����������߶�
int Height(BiTree bt)
{
    int depthL,depthR;
    if(bt==NULL)
        return 0;
    else
    {
        depthL=Height(bt->lchild);
        depthR=Height(bt->rchild);
        if(depthL>depthR)
            return (depthL+1);
        else
            return (depthR+1);
    }
}

int BitreeLeaf(BiTree bt)
{
    if(bt==NULL)
        return 0;
    else if(bt->lchild==NULL && bt->rchild==NULL)
        return 1;
    return (BitreeLeaf(bt->lchild)+BitreeLeaf(bt->rchild));
}

//��������������н���������
void PreInOrder(char preorder[],char inorder[],int i,int j,int k,int h,BiTree *t)
{
    int m;
    (*t)=(BiTree)malloc(sizeof(BiTreeNode));
    (*t)->data=preorder[i];
    printf("%d ",(*t)->data);
    m=k;
    while(inorder[m]!=preorder[i])
        m++;
    if(m==k)
        (*t)->lchild=NULL;
    else
        PreInOrder(preorder,inorder,i+1,i+m-k,k,m-1,&((*t)->lchild));
    if(m==h)
        (*t)->rchild=NULL;
    else
        PreInOrder(preorder,inorder,i+m-k+1,j,m+1,h,&((*t)->rchild));
}

void CreateBiTree(char preorder[],char inorder[],int n,BiTree root)
{
    if(n<=0)
        root=NULL;
    else
        PreInOrder(preorder,inorder,1,n,1,n,&root);
}

int main()
{
    BiTree btr=Create();

    printf("levelOrder:\n");
    LevelOrder(btr);
    printf("\n");

    printf("preOrder:\n");
    PreOrder(btr);
    printf("\n");

    printf("inOrder:\n");
    InOrder(btr);
    printf("\n");

    printf("postOrder:\n");
    PostOrder(btr);
    printf("\n");

    printf("preOrder_Stack:\n");
    PreOrder_Stack(btr);
    printf("\n");

    printf("inOrder_Stack:\n");
    InOrder_Stack(btr);
    printf("\n");

    printf("postOrder_Stack:\n");
    PostOrder_Stack(btr);
    printf("\n");



    int height;
    printf("height:\n");
    height=Height(btr);
    printf("%d\n",height);

    int leaf;
    printf("leaf:\n");
    leaf=BitreeLeaf(btr);
    printf("%d\n",leaf);
    return 0;

    char preorder[7]={'A','B','C','D','E','F','G'};
    char inorder[7]={'C','B','D','A','E','G','F'};
    BiTree btm;
    CreateBiTree(preorder,inorder,7,btm);
    return 0;
}
