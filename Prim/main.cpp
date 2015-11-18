#include <iostream>
#include <string>
using namespace std;

typedef struct Gragh
{
    string vexs[20];
    int power[20][20];
    int vexnum,arcnum;
}Gragh;

typedef struct CloseEdge
{
    string adjvex;          //所依附结点
    int lowcost;            //当前最小权重
}Closedge[20];

int locateVex(Gragh G,string vex)
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(G.vexs[i]==vex)
            return i;
    }
    return -1;
}

void createUDG(Gragh &G)
{
    int i,m,n,p,j;
    string v1,v2;
    cout<<"Enter the number of the points and the arcs:"<<endl;
    cin>>G.vexnum>>G.arcnum;
    cout<<"Please enter every points:"<<endl;
    for(i=0;i<G.vexnum;i++)
    {
        cin>>G.vexs[i];
    }

    for(i=0;i<G.vexnum;i++)
    {
        for(j=0;j<G.vexnum;j++)
            G.power[i][j]=1000;
    }
    cout<<"Please enter the both arcs and the power:"<<endl;
    for(i=0;i<G.arcnum;i++)
    {
        cin>>v1>>v2>>p;
        m=locateVex(G,v1);
        n=locateVex(G,v2);
        G.power[n][m]=G.power[m][n]=p;
    }
}

int minimum(Closedge closedge,int vexnum)
{
    int min,h,k,i=0;
    while(!closedge[i].lowcost)
        i++;
    min=closedge[i].lowcost;
    h=i;
    for(k=i+1;k<vexnum;k++)
    {
        if(closedge[k].lowcost>0 && closedge[k].lowcost<min)
        {
            min=closedge[k].lowcost;
            h=k;
        }
    }
    return h;
}

void miniSpanTree_PRIM(Gragh G,string u)
{
    int i,k,j;
    Closedge closedge;
    k=locateVex(G,u);
    for(i=0;i<G.vexnum;i++)
    {
        closedge[i].adjvex=u;
        closedge[i].lowcost=G.power[k][i];
    }
    closedge[k].lowcost=0;
    cout<<"Every sides:"<<endl;
    for(i=1;i<G.vexnum;i++)
    {
        k=minimum(closedge,G.vexnum);
        cout<<"<"<<closedge[k].adjvex<<","<<G.vexs[k]<<">"<<endl;
        closedge[k].lowcost=0;
        for(j=0;j<G.vexnum;j++)
        {
            if(G.power[k][j]<closedge[j].lowcost)
            {
                closedge[j].lowcost=G.power[k][j];
                closedge[j].adjvex=G.vexs[k];
            }
        }
    }
}

int main()
{
    Gragh G;
    createUDG(G);
    miniSpanTree_PRIM(G,G.vexs[0]);
    cout<<endl;
    return 0;
}
