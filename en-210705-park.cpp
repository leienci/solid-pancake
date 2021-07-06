#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define MAX 2   //停车场位置数
#define PRICE 5 //每小时停车费

typedef struct car //车辆数据
{
    int number; //车牌号
    int time;   //停车时间
} car;

typedef struct stack //定双向义栈
{
    car dates[MAX * 2];
    int top;
    int down;
} stack;

typedef struct queue //定义队列
{
    car data[MAX];
    int front;
    int rear;
} queue;

void initStack(struct stack *park) //初始化双向栈
{
    park->top = -1;
    park->down = MAX * 2;
}

int isEmptytop(struct stack *park) //判断底栈空
{
    return (park->top == -1) ? 1 : 0;
}

int isEmptydown(struct stack *park) //判断顶栈空
{
    return (park->down == MAX * 2) ? 1 : 0;
}

int isFulltop(struct stack *park) //判断底栈满
{
    return (park->top == MAX - 1) ? 1 : 0;
}

int isFulldown(struct stack *park) //判断顶栈满
{
    return (park->down == MAX) ? 1 : 0;
}

int pushtop(struct stack *park, int number, int time) //入栈操作(底栈)
{
    if (isFulltop(park)) //先判断栈是否满
        return 0;
    park->dates[++park->top].number = number;
    park->dates[park->top].time = time;
    return 1;
}

int pushdown(struct stack *park, int number, int time) //入栈操作(顶栈)
{
    if (isFulldown(park)) //先判断栈是否满
        return 0;
    park->dates[--park->down].number = number;
    park->dates[park->down].time = time;
    return 1;
}

int poptop(struct stack *park, int *number, int *time) //出栈操作(底栈)
{
    if (isEmptytop(park)) //先判断栈是否为空
        return 0;
    *number = park->dates[park->top].number;
    *time = park->dates[park->top].time;
    park->dates[park->top--];
    return 1;
}

int popdown(struct stack *park, int *number, int *time) //出栈操作(顶栈)
{
    if (isEmptydown(park)) //先判断栈是否为空
        return 0;
    *number = park->dates[park->down].number;
    *time = park->dates[park->down].time;
    park->dates[park->down++];
    return 1;
}

void printPark(struct stack *park) //输出栈的内容
{
    if (isEmptytop(park)) //先判断栈是否为空
    {
        printf("当前停车场为空！\n");
        return;
    }
    for (int i = park->top; i > -1; i--)
        printf("[%d]:车牌号%d:时间%d ", i, park->dates[i].number, park->dates[i].time);
    printf("\n");
}

queue *initQueue() //初始化队列
{
    queue *path = (queue *)malloc(sizeof(queue));
    path->front = path->rear = 0;
    return path;
}

int queueFull(struct queue *path) //判断队列是否满
{
    if ((path->rear + 1) % (MAX + 1) == path->front)
        return 1;
    else
        return 0;
}

int queueEmpty(struct queue *path) //判断队列是否空
{
    if (path->front == path->rear)
        return 1;
    else
        return 0;
}

int enQueue(struct queue *path, int data, int time) //入队操作
{
    if (queueFull(path))
        return 0;
    else
    {
        path->data[path->rear].number = data;
        path->data[path->rear].time = time;
        path->rear = (path->rear + 1) % (MAX + 1);
        return 1;
    }
}

int deQueue(struct queue *path, int *data, int *time) //出队操作
{
    if (queueEmpty(path))
        return 1;
    else
    {
        *data = path->data[path->front].number;
        *time = path->data[path->front].time;
        path->front = (path->front + 1) % (MAX + 1);
        return 0;
    }
}

void printQueue(struct queue *path) //打印队列
{
    //要知道当前队列有多少个元素
    int length = (path->rear - path->front + (MAX + 1)) % (MAX + 1);
    int index = path->front;
    for (int i = 0; i < length; i++)
    {
        printf("车牌号:[%d] -> ", path->data[index]);
        index = (index + 1) % (MAX + 1);
    }
    printf("NULL\n");
}

