#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100    //最大尺寸
#define INF 2147483647 //无穷大

typedef struct inf //定义信息结构体
{
    int number;          //序号
    char name[40];       //地点名称
    char introduce[100]; //介绍
} inf;

typedef struct graph //定义图结构体
{
    inf *inf;                   //地点信息
    int arcs[MAXSIZE][MAXSIZE]; //邻接矩阵
    int vexnum;                 //顶点数
    int arcnum;                 //边数
} graph;

int creatGraph(graph *map) //创建图
{
    FILE *fp = NULL;
    fp = fopen("./map.txt", "r"); //相对路径下读取文件
    if (fp == NULL)
        return 0;

    map->inf = (inf *)malloc(100 * sizeof(inf));
    fscanf(fp, "%d %d", &map->vexnum, &map->arcnum); //读取顶点数&边数
    for (int i = 0; i < map->vexnum; i++)            //读取地点信息
        fscanf(fp, "%d %s %s", &map->inf[i].number, &map->inf[i].name, &map->inf[i].introduce);

    for (int i = 0; i < MAXSIZE; i++) //初始化邻接矩阵
        for (int j = 0; j < MAXSIZE; j++)
            map->arcs[i][j] = INF;
    int i, j, k;
    while (fscanf(fp, "%d %d %d", &i, &j, &k) != EOF) //读取矩阵信息
        map->arcs[i][j] = k;

    return 1;
}

void numberPath(graph *map, int num) //通过编号查询
{
    int flag = INF;
    if (num != 0)
    {
        for (int i = 0; i < map->vexnum; i++)
        {
            if (map->inf[i].number == num)
                flag = i;
        }
    }

    if (flag == INF)
    {
        printf("找不到该景点");
        getchar();
        return;
    }

    //打印景点信息
    printf("景点编号:%d\n", map->inf[flag].number);
    printf("景点名称:%s\n", map->inf[flag].name);
    printf("景点介绍:%s\n\n", map->inf[flag].introduce);
    printf("该景点路径信息：\n");
    for (int j = 0; j < map->arcnum; j++) //遍历寻找相邻节点
        if (map->arcs[flag + 1][j] != INF)
            printf("到景点%d--%s的距离为%d\n", map->inf[j - 1].number, map->inf[j - 1].name, map->arcs[flag + 1][j]);
    getchar();
}

void namePath(graph *map, char name[40]) //通过名字查询
{
    int flag = INF;
    for (int i = 0; i < map->vexnum; i++)
    {
        if (strcmp(map->inf[i].name, name) == 0)
            flag = i;
    }

    if (flag == INF)
    {
        printf("找不到该景点");
        getchar();
        return;
    }

    //打印景点信息
    printf("景点编号:%d\n", map->inf[flag].number);
    printf("景点名称:%s\n", map->inf[flag].name);
    printf("景点介绍:%s\n\n", map->inf[flag].introduce);
    printf("该景点路径信息：\n");
    for (int j = 0; j < map->arcnum; j++) //遍历寻找相邻节点
        if (map->arcs[flag + 1][j] != INF)
            printf("到景点%d--%s的距离为%d\n", map->inf[j - 1].number, map->inf[j - 1].name, map->arcs[flag + 1][j]);
    getchar();
}

void printfAll(graph *map) //列出所有景点和道路信息
{
    printf("景点编号 景点名称\t景点介绍\n"); //循环打印景点
    for (int i = 0; i < map->vexnum; i++)
        printf("%d \t%s\t%s\n", map->inf[i].number, map->inf[i].name, map->inf[i].introduce);
    printf("道路信息：\n"); //循环打印道路信息
    for (int i = 0; i < map->vexnum; i++)
    {
        for (int j = 0; j < map->arcnum; j++)
            if (map->arcs[i][j] != INF)
                printf("%d--%s 和 %d--%s 存在道路 距离为%d\n", map->inf[i - 1].number, map->inf[i - 1].name, map->inf[j - 1].number, map->inf[j - 1].name, map->arcs[i][j]);
    }
}

