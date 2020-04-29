#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define SIZE_INCREASE 10 //顺序表满则自然增长数

typedef int typeelem; //元素类型

//定义数据类型SqList
typedef struct array
{
    typeelem *num; //元素
    int len;       //最大长度
    int cnt;       //有效位数
} SqList;

_Bool append_arr(SqList *sq, int sq_num);      //追加
_Bool init_arr(SqList *sq, int sql);           //顺序表初始化
void show_arr(SqList sq);                      //遍历顺序表
_Bool is_null(SqList sq);                      //判断顺序表是否为空
_Bool is_full(SqList sq);                      //判断顺序表是否满
_Bool inster_arr(SqList *sq, int n, int val);  //顺序表sq的下标为n的位置进行插入val
_Bool free_arr(SqList *sq);                    //释放顺序表
_Bool del_arr(SqList *sq, int num, _Bool way); //两种删除方法 1. way=0根据位置  2. way=1根据存放内容
_Bool increase_arr(SqList *sq);                //顺序表增加空间的实现
_Bool change_arr(SqList *sq, int no, int num); //对下标为no的修改

int main(void)
{
    SqList sq;
    int length, inster, where, del, change_num;
    //length为顺序表设置长度
    //inster插入值,where为下标，del为删除
    //change_num修改值
    _Bool b_del;
    short choice;
    _Bool running = 1;
    while (running)
    {
        printf("\n====================\n");
        printf("There are some function:\n");
        printf("1.Found a SeqList.\n");                   //创建一个顺序表
        printf("2.Do insert in the end.\n");              //末尾插入一个值
        printf("3.Show your SeqList.\n");                 //遍历顺序表
        printf("4.Your want to there Inster a value.\n"); //插入对某下标一个值
        printf("5.Free your SqList!\n");                  //释放顺序表
        printf("6.Delete one number!\n");                 //根据下标或者值来删除
        printf("7.Change a number\n");                    //改变一个值
        printf("8.Bow out!\n");                           //退出
        printf("Please choose your idea:");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("please return length:");
            scanf("%d", &length);
            if (init_arr(&sq, length))
            {
                printf("Success!\n");
            }
            else
            {
                printf("Fail!\n");
            }

            break;
        case 2:
            printf("Please input value:");
            scanf("%d", &inster);
            if (append_arr(&sq, inster))
            {
                printf("Success!\n");
            }
            else
            {
                printf("Fail!\n");
            }
            break;
        case 3:
            show_arr(sq);
            break;
        case 4:
            printf("Please input you want to value:");
            scanf("%d", &inster);
            printf("Where are you want to put:");
            scanf("%d", &where);
            if (inster_arr(&sq, where, inster))
            {
                printf("Success!\n");
            }
            else
            {
                printf("Fail!\n");
            }
            break;
        case 5:
            if (free_arr(&sq))
            {
                printf("Success!\n");
            }
            else
            {
                printf("Fail!\n");
            }
        case 6:
            printf("you can chose delete 1.in the num(input 1) 2.in the index(input 0):");
            scanf("%d", &b_del);
            printf("PLease input number:");
            scanf("%d", &del);
            if (del_arr(&sq, del, b_del))
            {
                printf("Success!\n");
            }
            else
            {
                printf("Fail!\n");
            }
            break;
        case 7:
            printf("Please input a number:");
            scanf("%d", change_num);
            printf("Please input index:");
            scanf("%d", &where);
            break;
        case 8:
            running = 0;
            break;
        default:
            printf("Input must 1-8!");
            break;
        }
    }
    return 0;
}

//初始化
_Bool init_arr(SqList *sq, int sql)
{
    if (sq->num = (typeelem *)malloc(sizeof(typeelem) * sql))
    {
        (*sq).len = sql;
        (*sq).cnt = 0;
        return OK;
    }
    return ERROR;
}

//对顺序表是否为空判断的函数,空返回0，否则返回1
_Bool is_null(SqList sq)
{
    if (sq.cnt)
    {
        return ERROR;
    }
    else
    {
        return OK;
    }
}

