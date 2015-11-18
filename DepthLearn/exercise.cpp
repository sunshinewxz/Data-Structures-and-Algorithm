#include <iostream>
#include <queue>
using namespace std;
#define MAX_VERTEX_NUM 100

typedef struct arcnode
{
	int adjvex;//这条弧指向的顶点的位置
	struct arcnode *nextarc;     //弧尾相同的下一条弧或者链表中下一个弧
	int info;//权值
}arcnode;

typedef struct vnode
{
	int data;//结点信息
	arcnode *firstarc; //指向依附于头结点的弧
}vnode,adjList[MAX_VERTEX_NUM];

typedef struct graph
{
	adjList vertices;
	int vexnum,arcnum;
}algragh;

int findVex(algragh &G,int data)
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(G.vertices[i].data==data)
        {
            return i;
        }
    }
    if(i>=G.vexnum)
        return -1;
    else
        return 0;
}

void createAG(algragh &G)
{
    int i,j,v1,v2,k;
    arcnode *p,*q;
    cout<<"Please enter the vexnum and the arcnum:"<<endl;
    cin >>G.vexnum;
    cin >>G.arcnum;
    //cout<<G.vexnum<<endl;
    //cout<<G.arcnum<<endl;
    cout<<"Please enter the data of the points:"<<endl;
    for(i=0;i<G.vexnum;i++)
    {

        cin>>G.vertices[i].data;
        G.vertices[i].firstarc=NULL;
    }
    cout<<"Please enter the data(start end):"<<endl;
    for(k=0;k<G.arcnum;k++)
    {
        cin>>v1;
        cin>>v2;
        i=findVex(G,v1);
        j=findVex(G,v2);
        //cout<<i<<endl;
        //cout<<j<<endl;
        if(G.vertices[i].firstarc==NULL)
        {
            p=(arcnode *)new arcnode;
            G.vertices[i].firstarc=p;
            q=G.vertices[i].firstarc;
        }
        else
        {
            q=G.vertices[i].firstarc;
            while(q->nextarc!=NULL)
                q=q->nextarc;
            //cout<<q->adjvex<<endl;
            p=(arcnode *)new arcnode;
            q->nextarc=p;
            q=q->nextarc;
        }
        q->adjvex=j;
        q->nextarc=NULL;
    }
    cout<<"Create successful!"<<endl;
}

bool visited[MAX_VERTEX_NUM];

void visitPrint(algragh &G,int v)
{
    cout<<G.vertices[v].data<<" ";
}

int firstVex(algragh &G,int v)
{
    int i,n=-1;
    arcnode *p;
    p=G.vertices[v].firstarc;
    if(p)
    {
        i=p->adjvex;
        if(!visited[i])
            n=i;
    }
    return n;
}

int nextVex(algragh &G,int v)
{
    int i,n=-1;
    arcnode *p;
    p=G.vertices[v].firstarc;
    for(i=p->adjvex;i<G.vexnum,p!=NULL;)
    {
        i=p->adjvex;
        if(!visited[i])
        {
            n=i;
            break;
        }
        else
            p=p->nextarc;

    }
    return n;
}

//深度优先遍历
void DFS(algragh &G,int v)
{
    int w;
    visited[v]=true;
    visitPrint(G,v);
    for(w=firstVex(G,v);w>=0;w=nextVex(G,v))
    {
        if(!visited[w])
            DFS(G,w);
    }
}

void DFSTraverse(algragh &G)
{
    int v;
    for(v=0;v<G.vexnum;v++)
    {
        visited[v]=false;
    }
    cout<<"DFS:"<<endl;
    for(v=0;v<G.vexnum;v++)
    {
        if(!visited[v])
            DFS(G,v);
    }
}

//广度优先遍历
void BFSTraverse(algragh &G)
{
    int i,v;
    queue<int> p;
    for(i=0;i<G.vexnum;i++)
    {
        visited[i]=false;
    }
    cout<<"BFS:"<<endl;
    for(i=0;i<G.vexnum;i++)
    {
        if(!visited[i])
        {
            visited[i]=true;
            visitPrint(G,i);
            p.push(i);
            while(p.empty()!=true)
            {
                i=p.front();
                p.pop();
                for(v=firstVex(G,i);v>=0;v=nextVex(G,i))
                {
                    if(!visited[v])
                    {
                        visited[v]=true;
                        visitPrint(G,v);
                        p.push(v);
                    }

                }
            }
        }
    }
}
//深度优先遍历非递归（栈）
/*
void StackTraverse(algragh &G)
{
    int stack[100]={0},i,top=-1,v,w;
    for(i=0;i<G.vexnum;i++)
        visited[i]=false;
    cout<<"StackTraverse:";
    for(i=0;i<G.vexnum;i++)
    {
        if(!visited[i])
        {
            visited[i]=true;
            visitPrint(G,i);
            top++;
            stack[top]=G.vertices[i].data;
            while(top>=0)
            {
                i=findVex(G,stack[top]);
                stack[top]=0;
                top--;
                for(w=firstVex(G,i);w>=0;w=nextVex(G,i))
                {
                    if(!visited[w])
                    {
                        stack[top]=G.vertices[w].data;
                        top++;
                    }
                }
            }
        }
    }
}
*/

void StackTraverse(algragh &G)
{
    int stack[100]={0};
    int i,top=-1,v,w;
    for(i=0;i<G.vexnum;i++)
    {
        visited[i]=false;
    }
    top++;
    stack[top]=G.vertices[0].data;
    while(top>=0)
    {
        v=findVex(G,stack[top]);
        visited[v]=true;
        visitPrint(G,v);
        stack[top]=0;
        top--;
        for(w=firstVex(G,v);w>=0;w=nextVex(G,v))
        {
            if(!visited[w])
                top++;
                stack[top]=G.vertices[w].data;
        }
    }
}

void menu()
{
    cout<<'\n';
    cout<<" //---------------Graph's single operation---------------//"<<endl;
    cout<<"  **     1.Graph's create         **"<<endl;
    cout<<"  **     2.DFS                    **"<<endl;
    cout<<"  **     3.BFS                    **"<<endl;
    cout<<"  **     4.DFSStack               **"<<endl;
    cout<<"  --------------------------------------------"<<endl;
    cout<<"Please enter operation's number:"<<endl;
}

int main()
{
    int i;
    algragh G;
    menu();
    cin>>i;
    while(i<5)
    {
        switch(i)
        {
        case 1:createAG(G);break;
        case 2:DFSTraverse(G);cout<<endl;break;
        case 3:BFSTraverse(G);cout<<endl;break;
        case 4:StackTraverse(G);cout<<endl;break;
        default:return -1;
        }
        menu();
        cin>>i;
    }

    return 0;
}