void spotMean(graph *map) //景点信息查询
{
    int num, input;
    char name[40];
    //system("cls");
    printf("1：按照景点编号查询\n");
    printf("2：按照景点名称查询\n");
    printf("3：列出所有景点和道路信息\n");
    printf("4：返回上一级\n");
    printf("请输入您的操作(1-4):");
    scanf("%d", &num);
    switch (num)
    {
    case 1:
        printf("请输入景点编号: ");
        scanf("%d", &input);
        numberPath(map, input);
        break;
    case 2:
        printf("请输入景点名称: ");
        scanf("%s", &name);
        namePath(map, name);
        break;
    case 3:
        printfAll(map);
        break;
    case 4:
        return;
    default:
        printf("输入有误，重新输入");
        break;
    }
}

void addPoint(graph *map) //添加景点信息
{
    int num;
    printf("请输入待新增景点信息：\n");
    printf("景点编号:");
    scanf("%d", &num);
    for (int i = 0; i < map->vexnum; i++) //遍历查询是否存在
    {
        if (map->inf[i].number == num)
        {
            printf("该编号已存在\n");
            return;
        }
    }
    map->inf[map->vexnum].number = num;
    printf("景点名称:");
    scanf("%s", map->inf[map->vexnum].name);
    printf("景点介绍:");
    scanf("%s", map->inf[map->vexnum].introduce);
    map->vexnum++;
    printf("添加成功\n");
    getchar();
}

void delPoint(graph *map) //删除景点信息
{
    int num, flag = INF;
    printf("请输入景点编号:");
    scanf("%d", &num);
    for (int i = 0; i < map->vexnum; i++) //// 寻找景点位置
        if (map->inf[i].number == num)
            flag = i;

    if (flag == INF)
    {
        printf("未找到景点！\n");
        getchar();
        return;
    }

    // 清空点的矩阵信息
    for (int i = 0; i < map->vexnum; i++)
    {
        if (map->arcs[flag][i] != INF)
        {
            map->arcs[flag][i] = INF;
            map->arcs[i][flag] = INF;
            map->arcnum--;
        }
    }

    // 重建矩阵
    // 右移矩阵
    for (int i = flag; i < map->vexnum - 1; i++)
        for (int j = flag; j < map->vexnum - 1; j++)
            map->arcs[i][j] = map->arcs[i][j + 1];
    // 上移矩阵
    for (int i = flag; i < map->vexnum - 1; i++)
        for (int j = flag; j < map->vexnum - 1; j++)
            map->arcs[i][j] = map->arcs[i + 1][j];

    // 重建信息
    for (int i = flag; i < map->vexnum - 1; i++)
    {
        map->inf[i] = map->inf[i + 1];
    }

    map->vexnum--;
    printf("删除景点完成\n");
    getchar();
}

void changePoint(graph *map)
{
    int number;
    char name[50];
    char introduce[200];
    printf("请输入景点编号:");
    scanf("%d", &number);
    for (int i = 0; i < map->vexnum; i++)
    {
        if (number == map->inf[i].number)
        {
            printf("请输入该景点修改后的名称和介绍\n");
            printf("名称：");
            scanf("%s", &name);
            printf("介绍：");
            scanf("%s", &introduce);
            strcpy(map->inf[i].name, name);
            strcpy(map->inf[i].introduce, introduce);
            printf("修改成功");
            getchar();
        }
    }
}

// 定义全局变量
int visited[MAXSIZE];
int road[MAXSIZE];
int pathnum = 0;

