#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define MAXINT 2147483647
//边表
typedef struct sizelist
{
    int info;                 //权值
    int adjvex;               //该边指向的顶点位置
    struct sizelist *nextarc; //链域
} SIZELIST, *PSIZELIST;
//头表
typedef struct headlist
{
    char data;          //顶点值域
    PSIZELIST firstarc; //指向第一个边
} HEADLIST, *PHEADLIST;
//邻接表
typedef struct GraphList
{
    HEADLIST vexs[MAX]; //点集合
    int vexsnum;        //点数
    int arcsnum;        //边数
} GRAPHLIST, *PGRAPHLIST;
//队列节点
typedef struct node
{
    int data;          //值域
    struct node *next; //下一节点指针
} NODE, *PNODE;
//队列
typedef struct queue
{
    PNODE head;   //头指针
    PNODE tail;   //尾指针
    int nodesnum; //节点数
} QUEUE, *PQUEUE;
//存储普利姆算法最小生成树信息表
typedef struct MainTree
{
    int adjvex; //最小边
    int power;  //权值
} MAINTREE, *PMAINTREE;
//克鲁斯卡尔存放边顶点与权值
typedef struct Kruskal
{
    int head;  //头顶点
    int tail;  //尾顶点
    int power; //权值
} KRUSKAL, *PKRUSKAL;

