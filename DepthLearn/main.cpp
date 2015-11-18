#include<iostream>
#include<string>
#include<queue>
using namespace std;
#define ERROR 1
#define MAX_VERTEX_NUM 100

typedef struct ArcNode{
    int adjvex;
    struct ArcNode *nextarc;
    string info;
}ArcNode;

typedef struct VNode{
    char date;
    ArcNode * firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct{
    AdjList vertices;
    int vexnum,arcnum;        //当前图的vexnum顶点数和arcnum弧数
    int kind;
}ALGraph;

int LocateVex(ALGraph &G,char &v1)
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(G.vertices[i].date==v1)
            return i;
    }
    if(i>=G.vexnum)
        return ERROR;
    else
        return 0;
}
void CreateDG(ALGraph &G)
{
    ArcNode *p,*q;
    char v1,v2;
    char v;
    int i,j,k,n;
    cout<<"Please enter the number of the graph's points and bows:"<<endl;
    cin>>G.vexnum;
    cin>>G.arcnum;
    cout<<"Enter points:"<<endl;

    for(i=0;i<G.vexnum;i++)
    {
        cin>>v;
        G.vertices[i].date=v;
        G.vertices[i].firstarc=NULL;
    }
    cout<<"bows start, end:";
    for(k=0;k<G.arcnum;k++)
    {
        cin>>v1;
        cin>>v2;
        i=LocateVex(G,v1);j=LocateVex(G,v2);

        if(G.vertices[i].firstarc==NULL)
        {
            p=(ArcNode *)new ArcNode;
            G.vertices[i].firstarc=p;
            q=G.vertices[i].firstarc;
        }
        else
        {
            q=G.vertices[i].firstarc;
            for(n=0;n<G.arcnum;n++,q=q->nextarc)
            {
                if(!q->nextarc)
                    break;
            }
            p=(ArcNode *)new ArcNode;
            q->nextarc=p;
            q=q->nextarc;
        }
        q->adjvex=j;
        q->nextarc=NULL;
    }
    cout<<"Create successful!";
}
//----------------深度优先遍历--------------------//

bool visited[MAX_VERTEX_NUM];

int FirstAdjVex(ALGraph &G,int v)
{
    int i;
    int n=-1;
    ArcNode*p;
    p=G.vertices[v].firstarc;
    if(p)
    {
        i=p->adjvex;
        if(visited[i]==false)
            n=i;
    }
    return n;
}

int NextAdjVex(ALGraph &G,int v)
{
    int i;
    int n=-1;
    ArcNode *p;
    p=G.vertices[v].firstarc;
    for(i=p->adjvex;i<G.vexnum,p!=NULL;)
    {
        i=p->adjvex;
        if(visited[i]==false)
        {
            n=i;
            break;
        }
        else
            p=p->nextarc;
    }
    return n;
}

void VisitFuc(ALGraph &G,int v)
{
    cout<<G.vertices[v].date<<" ";
}

void DFS(ALGraph &G,int v)
{
    int w;
    visited[v]=true;
    VisitFuc(G,v);
    for(w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v))
        if(!visited[w]) DFS(G,w);

}
void DFSTraverse(ALGraph &G)
{
    int v;
    for(v=0;v<G.vexnum;v++)
        visited[v]=false;
    cout<<"DFS:"<<endl;
    for(v=0;v<G.vexnum;v++)
    {
        if(!visited[v])
            DFS(G,v);
    }
}

//----------------广度优先遍历--------------------//

void BFSTraverse(ALGraph &G)
{
    int v;
    int w;
    queue<int> q; //STL队列
    for(v=0;v<G.vexnum;v++)
        visited[v]=false;
//  InitQueue(Q);
    cout<<"BFS:";
    for(v=0;v<G.vexnum;v++)
    {
        if(!visited[v])
        {
            visited[v]=true;
            VisitFuc(G,v);

            q.push(v);   //v进队

            while(q.empty()!=true)
            {
                v = q.front();
                q.pop();
                for(w=FirstAdjVex(G,v);w>=0;w=NextAdjVex(G,v))
                {   if(!visited[w])
                    {
                        visited[w]=true;
                        VisitFuc(G,w);

                        q.push(w);
                    }
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////
void menu()
{
    cout<<'\n';
    cout<<" //---------------Graph's single operation---------------//"<<endl;
    cout<<"  **     1.Graph's create                        **"<<endl;
    cout<<"  **     2.DFS                    **"<<endl;
    cout<<"  **     3.BFS                    **"<<endl;
    cout<<"  --------------------------------------------"<<endl;
    cout<<"Please enter operation's number:"<<endl;
}
int main()
{
    ALGraph G;
    int i;
    menu();
    cin>>i;
    while(i<4)
    {
        switch(i)
        {
        case 1:CreateDG(G);break;
        case 2:DFSTraverse(G);cout<<endl;break;
        case 3:BFSTraverse(G);cout<<endl;break;
        default:return ERROR;
        }
        menu();
        cin>>i;
    }
    return 0;
}