int isCar(stack *park, queue *path, int num) //判断车辆是否在内
{
    for (int i = park->top; i > -1; i--)
        if (park->dates[i].number == num)
            return 1;

    int length = (path->rear - path->front + (MAX + 1)) % (MAX + 1);
    int index = path->front;

    for (int i = 0; i < length; i++)
    {
        if (path->data[index].number == num)
            return 2;
        index = (index + 1) % (MAX + 1);
    }

    return 0;
}

void inPark(stack *park, queue *path, car vehicle) //车辆进场
{
    int num, intime;
    printf("车牌号：");
    scanf("%d", &num);
    printf("入场时间：");
    scanf("%d", &intime);
    if (isCar(park, path, num) == 0)
    {
        if (pushtop(park, num, intime))
        {
            printf("当前车辆停在[%d]号车位:", park->top + 1);
            printf("入场成功\n");
        }
        else
        {
            if (enQueue(path, num, intime))
            {
                printf("停车场当前已满，进入过道等候\n");
                printf("当前车辆停在过道:等待入场\n", path->rear);
            }
            else
                printf("过道已满，停车失败");
        }
    }
    else
    {
        printf("车辆已在场内!\n");
    }
}

void outPark(stack *park, queue *path, int *number, car vehicle, int *data, int *time) //车辆出场
{
    int num, outtime;
    printf("车牌号：");
    scanf("%d", &num);
    printf("出场时间：");
    scanf("%d", &outtime);
    if (isCar(park, path, num) == 1)
    {
        int flag = 1, tempnumber, temptime;
        while (park->top != -1 && flag == 1) //遍历底栈
        {
            if (park->dates[park->top].number == num)
            {
                flag = 0;
                poptop(park, number, time);
                break;
            }
            poptop(park, number, time); //将车辆先转移至顶栈
            tempnumber = *number;
            temptime = *time;
            pushdown(park, tempnumber, temptime);
        }

        printf("车牌号[%d]已成功出场，收费为%d元\n", *number, PRICE * (outtime - *time));

        while (park->down != MAX * 2) //遍历顶栈
        {
            popdown(park, number, time);
            tempnumber = *number;
            temptime = *time;
            pushtop(park, tempnumber, temptime); //车辆重新返回停车场
        }

        if (queueEmpty != 0) //队列不为空
        {
            deQueue(path, data, time); //便道的车辆入场
            tempnumber = *number;
            temptime = outtime; //修改车辆的入场时间
            pushtop(park, tempnumber, temptime);
        }
    }
    else if (isCar(park, path, num) == 2)
        printf("车辆在便道上\n");
    else
        printf("未找到车辆！\n");
}

void mainMeun(stack *park) //主菜单
{
    printf("\n\n                  ** 停车场管理程序 **\n");
    printf("=========================================================\n");
    printf("**                                                     **\n");
    printf("**       A --- 汽车进车场       D --- 汽车出车场       **\n");
    printf("**                                                     **\n");
    printf("**       P --- 显示车辆信息     E --- 退出程序         **\n");
    printf("**                                                     **\n");
    printf("**          停车场剩余%d车位，每小时收费%d元             **\n", MAX - park->top - 1, PRICE);
    printf("=========================================================\n");
    printf(" 请选择 :(A,D,P,E): \n");
}

int main()
{
    struct stack park;
    struct car vehicle;

    char input;
    int chip;

    initStack(&park);          //初始化栈
    queue *path = initQueue(); //初始化队列

    while (1)
    {
        mainMeun(&park); //显示主菜单
        scanf("%s", &input);
        switch (input)
        {
        case 'A':
        case 'a':
            inPark(&park, path, vehicle); //车辆进场
            break;
        case 'D':
        case 'd':
            outPark(&park, path, &chip, vehicle, &chip, &chip); //车辆出场
            break;
        case 'P':
        case 'p':
            printPark(&park); //显示车辆信息
            printQueue(path);
        case 'E':
        case 'e':
            return 0;
        default:
            printf("输入错误，请重新输入\n");
            break;
        }
    }
    return 0;
}