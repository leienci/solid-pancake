#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LIST_INIT_SIZE 50 //线性表存储空间的初始分配量
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define N 5 //课程数量

typedef struct bir //生日结构体
{
    int year;
    int month;
    int day;
} birthday;

typedef struct stu //学生信息结构体
{
    char stuno[10];
    char name[10];
    char sex[2];
    birthday date;
    char tel[12];
    char adds[50];
    int score[N];
} student;

typedef struct //学生成绩排序结构体
{
    int point; //保存学生序号
    int score;
} s_score;

typedef struct /*定义顺序表结构体*/
{
    student *List; //线性表首地址
    int length;    //当前的长度
    int listsize;  //当前分配的存储容量，以elemType为单位
} StudentList;

void InitList(StudentList *L) //初始化一个空的线性表
{
    L->List = (student *)malloc(LIST_INIT_SIZE * sizeof(student));
    if (!L->List)
        exit(OVERFLOW);           //overflow
    L->length = 0;                //初始表为空表
    L->listsize = LIST_INIT_SIZE; //初始表的存储容量，为LIST_INIT_SIZE个elemType单位
    return;
}

void Insert(StudentList *L, student e) //顺序表增加操作
{

    if (L->length >= L->listsize) //空间不足
        return;
    L->List[L->length] = e;
    L->length++; //表长度+1
    return;
}

void Menu1() //学生基本信息管理菜单
{
    printf("\n");
    printf("******************学生基本信息管理******************\n");
    printf("\n");
    printf("               1.添加学生信息\n");
    printf("               2.浏览学生信息\n");
    printf("               3.查询学生信息\n");
    printf("               4.修改学生信息\n");
    printf("               5.删除学生信息\n");
    printf("               6.退出\n");
    printf("\n");
    printf("****************************************************\n");
    printf("\n");
}

void Menu2() //查询学生信息基本菜单
{
    printf("\n");
    printf("******************查询学生信息******************\n");
    printf("\n");
    printf("               1.通过姓名查询学生信息\n");
    printf("               2.通过学号查询学生信息\n");
    printf("               3.退出\n");
    printf("\n");
    printf("************************************************\n");
    printf("\n");
}

void Menu3() //学生成绩管理菜单
{
    printf("\n");
    printf("******************学生成绩管理******************\n");
    printf("\n");
    printf("               1.添加成绩信息\n");
    printf("               2.浏览成绩信息\n");
    printf("               3.查询成绩信息\n");
    printf("               4.修改成绩信息\n");
    printf("               5.排序成绩信息\n");
    printf("               6.退出\n");
    printf("\n");
    printf("************************************************\n");
    printf("\n");
}

void SortScore(StudentList *L) //学生成绩排序
{
    int n, m;
    printf("******************学生成绩排序******************\n");
    printf("请输入排序的课程：");
    scanf("%d", &n);
    printf("1.升序排序 2.降序排序\n");
    scanf("%d", &m);

    student temp;
    for (int i = 0; i < L->length; i++) //开始冒泡排序
    {
        //遍历数组找出最大
        for (int j = 0; j < L->length - i - 1; j++)
        {
            switch (m)
            {
            case 1:                                                        //升序
                if (L->List[j].score[n - 1] > L->List[j + 1].score[n - 1]) //两两比较
                {
                    //两两交换
                    temp = L->List[j];
                    L->List[j] = L->List[j + 1];
                    L->List[j + 1] = temp;
                }
                break;
            default:                                                       //降序
                if (L->List[j].score[n - 1] < L->List[j + 1].score[n - 1]) //两两比较
                {
                    //两两交换
                    temp = L->List[j];
                    L->List[j] = L->List[j + 1];
                    L->List[j + 1] = temp;
                }
                break;
            }
        }
    }
    printf("学号    姓名    科目1   科目2   科目3   科目4   科目5\n");
    for (int i = 0; i < L->length; i++)
        printf("%s    %s    %d    %d    %d    %d    %d\n", L->List[i].stuno, L->List[i].name, L->List[i].score[0], L->List[i].score[1], L->List[i].score[2], L->List[i].score[3], L->List[i].score[4]);
    printf("******************学生成绩排序******************\n");
    system("pause");
}

void PrintScore(StudentList *L, int i) //修改成功回显
{
    printf("修改成功！\n");
    printf("当前成绩为：\n");
    printf("学号    姓名    科目1   科目2   科目3   科目4   科目5\n");
    printf("%s    %s    %d    %d    %d    %d    %d\n", L->List[i].stuno, L->List[i].name, L->List[i].score[0], L->List[i].score[1], L->List[i].score[2], L->List[i].score[3], L->List[i].score[4]);
}