PGRAPHLIST init_GraphList();                                                //初始化一个图，存储结构为邻接表
char *DFS(PGRAPHLIST graph);                                                //深度优先搜索
void DFSED(PGRAPHLIST graph, int v, _Bool *visited, char *val, int *count); //深度优先搜索连通图
char *BFS(PGRAPHLIST graph);                                                //广度优先搜索
void BFSED(PGRAPHLIST graph, _Bool *visited, int v, char *val, int *count); //广度优先搜索连通图
int fristadjvex(PGRAPHLIST graph, int v);                                   //找v的第一个邻接点
int nextadjvex(PGRAPHLIST graph, int v, int w);                             //找v相对于w的下一个邻接点
PMAINTREE MainTree_Prim(PGRAPHLIST graph, int v);                           //最小生成树普利姆算法
PKRUSKAL MainTree_Kruskal(PGRAPHLIST graph);                                //最小生成树克鲁斯卡尔算法
void Sort_Power(PGRAPHLIST graph, PKRUSKAL list);                           //权值排序
PQUEUE init_Queue();                                                        //初始化一个队列
_Bool EnQueue(PQUEUE q, int val);                                           //进队
int DeQueue(PQUEUE q);                                                      //出队
void deface_Queue(PQUEUE q);                                                //销毁队列
int main(void)
{
    PGRAPHLIST agraph = init_GraphList();
    char *val = BFS(agraph);
    PKRUSKAL p = MainTree_Kruskal(agraph);
    free(val);
    return 0;
}
//初始化一个图，存储结构为邻接表，初始化失败返回空指针
PGRAPHLIST init_GraphList()
{
    PGRAPHLIST graph;
    if (!(graph = (PGRAPHLIST)malloc(sizeof(GRAPHLIST))))
    {
        return graph;
    }
    //输入点数，输入边数
    printf("input spot number:");
    scanf("%d", &graph->vexsnum);
    printf("input arcs number:");
    scanf("%d", &graph->arcsnum);
    //清空缓冲区
    while (getchar() != '\n')
    {
        continue;
    }
    //输入点数
    for (int i = 0; i < graph->vexsnum; i++)
    {
        printf("no%d:", i);
        scanf("%c", &(graph->vexs[i].data));
        graph->vexs[i].firstarc = NULL;
        //清空缓冲区
        while (getchar() != '\n')
        {
            continue;
        }
    }
    //输入边
    for (int i = 0; i < graph->arcsnum; i++)
    {
        int head, tail, power; //弧头，弧尾，权
        PSIZELIST *where;      //指向插入位置
        printf("input no%d arc:", i);
        if (scanf("%d %d %d", &tail, &head, &power) != 3)
        {
            printf("输入错误！");
        }
        where = &(graph->vexs[tail].firstarc);
        //使where指向空的地址
        while (*where != NULL)
        {
            where = &((*where)->nextarc);
        }
        if (!(*where = (PSIZELIST)malloc(sizeof(SIZELIST))))
        {
            return NULL;
        }
        (*where)->info = power;
        (*where)->adjvex = head;
        (*where)->nextarc = NULL;
        //清空缓冲区
        while (getchar() != '\n')
        {
            continue;
        }
    }
    return graph;
}
//找v的第一个邻接点
int fristadjvex(PGRAPHLIST graph, int v)
{
    if (graph->vexs[v].firstarc == NULL)
    {
        return -1;
    }
    v = graph->vexs[v].firstarc->adjvex;
    return v;
}
//找v相对于w的下一个邻接点
int nextadjvex(PGRAPHLIST graph, int v, int w)
{
    PSIZELIST where = graph->vexs[v].firstarc;
    while (where->adjvex != w)
    {
        where = where->nextarc;
    }
    if (where->nextarc == NULL)
    {
        return -1;
    }
    return where->nextarc->adjvex;
}
/*-------------------------深度优先搜索--------------------------------*/
//深度优先搜索
char *DFS(PGRAPHLIST graph)
{
    _Bool visited[graph->vexsnum];
    char *val;
    if (!(val = (char *)malloc(graph->vexsnum + 1)))
    {
        return val;
    }
    int count = 0;
    int allcount = 0;
    //数组初始化
    while (count < graph->vexsnum)
    {
        visited[count++] = 0;
    }
    count = 0;
    while (count < graph->vexsnum)
    {
        if (!visited[count])
        {
            DFSED(graph, count, visited, val, &allcount);
        }
        count++;
    }
    return val;
}
//深度遍历连通图
void DFSED(PGRAPHLIST graph, int v, _Bool *visited, char *val, int *count)
{
    val[(*count)++] = (graph->vexs[v].data);
    visited[v] = 1;
    for (int w = fristadjvex(graph, v); w != -1; w = nextadjvex(graph, v, w))
    {
        if (!visited[w])
        {
            DFSED(graph, w, visited, val, count);
        }
    }
}
/*----------------------广度优先搜索------------------------------*/
//广度优先搜索
char *BFS(PGRAPHLIST graph)
{
    _Bool mark[graph->vexsnum];
    int count = 0;
    char *val;
    int all = 0;
    if (!(val = (char *)malloc(graph->vexsnum)))
    {
        printf("Room is not enough!");
        return val;
    }
    //初始化赋0
    while (count < graph->vexsnum)
    {
        mark[count++] = 0;
    }
    count = 0;
    while (count < graph->vexsnum)
    {
        if (!mark[count])
        {
            BFSED(graph, mark, count, val, &all);
        }
        count++;
    }
    return val;
}
//广度优先搜索连通图
void BFSED(PGRAPHLIST graph, _Bool *visited, int v, char *val, int *count)
{
    int where;
    PQUEUE que = init_Queue();
    if (!visited[v])
    {
        EnQueue(que, v);
        val[(*count)++] = graph->vexs[where].data;
        visited[v] = 1;
    }
    while (que->nodesnum)
    {
        where = DeQueue(que);
        for (int i = fristadjvex(graph, where); i != -1; i = nextadjvex(graph, where, i))
        {
            if (!(visited[i]))
            {
                val[(*count)++] = graph->vexs[i].data;
                visited[i] = 1;
                EnQueue(que, i);
            }
        }
    }
    deface_Queue(que);
}
/*------------------------------最小生成树----------------------------------*/
//最小生成树普利姆算法
PMAINTREE MainTree_Prim(PGRAPHLIST graph, int v)
{
    PMAINTREE MinTree = (PMAINTREE)malloc(sizeof(MAINTREE) * (graph->vexsnum));
    _Bool visited[graph->vexsnum]; //标记顶点是否在u中
    int count = 0;                 //循环计数
    //初始化MinTree,visited
    while (count < graph->vexsnum)
    {
        if (count == v)
        {
            visited[count] = 1;
            MinTree[count].power = 0;
            MinTree[count++].adjvex = v;
        }
        else
        {
            visited[count] = 0;
            MinTree[count].adjvex = v;
            MinTree[count++].power = MAXINT;
        }
    }
    PSIZELIST vlist = graph->vexs[v].firstarc;
    do
    {
        MinTree[vlist->adjvex].power = vlist->info;
        vlist = vlist->nextarc;
    } while (vlist);
    count = 1;
    //边数=n-1
    while (count != graph->vexsnum)
    {
        int sizenum = 0;        //循环计数
        int sizeno;             //最小边编号
        int shortside = MAXINT; //最小边权值，设为int最大值，方便查找第一个边
        PSIZELIST vpoint;       //新增点
        //挑选最短边
        while (sizenum < graph->vexsnum)
        {
            if ((!visited[sizenum]) && (shortside > visited[sizenum]))
            {
                shortside = visited[sizenum];
                sizeno = sizenum; //最小边赋值
            }
            sizenum++;
        }
        //将点并上集合U，并且更新各点最短路径
        visited[sizeno] = 1;
        vpoint = graph->vexs[sizeno].firstarc;
        do
        {
            if ((vpoint->info) < (MinTree[vpoint->adjvex].power))
            {
                MinTree[vpoint->adjvex].power = vpoint->info;
            }
            vpoint = vpoint->nextarc;
        } while (vpoint);
        count++;
    }
    return MinTree;
}
//最小生成树克鲁斯卡尔算法
PKRUSKAL MainTree_Kruskal(PGRAPHLIST graph)
{
    PKRUSKAL list = (PKRUSKAL)malloc(sizeof(KRUSKAL) * (graph->arcsnum));//
    PKRUSKAL MainTree=(PKRUSKAL)malloc(sizeof(KRUSKAL)*(graph->vexsnum-1));//
    int count=0;//
    int vpart[graph->vexsnum];//判断是否连通
    //按权值排序边，依次输入MainTree数组中
    Sort_Power(graph, list);
    //初始化vpart数组
    for (int i = 0; i < graph->vexsnum; i++)
    {
        vpart[i] = i;
    }
    //依次查看权值数组
    for (int i = 0; i < graph->arcsnum; i++)
    {
        int v1,v2,vs1,vs2;
        v1=list[i].head;
        v2=list[i].tail;
        vs1=vpart[v1];
        vs2=vpart[v2];
        if (vs1!=vs2)
        {
            MainTree[count].head=list[i].head;
            MainTree[count].tail=list[i].tail;
            MainTree[count++].power=list[i].power;
            for (int a = 0; a < graph->vexsnum; a++)
            {
                if (vpart[a]==vs2)
                {
                    vpart[a]=vs1;
                }   
            }   
        }
    }
    free(list);
    return MainTree;
}
//权值排序
void Sort_Power(PGRAPHLIST graph, PKRUSKAL list)
{
    KRUSKAL minPower;//排序使用的
    int num;
    int count=0;
    //将图中权值与顶点赋值进入数组
    for (int i = 0; i < graph->vexsnum; i++)
    {
        PSIZELIST where = graph->vexs[i].firstarc;
        while (where)
        {
            list[count].head = where->adjvex;
            list[count].tail = i;
            list[count++].power = where->info;
            where = where->nextarc;
        }
    }
    //选择排序
    for (int i = 0; i < (graph->arcsnum-1); i++)
    {
        minPower.power=MAXINT;
        for (int a = i; a < graph->arcsnum; a++)
        {
            if (minPower.power>list[a].power)
            {
                minPower.power=list[a].power;
                minPower.head=list[a].head;
                minPower.tail=list[a].tail;
                num=a;//记录最小权值位置
            }
        }
        //进行交换
        list[num].head=list[i].head;
        list[num].tail=list[i].tail;
        list[num].power=list[i].power;
        list[i].head=minPower.head;
        list[i].tail=minPower.tail;
        list[i].power=minPower.power;
    }
}
/*--------------------------------队列-------------------------------------*/
//初始化一个队列
PQUEUE init_Queue()
{
    PQUEUE que;
    PNODE noe;
    if (que = (PQUEUE)malloc(sizeof(QUEUE)))
    {
        que->nodesnum = 0;
        if (!(noe = (PNODE)malloc(sizeof(NODE))))
        {
            return NULL;
        }
        noe->next = NULL;
        que->head = noe;
        que->tail = noe;
    }
    return que;
}
//进队
_Bool EnQueue(PQUEUE q, int val)
{
    if (!(q->tail->next = (PNODE)malloc(sizeof(NODE))))
    {
        return 0;
    }
    q->tail = q->tail->next;
    q->tail->data = val;
    q->tail->next = NULL;
    (q->nodesnum)++;
    return 1;
}
//出队
int DeQueue(PQUEUE q)
{
    PNODE del;
    int val;
    if (q->nodesnum == 0)
    {
        return -1;
    }
    del = q->head->next;
    q->head->next = q->head->next->next;
    val = del->data;
    (q->nodesnum)--;
    free(del);
    if (q->nodesnum == 0)
    {
        q->tail = q->head;
    }
    return val;
}
//销毁队列
void deface_Queue(PQUEUE q)
{
    int count = q->nodesnum;
    PNODE del;
    while (count--)
    {
        del = q->head;
        q->head = q->head->next;
        free(del);
    }
    free(q->head);
    free(q);
}