//对顺序表是否满的判断函数，满返回1，否则返回0
_Bool is_full(SqList sq)
{
    if (sq.len == sq.cnt)
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}

//对顺序表的遍历的实现
void show_arr(SqList sq)
{
    if (is_null(sq))
    {
        printf("it is NULL table!\n");
        return;
    }

    for (int i = 0; i < sq.cnt; i++)
    {
        printf("%5d", sq.num[i]);
    }
    return;
}

//对顺序表追加的实现成功返回1，失败返回0。
_Bool append_arr(SqList *sq, int sq_num)
{
    //判断顺序表是否已满的判断
    //满则扩容的实现
    if ((is_full(*sq)))
    {
        if ((increase_arr(sq)))
        {
            (sq->num)[sq->cnt] = sq_num;
            (sq->cnt)++;
            return OK;
        }
        return ERROR; //满且内存空间不足无法增加
    }
    else //顺序表空间有剩余
    {
        (sq->num)[sq->cnt] = sq_num;
        (sq->cnt)++;
        return OK;
    }
    return ERROR;
}

//顺序表sq的下标为n的位置进行插入val
_Bool inster_arr(SqList *sq, int n, int val)
{
    //对插入位置合法性检查
    if (sq->cnt + 1 < n || n < 0)
    {
        return ERROR;
    }
    //对空间合法性检查
    if ((is_full(*sq)))
    {
        if ((increase_arr(sq)))
        {
            //将顺序表从后开始移动一位，直到下标为n移动完成停止
            for (int i = (*sq).cnt; i >= n; i--)
            {
                sq->num[i + 1] = sq->num[i];
            }
            //在n位置传入val的值
            sq->num[n] = val;
            sq->cnt++;
            return OK;
        }
        return ERROR; //满且内存空间不足无法增加
    }
    //将顺序表从后开始移动一位，直到下标为n移动完成停止
    for (int i = (*sq).cnt; i >= n; i--)
    {
        sq->num[i + 1] = sq->num[i];
    }
    //在n位置传入val的值
    sq->num[n] = val;
    sq->cnt++;
    return OK;
}

//释放顺序表
_Bool free_arr(SqList *sq)
{
    free(sq);
    return OK;
}

//两种删除方法 1. way=0根据位置  2. way=1根据存放内容
_Bool del_arr(SqList *sq, int num, _Bool way)
{
    if (way) //根据存放内容
    {
        if (is_null(*sq))
        {
            printf("it is NULL table!\n");
            return ERROR;
        }
        _Bool b_arr = 0;
        for (int i = 0; i < sq->cnt; i++)
        {
            if (sq->num[i] == num || b_arr)
            {
                sq->num[i] = sq->num[i + 1];
                b_arr++;
            }
            //遍历顺序表当找到删除值时进行删除，并将后面值依次向前移动一位
        }
        //遍历之后有俩种结果1.找到2.没找到
        if (b_arr) //找到该值
        {
            sq->cnt--;
            return OK;
        }
        else //没有找到该值
        {
            printf("I don't find it!");
            return ERROR;
        }
    }
    else //根据位置
    {
        //先是合法性判断
        if (sq->cnt < num)
        {
            return ERROR;
        }
        else
        {
            //将删除位置的值用下一位覆盖，后面依次向前移动一位
            for (int i = num; i < sq->cnt; i++)
            {
                sq->num[i] = sq->num[i + 1];
            }
            sq->cnt--;
            return OK;
        }
    }
}

//增加10个typeelem的空间，成功返回1，失败返回0
_Bool increase_arr(SqList *sq)
{
    if (sq->num = (typeelem *)realloc(sq->num, SIZE_INCREASE + sq->len))
    {
        sq->len = SIZE_INCREASE + sq->len;
        return OK;
    }
    else
    {
        return ERROR;
    }
}

//修改顺序表下标为no的值为num,成功返回1，失败返回0
_Bool change_arr(SqList *sq, int no, int num)
{
    //修改位置合法检查
    if (no > 0 && no < sq->cnt)
    {
        sq->num[no] = num;
        return OK;
    }
    return ERROR;
}