void UpdateScore(StudentList *L) //学生成绩修改
{
    char num[10], tmp[50];
    int item, flag = 1, year, month, day;
    system("cls");
    printf("\n");
    printf("******************修改成绩信息******************\n");
    printf("请输入要修改学生的学号：");
    scanf("%s", &num);
    for (int i = 0; i < L->length; i++)
    {
        if (strcmp(L->List[i].adds, num) == 0)
        {
            flag = 0;
            printf("1.修改科目1\n");
            printf("2.修改科目2\n");
            printf("3.修改科目3\n");
            printf("4.修改科目4\n");
            printf("5.修改科目5\n");
            printf("6.重新查找\n");
            printf("7.退出\n");
            while (1)
            {
                printf("请选择功能（输入数值）：");
                scanf("%d", &item);
                switch (item)
                {
                case 1:
                    printf("请输入新成绩（科目1）:\n");
                    scanf("%d", &L->List[i].score[0]);
                    PrintScore(L, i);
                    break;
                case 2:
                    printf("请输入新成绩（科目2）:\n");
                    scanf("%d", &L->List[i].score[1]);
                    PrintScore(L, i);
                    break;
                case 3:
                    printf("请输入新成绩（科目3）:\n");
                    scanf("%d", &L->List[i].score[2]);
                    PrintScore(L, i);
                    break;
                case 4:
                    printf("请输入新成绩（科目4）:\n");
                    scanf("%d", &L->List[i].score[3]);
                    PrintScore(L, i);
                    break;
                case 5:
                    printf("请输入新成绩（科目5）:\n");
                    scanf("%d", &L->List[i].score[0]);
                    PrintScore(L, i);
                    break;
                case 6:
                    UpdateScore(L);
                case 7:
                    return;
                default:
                    printf("输入错误\n");
                    break;
                }
            }
            break;
        }
    }
    if (flag)
        printf("No Found\n");
    printf("******************************************\n");
    system("pause");
}

void SelectScore(StudentList *L) //学生成绩查询
{
    char tmp[10];
    int flag = 1;
    printf("******************查询成绩信息******************\n");
    printf("请输入学号：");
    scanf("%s", &tmp);
    for (int i = 0; i < L->length; i++)
    {
        if (strcmp(L->List[i].adds, tmp) == 0)
        {
            printf("学号    姓名    科目1   科目2   科目3   科目4   科目5\n");
            printf("%s    %s    %d    %d    %d    %d    %d\n", L->List[i].stuno, L->List[i].name, L->List[i].score[0], L->List[i].score[1], L->List[i].score[2], L->List[i].score[3], L->List[i].score[4]);
            flag = 0;
            break;
        }
    }
    if (flag)
        printf("No Found\n");
    printf("****************************************************\n");
    printf("\n");
    system("pause");
}

void PrintScore(StudentList *L) //学生成绩浏览
{
    system("cls"); //清屏
    printf("\n");
    printf("******************学生成绩浏览******************\n");
    printf("拥有%d位学生\n", L->length);
    printf("学号    姓名    科目1   科目2   科目3   科目4   科目5\n");
    for (int i = 0; i < L->length; i++)
        printf("%s    %s    %d    %d    %d    %d    %d\n", L->List[i].stuno, L->List[i].name, L->List[i].score[0], L->List[i].score[1], L->List[i].score[2], L->List[i].score[3], L->List[i].score[4]);
    printf("***********************************************\n");
    printf("\n");
    system("pause");
}

void AddScore(StudentList *L) //添加成绩信息
{
    char tmp[10];
    int flag = 1;
    printf("******************添加成绩信息******************\n");
    printf("请输入学号：");
    scanf("%s", &tmp);
    for (int i = 0; i < L->length; i++)
    {
        if (strcmp(L->List[i].adds, tmp) == 0)
        {
            printf("查找成功！\n请输入各科成绩（空格分隔）：\n");
            printf("科目1   科目2   科目3   科目4   科目5\n");
            scanf("%d %d %d %d %d", &L->List[i].score[0], &L->List[i].score[1], &L->List[i].score[2], &L->List[i].score[3], &L->List[i].score[4]);
            flag = 0;
            break;
        }
    }
    if (flag)
        printf("No Found\n");
    printf("****************************************************\n");
    printf("\n");
    system("pause");
}

void ScoreInfo(StudentList *L) //学生成绩管理
{
    int i;
    while (1)
    {
        system("cls"); //清屏
        Menu3();
        printf("请选择功能（输入数值）：");
        scanf("%d", &i);
        switch (i)
        {
        case 1:
            AddScore(L);
            break;
        case 2:
            PrintScore(L);
            break;
        case 3:
            SelectScore(L);
            break;
        case 4:
            UpdateScore(L);
            break;
        case 5:
            SortScore(L);
            break;
        case 6:
            return;
        default:
            printf("您输入有误，重新选择!\n");
            break;
        }
    }
}

