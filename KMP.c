#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define MAXSIZE 100

typedef struct list
{
    char *data;
    int Length; //总长
    int count;  //有效长度
} LIST, *PLIST;

PLIST init_list();         //初始化一个串（顺序结构）
void add_list(PLIST a);    //添加字符串到enter结束
int KMP(PLIST a, PLIST b); //kmp算法实现
int *cal_next(PLIST a);    //计算next数组，返回next数组指针

int main(void)
{
    PLIST a, b;
    int n;
    a = init_list();
    b = init_list();
    printf("Please input string:\n");
    add_list(a);
    printf("Please input string:\n");
    add_list(b);
    n = KMP(a, b);
    printf("Index:%d", n);
    return 0;
}

//初始化一个串（顺序结构）
PLIST init_list()
{
    PLIST p = (PLIST)malloc(sizeof(LIST));
    p->data = (char *)malloc(sizeof(char) * MAXSIZE);
    p->count = 0;
    p->Length = MAXSIZE;
    return p;
}

//添加字符串到enter结束
void add_list(PLIST a)
{
    char val = getchar();
    while (val != '\n')
    {
        (a->data)[a->count] = val;
        a->count++;
        val = getchar();
    }
}

//kmp算法实现
int KMP(PLIST a, PLIST b)
{
    int i, j, *next; //i指向被匹配数，j指向模式串，next指向
    i = 1;
    j = 1;
    next = cal_next(b);
    while (i - 1 < a->count && j - 1 < b->count)
    {
        if (a->data[i - 1] == b->data[j - 1] || j == 0)
        {
            i++;
            j++;
        }
        else
        {
            j = next[j - 1];
        }
    }
    free(next);
    if (j == b->count + 1)
    {
        return i - b->count;
    }
    return -1; //失败返回-1
}

//计算next数组，返回next数组指针
int *cal_next(PLIST a)
{
    int *next = (int *)malloc(sizeof(int) * (a->count) );
    int i = 1;
    int j = 0;
    next[0] = 0;
    while (i < a->count)
    {
        if (j == 0 || a->data[i - 1] == a->data[j - 1])
        {
            i++;
            j++;
            if (a->data[i - 1] == a->data[j - 1])
            {
                next[i - 1] = next[j - 1];
            }
            else
            {
                next[i - 1] = j;
            }
        }
        else
        {
            j = next[j - 1];
        }
    }
    return next;
}