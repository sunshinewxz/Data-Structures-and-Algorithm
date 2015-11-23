#include <iostream>
#include <string>
#define max 20
using namespace std;

string topo[max];
typedef struct arcnode
{
    int adjvex;
    struct arcnode *nextarc;
    int time;
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
    int i,m,n,pow;
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
    cout<<"Please enter the arcs and the power:"<<endl;
    for(i=0;i<G.arcnum;i++)
    {
        cin>>v1;
        cin>>v2;
        cin>>pow;
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
        q->time=pow;
        q->adjvex=n;
        q->nextarc=NULL;
    }
    cout<<"Create successful!"<<endl;

}

void findIndegree(algragh G,int *indegree)         //Çó³öÍ¼ÖÐËùÓÐµãµÄÈë¶È
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
    int top=-1,k,m,n=0,i;
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
        cout<<stack[top]<<endl;
        topo[n]=stack[top];
        n++;
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

//点代表事件，边代表活动
int critical(algragh G)
{
    int time=0;
    int i,k,n=0,j,s,ne=0;
    arcnode *p;
    int ev[G.vexnum],lv[G.vexnum],l[G.arcnum],e[G.arcnum];//ev每个点的最早出现时间,lv每个点的最迟出现时间,l每条弧的最早开始时间,e每条弧的最迟出现时间
    for(i=0;i<G.vexnum;i++)
    {
        ev[i]=0;
    }
    ne=findVex(G,topo[0]);
    for(k=0;k<G.vexnum;k++)                             //求各点最早出现时间
    {
        i=findVex(G,topo[k]);
        p=G.vertices[i].firstarc;
        while(p!=NULL)
        {
            j=p->adjvex;
            //cout<<"p->adjvex="<<p->adjvex<<endl;
            if(ev[i]+p->time>ev[j])
                ev[j]=ev[i]+p->time;
            p=p->nextarc;
        }
        /*
        ev[m]=ev[n]+p->time;
        cout<<"n="<<n<<endl;
        n=m;
        ne=findVex(G,topo[k]);
        cout<<"m="<<m<<endl;
        cout<<"ev[m]="<<ev[m]<<endl;
        cout<<"ne="<<ne<<endl;
        */
    }

    for(i=0;i<G.vexnum;i++)
        lv[i]=ev[G.vexnum-1];
    n=findVex(G,topo[G.vexnum-1]);
    for(k=G.vexnum-2;k>=0;k--)                            //求各点最迟出现时间
    {
        i=findVex(G,topo[k]);
        p=G.vertices[i].firstarc;
        while(p!=NULL)
        {
            j=p->adjvex;
            if(lv[j]-p->time<lv[i])
                lv[i]=lv[j]-p->time;
            p=p->nextarc;
        }
        //lv[m]=lv[n]-G.vertices[m].firstarc->time;
        //n=m;
    }
    k=0;
    for(i=0;i<G.vexnum;i++)
    {
        s=findVex(G,topo[i]);
        p=G.vertices[s].firstarc;
        while(p!=NULL)
        {
            j=p->adjvex;
            e[k]=ev[i];
            l[k]=lv[j]-p->time;
            if(e[k]==l[k])
            {
                time=time+G.vertices[k].firstarc->time;
                cout<<"&&&&&&time="<<time<<endl;
                //cout<<"<"<<i+1<<","<<j+1<<">"<<endl;

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
    topoSort(G,indegree);
    //for(i=0;i<G.vexnum;i++)
        //cout<<"########"<<topo[i]<<endl;
    critical(G);
    return 0;
}