void DeleteStudent(StudentList *L) //删除学生信息
{
    char num[10];
    int flag = 0, tmp;
    system("cls");
    printf("\n");
    printf("******************删除学生信息******************\n");
    printf("请输入要删除的学生的学号：");
    scanf("%s", &num);
    for (int i = 0; i < L->length; i++)
    {
        if (strcmp(L->List[i].adds, num) == 0)
        {
            printf("是否确定删除？\n1.确定 2.取消\n");
            scanf("%d", &tmp);
            switch (tmp)
            {
            case 1:
                flag = 1;
                for (int j = i; j < L->length - 1; j++) //要删除学生后面的学生往前移一位
                    L->List[j] = L->List[j + 1];
                break;
            default:
                break;
            }
        }
    }
    if (flag == 0) //查找失败
        printf("该学号不存在!!!\n");
    if (flag == 1)
    {
        printf("删除成功！！！\n"); //删除成功，学生人数减1
        (L->length)--;
    }
    printf("******************************************\n");
    system("pause");
}

void PrintUpdate(StudentList *L, int i) //输出修改
{
    printf("修改成功！\n");
    printf("当前信息为：\n");
    printf("学号    姓名    性别    生日    电话    地址\n");
    printf("%s    %s    %s    %d-%d-%d    %s    %s\n", L->List[i].stuno, L->List[i].name, L->List[i].sex, L->List[i].date.year, L->List[i].date.month, L->List[i].date.day, L->List[i].tel, L->List[i].adds);
}

void UpdateStudent(StudentList *L) //修改学生信息
{
    char num[10], tmp[50];
    int item, flag = 1, year, month, day;
    system("cls");
    printf("******************修改学生信息******************\n");
    printf("请输入要修改学生的学号：");
    scanf("%s", &num);
    for (int i = 0; i < L->length; i++)
    {
        if (strcmp(L->List[i].adds, num) == 0)
        {
            printf("1.修改姓名\n");
            printf("2.修改性别\n");
            printf("3.修改生日\n");
            printf("4.修改电话\n");
            printf("5.修改地址\n");
            printf("6.重新查找\n");
            printf("7.退出\n");
            while (1)
            {
                printf("请选择功能（输入数值）：");
                scanf("%d", &item);
                switch (item)
                {
                case 1:
                    printf("请输入新姓名:\n");
                    scanf("%s", tmp);
                    strcpy(L->List[i].name, tmp);
                    PrintUpdate(L, i);
                    break;
                case 2:
                    printf("请输入新性别:\n");
                    scanf("%s", tmp);
                    strcpy(L->List[i].sex, tmp);
                    PrintUpdate(L, i);
                    break;
                case 3:
                    printf("请输入新生日:\n");
                    scanf("%d-%d-%d", &year, &month, &day);
                    L->List[i].date.year = year;
                    L->List[i].date.month = month;
                    L->List[i].date.day = day;
                    PrintUpdate(L, i);
                    break;
                case 4:
                    printf("请输入新电话:\n");
                    scanf("%s", tmp);
                    strcpy(L->List[i].tel, tmp);
                    PrintUpdate(L, i);
                    break;
                case 5:
                    printf("请输入新地址:\n");
                    scanf("%s", tmp);
                    strcpy(L->List[i].adds, tmp);
                    PrintUpdate(L, i);
                    break;
                case 6:
                    UpdateStudent(L);
                case 7:
                    return;
                default:
                    printf("输入错误\n");
                    break;
                }
            }
            break;
        }
    }
    if (flag)
        printf("查询失败（请核对后重新输入）\n");
    printf("******************************************\n");
    system("pause");
}

void SelectName(StudentList *L) //通过姓名查询
{
    char tmp[10];
    int flag = 1;
    printf("******************查询学生信息******************\n");
    printf("请输入姓名：");
    scanf("%s", &tmp);
    for (int i = 0; i < L->length; i++)
    {
        if (strcmp(L->List[i].name, tmp) == 0)
        {
            printf("学号    姓名    性别    生日    电话    地址\n");
            printf("%s    %s    %s    %d-%d-%d    %s    %s\n", L->List[i].stuno, L->List[i].name, L->List[i].sex, L->List[i].date.year, L->List[i].date.month, L->List[i].date.day, L->List[i].tel, L->List[i].adds);
            flag = 0;
            break;
        }
    }
    if (flag)
        printf("No Found\n");
    printf("****************************************************\n");
    printf("\n");
    system("pause");
}

