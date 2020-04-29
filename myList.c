#include <stdlib.h>
#include <stdio.h>

#define ERROR 0;
#define OK 1;

//链表元素定义
typedef int elem;
//节点设定
typedef struct list
{
    elem list_Data;
    struct list *list_Next;
} myList, *pMyList;

//函数声明

pMyList Initialize();                              //初始化一个单链表，返回一个头指针
_Bool Add_List(pMyList p, elem num);               //对元素的添加
_Bool Inster_List(pMyList p, int no, pMyList num); //对元素的插入
_Bool Del_List(pMyList p, int no);                 //对于第no(从零开始计数)个数的删除
_Bool Change_List(pMyList p, int no, elem num);    //对第no(从零开始计数)换成num
int Find_List(myList p, elem num);                 //查询num，返回所在位置。

int main(void)
{
    pMyList list1 = Initialize(); //类似oo语言的实例化
    int i;                        //存储查询出的位置
    Add_List(list1, 10);
    Add_List(list1, 11);
    Add_List(list1, 12);
    Add_List(list1, 13);
    Add_List(list1, 14);
    Add_List(list1, 16);
    myList my;
    my.list_Data = 15;
    Inster_List(list1, 3, &my);
    Del_List(list1, 6);
    Change_List(list1, -1, 39);
    i = Find_List(*list1, 15);
    printf("%d", i);
    return 0;
}

//初始化一个单链表，返回一个头指针
pMyList Initialize()
{
    pMyList p1 = NULL;
    if (p1 = (pMyList)malloc(sizeof(myList)))
    {
        (*p1).list_Next = NULL;
        return p1;
    }
    printf("You don't have room to do it!");
}

//对元素的添加
_Bool Add_List(pMyList p, elem num)
{
    _Bool Running = 1;
    while (Running)
    {
        if (!p->list_Next)
        {
            pMyList padd;
            if (padd = (pMyList)malloc(sizeof(myList)))
            {
                (*padd).list_Data = num;
                p->list_Next = padd;
                (*(p->list_Next)).list_Next = NULL;
                Running--;
            }
            else
            {
                return ERROR;
            }
        }
        else
        {
            p = p->list_Next;
        }
    }
    return OK;
}

//对元素的插入
_Bool Inster_List(pMyList p, int no, pMyList num)
{
    //合法性检测
    if (no < 0)
    {
        printf("Don't have it!");
        return ERROR;
    }
    for (int i = 1; i <= no; i++)
    {
        if (p->list_Next)
        {
            p = p->list_Next;
        }
        else
        {
            return ERROR;
        }
    }
    num->list_Next = p->list_Next;
    p->list_Next = num;
}

//对于第no(从零开始计数)个数的删除
_Bool Del_List(pMyList p, int no)
{
    pMyList p_Del = p; //定义p_Del表示删除的前一个指针
    pMyList del_num;   //保存删除的地址，以便释放
                       //合法性检测
    if (no < 0)
    {
        printf("Don't have it!");
        return ERROR;
    }
    for (int i = 0; i < no; i++)
    {
        if (p_Del->list_Next->list_Next != NULL)
        {
            p_Del = p_Del->list_Next;
        }
        else
        {
            printf("no is bu he fa!");
            return ERROR;
        }
    }
    //经过for循环p-Del指向删除的前一个
    del_num = p_Del->list_Next;
    //判断是否是最后一个
    if (del_num->list_Next)
    {
        p_Del->list_Next = p_Del->list_Next->list_Next;
    }
    else
    {
        p_Del->list_Next = NULL;
    }
    free(del_num);
    return OK;
}

//对第no(从零开始计数)换成num
_Bool Change_List(pMyList p, int no, elem num)
{
    //合法性检测
    if (no < 0)
    {
        printf("Don't have it!");
        return ERROR;
    }
    pMyList p_Ch = p;
    for (int i = 0; i < no; i++)
    {
        if (p_Ch->list_Next->list_Next != NULL)
        {
            p_Ch = p_Ch->list_Next;
        }
        else
        {
            printf("no is bu he fa!");
            return ERROR;
        }
    }
    p_Ch->list_Next->list_Data = num;
    return OK;
}

//查询num，返回所在位置。
int Find_List(myList p, elem num)
{
    pMyList p_List = &p;
    int num_Where = 0;
    while (p_List->list_Next->list_Data != num)
    {
        if (p_List->list_Next)
        {
            p_List = p_List->list_Next;
            num_Where++;
        }
        else
        {
            exit(-1);
        }
    }
    return num_Where;
}
