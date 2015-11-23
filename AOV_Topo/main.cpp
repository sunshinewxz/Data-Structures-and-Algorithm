#include <iostream>
#include <string>
#define max 20
using namespace std;

typedef struct arcnode
{
    int adjvex;
    struct arcnode *nextarc;
}arcnode;

typedef struct vnode
{
    string node;
    arcnode *firstarc;
}vnode,adjlist;

typedef struct
{
    adjlist vertices[max];
    int vexnum,arcnum;
}algragh;

int findVex(algragh G,string vex)
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(vex==G.vertices[i].node)
            return i;
    }
    if(i>=G.vexnum)
        return -1;
    else
        return 0;
}

void createGragh(algragh &G)
{
    int i,m,n;
    string v1,v2;
    arcnode *p,*q;
    cout<<"Please enter the vexnum and the arcnum:"<<endl;
    cin>>G.vexnum>>G.arcnum;
    cout<<"Please enter the points:"<<endl;
    for(i=0;i<G.vexnum;i++)
    {
        cin>>G.vertices[i].node;
        G.vertices[i].firstarc=NULL;
    }
    cout<<"Please enter the arcs:"<<endl;
    for(i=0;i<G.arcnum;i++)
    {
        cin>>v1;
        cin>>v2;
        m=findVex(G,v1);
        n=findVex(G,v2);
        if(G.vertices[m].firstarc==NULL)
        {
            p=(arcnode *)new arcnode;
            G.vertices[m].firstarc=p;
            q=G.vertices[m].firstarc;
        }
        else
        {
            q=G.vertices[m].firstarc;
            while(q->nextarc!=NULL)
                q=q->nextarc;
            p=(arcnode *)new arcnode;
            q->nextarc=p;
            q=q->nextarc;
        }
        q->adjvex=n;
        q->nextarc=NULL;
    }
    cout<<"Create successful!"<<endl;

}

void findIndegree(algragh G,int *indegree)         //求出图中所有点的入度
{
    int i,j;
    arcnode *p;
    for(i=0;i<max;i++)
        indegree[i]=0;
    for(i=0;i<G.vexnum;i++)
    {
        p=G.vertices[i].firstarc;
        while(p)
        {
            j=p->adjvex;
            indegree[j]++;
            p=p->nextarc;
        }
    }
}

int topoSort(algragh G,int indegree[])
{
    string stack[max];
    int top=-1,k,m,i;
    arcnode *p;
    for(i=0;i<G.vexnum;i++)
    {
        if(indegree[i]==0)
        {
            top++;
            stack[top]=G.vertices[i].node;
        }
    }
    while(top!=-1)
    {
        cout<<"**********"<<stack[top]<<endl;
        k=findVex(G,stack[top]);
        //cout<<k<<endl;
        top--;
        p=G.vertices[k].firstarc;
        while(p)
        {
            m=p->adjvex;
            indegree[m]--;
            //cout<<"m="<<m<<endl;
            //cout<<"indegree[m]="<<indegree[m]<<endl;
            if(indegree[m]==0)
            {
                top++;
                stack[top]=G.vertices[m].node;
                //cout<<"##########"<<stack[top]<<endl;
            }
            p=p->nextarc;
        }
    }
    return 0;
}

int main()
{
    //int i;
    algragh G;
    createGragh(G);
    int indegree[max];
    findIndegree(G,indegree);
    //for(i=0;i<G.vexnum;i++)
        //cout<<indegree[i]<<endl;
    topoSort(G,indegree);
    return 0;
}