void SelectNumber(StudentList *L) //通过学号查询
{
    char tmp[10];
    int flag = 1;
    printf("******************查询学生信息******************\n");
    printf("请输入学号：");
    scanf("%s", &tmp);
    for (int i = 0; i < L->length; i++)
    {
        if (strcmp(L->List[i].adds, tmp) == 0)
        {
            printf("学号    姓名    性别    生日    电话    地址\n");
            printf("%s    %s    %s    %d-%d-%d    %s    %s\n", L->List[i].stuno, L->List[i].name, L->List[i].sex, L->List[i].date.year, L->List[i].date.month, L->List[i].date.day, L->List[i].tel, L->List[i].adds);
            flag = 0;
            break;
        }
    }
    if (flag)
        printf("No Found\n");
    printf("****************************************************\n");
    printf("\n");
    system("pause");
}

void SelectStudent(StudentList *L) //查询学生信息
{
    system("cls"); //清屏
    int i;
    while (1)
    {
        system("cls"); //清屏
        Menu2();
        printf("请选择功能（输入数值）：");
        scanf("%d", &i);
        switch (i)
        {
        case 1:
            SelectName(L);
            break;
        case 2:
            SelectNumber(L);
            break;
        case 3:
            return;
        default:
            printf("你输入有误，重新选择!\n");
            scanf("%d", &i);
            break;
        }
    }
}

void PrintInfo(StudentList *L) //浏览学生信息
{
    system("cls"); //清屏
    printf("\n");
    printf("******************学生信息浏览******************\n");
    printf("拥有%d位学生\n", L->length);
    printf("学号    姓名    性别    生日    电话    地址\n");
    for (int i = 0; i < L->length; i++)
        printf("%s    %s    %s    %d-%d-%d    %s    %s\n", L->List[i].stuno, L->List[i].name, L->List[i].sex, L->List[i].date.year, L->List[i].date.month, L->List[i].date.day, L->List[i].tel, L->List[i].adds);
    printf("***********************************************\n");
    printf("\n");
    system("pause");
}

void Input(StudentList *L) //输入学生数据
{
    student e;
    int i;
    printf("学号：");
    scanf("%s", e.stuno);
    printf("姓名：");
    scanf("%s", e.name);
    printf("性别：");
    scanf("%s", e.sex);
    printf("出生日期(如yyyy-mm-dd)：");
    scanf("%d-%d-%d", &e.date.year, &e.date.month, &e.date.day);
    printf("电话：");
    scanf("%s", e.tel);
    printf("地址：");
    scanf("%s", e.adds);
    for (i = 0; i < N; i++) //初始成绩均为0
        e.score[i] = 0;
    Insert(L, e); //输入完成，插入到顺序表尾端
    return;
}

void InsertStudent(StudentList *L) //新增学生信息
{
    int i;
    while (1)
    {
        printf("录入学生信息，请选择：1:输入数据  0：返回\n");
        scanf("%d", &i);
        switch (i)
        {
        case 0:
            break;
        case 1:
            Input(L);
            break;
        default:
            printf("您输入有误，重新选择!\n");
            break;
        }
        if (i == 0)
            break;
    }
    return;
}

void StudentInfo(StudentList *L) //学生基本信息管理操作
{
    int i;
    while (1)
    {
        system("cls"); //清屏
        Menu1();
        printf("请选择功能（输入数值）：");
        scanf("%d", &i);
        switch (i)
        {
        case 1:
            InsertStudent(L);
            break;
        case 2:
            PrintInfo(L);
            break;
        case 3:
            SelectStudent(L);
            break;
        case 4:
            UpdateStudent(L);
            break;
        case 5:
            DeleteStudent(L);
            break;
        case 6:
            return;
        default:
            printf("您输入有误，重新选择!\n");
            scanf("%d", &i);
            break;
        }
    }
}

void MainMenu() //主菜单
{
    printf("\n");
    printf("******************欢迎进入学生管理系统******************\n");
    printf("\n");
    printf("               1.基本信息管理\n");
    printf("               2.成绩管理\n");
    printf("               3.退出\n");
    printf("\n");
    printf("*******************************************************\n");
    printf("\n");
    return;
}

int main()
{
    StudentList L;
    int i;
    InitList(&L);
    while (1)
    {
        system("cls"); //清屏
        MainMenu();
        printf("请选择功能（输入数值）：");
        scanf("%d", &i);
        switch (i)
        {
        case 1:
            StudentInfo(&L);
            break;
        case 2:
            ScoreInfo(&L);
            break;
        case 3:
            return 0;
        default:
            printf("您输入有误，重新选择!\n");
            break;
        }
    }
    return 0;
}