void getPath(graph *map, int i, int j, int k)
{
    int temp;
    if (visited[k] == j)
    {
        pathnum++; //路径数值++
        printf("第%d条路径：", pathnum);
        for (temp = 1; temp < k; temp++)
            printf("%s->", map->inf[visited[temp]].name);
        printf("%s\n", map->inf[visited[temp]].name);
    }
    temp = 1;
    while (temp <= map->vexnum)
    {
        if (temp != i)
        {
            if (map->arcs[visited[k]][temp] != INF && road[temp] == 0)
            {
                road[temp] = 1;
                visited[k + 1] = temp;
                getPath(map, i, j, k + 1); //递归调用
                road[temp] = 0;
            }
        }
        temp++;
    }
}

void listPath(graph *map, int i, int j)
{
    int k = 1;
    visited[1] = i;
    road[i] = 0; //初始化标志
    pathnum = 0; //初始化路径数量
    getPath(map, i, j, k);
}

void pathPoint(graph *map) //两个景点的路径查询
{
    int star, end, tstar = -1, tend = -1;
    printf("请输入起点编号：");
    scanf("%d", &star);
    printf("请输入终点编号：");
    scanf("%d", &end);
    for (int i = 0; i < map->vexnum; i++) //遍历寻找节点
    {
        if (map->inf[i].number == star) //找到起点位置
            tstar = i;
        if (map->inf[i].number == end) //找到终点位置
            tend = i;
    }
    if (tstar == -1) //判断起点是否存在
    {
        printf("起点不存在!\n");
        return;
    }
    if (tend == -1) //判断终点是否存在
    {
        printf("终点不存在!\n");
        return;
    }
    printf("从%s到%s的所有游览路径有:\n", map->inf[tstar].name, map->inf[tend].name);
    listPath(map, tstar, tend);
}

