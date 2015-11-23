#include <iostream>
#include <string>
#define MAX 20
using namespace std;

//string S[MAX];
int T[MAX];
int dist[MAX]={500};
typedef struct Gragh
{
    int vexnum,arcnum;
    string point[MAX];
    int arc[MAX][MAX];
}Gragh;

int findVex(Gragh G,string point)
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(G.point[i]==point)
            return i;
    }
    return 0;
}

void createGragh(Gragh &G)
{
    int i,p,m,n,j;
    string v1,v2;
    cout<<"Please enter the vexnum and the arcnum:"<<endl;
    cin>>G.vexnum>>G.arcnum;
    cout<<"Please enter the points:"<<endl;
    for(i=0;i<G.vexnum;i++)
        cin>>G.point[i];
    for(i=0;i<G.arcnum;i++)                 //初始化使每两个点之间的距离为最大
    {
        for(j=0;j<G.arcnum;j++)
            G.arc[i][j]=500;
    }
    cout<<"Please enter the arcs and the distance:"<<endl;
    for(i=0;i<G.arcnum;i++)
    {
        cin>>v1>>v2>>p;
        m=findVex(G,v1);
        n=findVex(G,v2);
        G.arc[m][n]=p;
    }
    for(i=0;i<G.vexnum;i++)
        dist[i]=G.arc[0][i];
}

int find_Min(Gragh G)
{
    int i,m=dist[0],loc=0;
    for(i=0;i<G.vexnum;i++)
    {
        if(T[i]!=0)
        {
            if(dist[i]<m)
            {
                m=dist[i];
                loc=i;
            }
        }

    }
    return loc;
}

void find_Path(Gragh G)
{
    int si,i,Sn=1,Tn=G.vexnum-1,m;       //sn是数组s中的元素个数,Tn是数组T中的元素个数
    //S[0]=G.point[0];
    for(i=1;i<G.vexnum;i++)         //i表示T中vi的位置，T储存还未找到最短路径的顶点位置
        T[i]=i;
    si=1;
    while(Sn<G.vexnum)
    {
        m=find_Min(G);
        //S[si]=G.point[m];
        //si++;
        Sn++;
        i++;
        T[m]=0;
        Tn--;
        for(i=0;i<G.vexnum;i++)
        {
            if((dist[m]+G.arc[m][i])<dist[i])
            {
                dist[i]=(dist[m]+G.arc[m][i]);
            }
        }
    }
}

int main()
{
    int i;
    Gragh G;
    createGragh(G);
    find_Path(G);
    for(i=1;i<G.vexnum;i++)
        cout<<dist[i]<<endl;
    //cout << "Hello world!" << endl;
    return 0;
}
