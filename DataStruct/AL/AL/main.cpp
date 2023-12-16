#include<stdio.h>
#include<stdlib.h>

#define MVNum 100
int visit[MVNum];
typedef char VerTexType;
typedef struct ArcNode              //表节点
{
    int adjvex;
    struct ArcNode *nextarc;
}ArcNode;

typedef struct VNode                //存放节点数据
{
    VerTexType data;
    ArcNode *firstarc;
}VNode,AdjList[MVNum];
typedef struct                        //存放邻接表数据
{
    AdjList vertices;
    int vexnum,arcnum;                //顶点数和边数
}ALgraph;
int LocateVex(ALgraph G,VerTexType u)
{
    int i;
    for(i=0;i<G.vexnum;i++)
    {
        if(u==G.vertices[i].data)
        {
            return i;
        }
        
    }
    return -1;
}
void CreateUDG(ALgraph &G)
{
    char v1,v2;
    printf("请输入总定点数和总边数");
    scanf("%d %d",&G.vexnum,&G.arcnum);
    getchar();
    for(int i=0;i<G.vexnum;i++)
    {
        scanf("%c",&G.vertices[i].data);
        G.vertices[i].firstarc=NULL;
    }
    
    printf("输入一条边依附的两个顶点\n");
    
    for(int k=0;k<G.arcnum;k++)
    {
        getchar();
        scanf("%c %c",&v1,&v2);
        int i,j;
        i=LocateVex(G,v1);
        j=LocateVex(G,v2);
        ArcNode* p1;
        p1=new ArcNode;
        p1->adjvex=j;
        p1->nextarc=G.vertices[i].firstarc;
        G.vertices[i].firstarc=p1;
        ArcNode *p2;
        p2= new ArcNode;
        p2->adjvex=i;
        p2->nextarc=G.vertices[j].firstarc;
        G.vertices[j].firstarc=p2;
    }
}
void DEF_AL(ALgraph G,int v)
{
    int w=0;
    visit[v]=1;
    ArcNode *p;
    p=new ArcNode;
    p=G.vertices[v].firstarc;
    while(p!=NULL)
    {
        w=p->adjvex;
        if(!visit[w])
        {
            DEF_AL(G,w);
            p=p->nextarc;
        }
        printf("%c ",G.vertices[w].data);
    }
}
void PrintAdjList(ALgraph g)
{
    ArcNode *sn;
    for(int i=0;i<g.vexnum;i++)
    {
        sn=g.vertices[i].firstarc;
        printf("%d",i);
        while(sn!=NULL)
        {
            printf("->%d",sn->adjvex);
 
            sn=sn->nextarc;
        }
        printf("\n");
    }
}

int main()
{
    ALgraph G;
    CreateUDG(G);
    PrintAdjList(G);
}