void dijkstra(graph *map, int sp) //迪杰斯特拉算法
{
    int i, j, k = 0;
    int min;
    int tmp;
    int flag[MAXSIZE]; //flag[i]=1表示"顶点sp"到"顶点i"的最短路径已成功获取。
    int prev[MAXSIZE] = {0};
    int dist[MAXSIZE] = {0};

    for (i = 0; i < map->vexnum; i++) //初始化
    {
        flag[i] = 0;                //顶点i的最短路径还没获取到。
        prev[i] = 0;                //顶点i的前驱顶点为0。
        dist[i] = map->arcs[sp][i]; //顶点i的最短路径为"顶点sp"到"顶点i"的权。
    }

    flag[sp] = 1; //对"顶点sp"自身进行初始化
    dist[sp] = 0;

    for (i = 1; i < map->vexnum; i++) //遍历每次找出一个顶点的最短路径。
    {
        //寻找当前最小的路径；
        //即，在未获取最短路径的顶点中，找到离sp最近的顶点(k)。
        min = INF;
        for (j = 0; j < map->vexnum; j++)
        {
            if (flag[j] == 0 && dist[j] < min)
            {
                min = dist[j];
                k = j;
            }
        }
        //标记"顶点k"为已经获取到最短路径
        flag[k] = 1;

        //修正当前最短路径和前驱顶点
        //即，当已经"顶点k的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"。
        for (j = 0; j < map->vexnum; j++)
        {
            tmp = (map->arcs[k][j] == INF ? INF : (min + map->arcs[k][j])); //防止溢出
            if (flag[j] == 0 && (tmp < dist[j]))
            {
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }

    for (i = 0; i < map->vexnum; i++) //打印dijkstra最短路径的结果
        if (i != sp)
        {
            printf("%s->%s\n", map->inf[sp].name, map->inf[i].name);
            printf("路径:%d\n", dist[i]);
        }
}

void shortPath(graph *map) //景点最短路径
{
    int num, flag = -1;
    printf("请输入起始景点编号：\n");
    scanf("%d", &num);
    for (int i = 0; i < map->vexnum; i++) // 遍历寻找景点位置
        if (num == map->inf[i].number)
            flag = i;
    if (flag == -1)
    {
        printf("未找到景点\n");
        getchar();
        return;
    }
    printf("%s到其他各景点的最短距离如下：\n", map->inf[flag].name);
    printf("\n");
    dijkstra(map, flag);
}

void printfDijkstra(graph *map, int tstar, int tend)
{
    int i, j, k;
    int min;
    int tmp;
    int flag[MAXSIZE]; //flag[i]=1表示"顶点tstar"到"顶点i"的最短路径已成功获取。
    int prev[MAXSIZE] = {0};
    int dist[MAXSIZE] = {0};

    for (i = 0; i < map->vexnum; i++)
    {                                  //初始化
        flag[i] = 0;                   //顶点i的最短路径还没获取到。
        prev[i] = 0;                   //顶点i的前驱顶点为0。
        dist[i] = map->arcs[tstar][i]; //顶点i的最短路径为"顶点tstar"到"顶点i"的权。
    }

    //对"顶点tstar"自身进行初始化
    flag[tstar] = 1;
    dist[tstar] = 0;

    //遍历G.vexnum-1次；每次找出一个顶点的最短路径。
    for (i = 1; i < map->vexnum; i++)
    {
        //寻找当前最小的路径；
        //即，在未获取最短路径的顶点中，找到离tstar最近的顶点(k)。
        min = INF;
        for (j = 0; j < map->vexnum; j++)
        {
            if (flag[j] == 0 && dist[j] < min)
            {
                min = dist[j];
                k = j;
            }
        }
        //标记"顶点k"为已经获取到最短路径
        flag[k] = 1;

        //修正当前最短路径和前驱顶点
        //即，当已经"顶点k的最短路径"之后，更新"未获取最短路径的顶点的最短路径和前驱顶点"。
        for (j = 0; j < map->vexnum; j++)
        {
            tmp = (map->arcs[k][j] == INF ? INF : (min + map->arcs[k][j])); // 防止溢出
            if (flag[j] == 0 && (tmp < dist[j]))
            {
                dist[j] = tmp;
                prev[j] = k;
            }
        }
    }
}
void pointPath(graph *map) //两点最短路径
{
    int star, end, tstar = 0, tend = 0;
    printf("请输入起点编号：\n");
    scanf("%d", &star);
    printf("请输入终点编号：\n");
    scanf("%d", &end);

    for (int i = 0; i < map->vexnum; i++) //遍历寻找两点
    {
        if (map->inf[i].number == star)
            tstar = i;
        if (map->inf[i].number == end)
            tend = i;
    }
    if (tstar == 0)
    {
        printf("未找到起点\n");
        getchar();
        return;
    }
    if (tend == 0)
    {
        printf("未找到终点\n");
        getchar();
        return;
    }
    printfDijkstra(map, tstar, tend);
}

void mainMean() //主菜单
{
    printf("\n");
    printf("\t欢迎使用厦门理工学院导游咨询系统\n");
    printf("*******************************************\n");
    printf("\t1.景点信息查询\n");
    printf("\t2.新增景点信息\n");
    printf("\t3.修改景点和道路信息\n");
    printf("\t4.删除景点和道路信息\n");
    printf("\t5.任意两个景点的路径查询\n");
    printf("\t6.求一个景点到所有景点的最短路径\n");
    printf("\t7.求任意的两个景点之间的最短路径\n");
    printf("\t8.退出系统\n");
    printf("*******************************************\n");
}

int main()
{
    graph map;
    int input;
    creatGraph(&map); //初始化图
    while (1)
    {
        //system("cls");
        mainMean();
        printf("请选择功能：");
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            spotMean(&map);
            break;
        case 2:
            addPoint(&map);
            break;
        case 3:
            changePoint(&map);
            break;
        case 4:
            delPoint(&map);
            break;
        case 5:
            pathPoint(&map);
            break;
        case 6:
            shortPath(&map);
            break;
        case 7:
            pointPath(&map);
            break;
        case 8:
            return 0;
            break;
        default:
            printf("输入有误，请重新输入\n");
            break;
        }
    }
    return 0;
}