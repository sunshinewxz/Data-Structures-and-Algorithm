#include <iostream>
#include <string>
using namespace std;

typedef struct Gragh
{
    string vexs[20];
    int power[20][20];
    int vexnum,arcnum;
}Gragh;

typedef struct Acr
{
    int pre;
    int bak;
    int weight;
}Edg[40];

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
    int i,j,p,m,n;
    string v1,v2;
    cout<<"Please enter the number of the points and the arcs:"<<endl;
    cin>>G.vexnum>>G.arcnum;
    cout<<"Please enter the points:"<<endl;
    for(i=0;i<G.vexnum;i++)
    {
        cin>>G.vexs[i];
    }
    for(i=0;i<20;i++)
    {
        for(j=0;j<20;j++)
            G.power[i][j]=1000;
    }
    cout<<"Please enter both arcs and the power:"<<endl;
    for(i=0;i<G.arcnum;i++)
    {
        cin>>v1>>v2>>p;
        m=locateVex(G,v1);
        n=locateVex(G,v2);
        G.power[m][n]=G.power[n][m]=p;
    }
}

void sort(Edg edg,Gragh G)
{
    int i,j,k,min,m,n;
    for(i=0;i<40;i++)
    {
        edg[i].weight=1000;
    }
    min=G.power[0][0];
    for(k=0;k<G.arcnum;k++)
    {
        for(i=0;i<G.vexnum;i++)
        {
            for(j=0;j<G.vexnum;j++)
            {
                if(G.power[i][j]<min)
                {
                    min=G.power[i][j];
                    //cout<<min<<endl;
                    m=i;
                    n=j;
                }
            }
        }
        edg[k].pre=m;
        edg[k].bak=n;
        edg[k].weight=min;
        min=1000;
        G.power[m][n]=G.power[n][m]=1000;
        //cout<<edg[k].pre<<endl;
        //cout<<edg[k].bak<<endl;
        //cout<<edg[k].weight<<endl;
    }
}

int arcvisited[20]={0};

int find(int arcvisited[],int f)
{
    while(arcvisited[f]>0)
        f=arcvisited[f];
    return f;
}

void kruskal(Gragh G,Edg edg)
{
    int i,m,n,buf,edf;
    sort(edg,G);
    for(i=0;i<G.vexnum;i++)
    {
        arcvisited[i]=0;
    }
    for(i=0;i<G.arcnum;i++)
    {
        m=edg[i].pre;
        n=edg[i].bak;
        //cout<<m<<endl;
        //cout<<n<<endl;
        buf=find(arcvisited,m);
        edf=find(arcvisited,n);
        if(buf!=edf)
        {
            arcvisited[buf]=edf;
            cout<<G.vexs[m]<<"-"<<G.vexs[n]<<endl;
        }
    }
}

int main()
{
    Gragh G;
    Edg edg;
    createUDG(G);
    kruskal(G,edg);
    return 0;
}
