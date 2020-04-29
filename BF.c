#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1

typedef struct string
{
    char val;
    struct string *next;
    int length;
} STRING, *PSTRING;

PSTRING init_str();                    //初始化
_Bool add_str(PSTRING, char);          //追加
_Bool bf_arr(PSTRING ed, PSTRING ing); //BF算法

int main(void)
{
    char input;
    //将匹配字符字符串与被匹配字符串初始化
    PSTRING BFing = init_str();
    PSTRING BFed = init_str();
    printf("BF show!\n");
    printf("input no.1 string:\n");
    while (scanf("%c", &input) == 1 && input != '#')
    {
        //只读取每行首字符
        while (getchar() != '\n')
        {
            continue;
        }
        add_str(BFed, input);
    }
    printf("input no.2 string:\n");
    getchar();
    while (scanf("%c", &input) == 1 && input != '#')
    {
        while (getchar() != '\n')
        {
            continue;
        }
        add_str(BFing, input);
    }

    bf_arr(BFed, BFing) ? printf("succse!") : printf("Fail!");
    return ERROR;
}

//初始化
PSTRING init_str()
{
    PSTRING head;
    if (head = (PSTRING)malloc(sizeof(STRING)))
    {
        head->next = NULL;
        head->length = 0;
        return head;
    }
    printf("We have no room!");
}

//追加
_Bool add_str(PSTRING head, char val)
{
    PSTRING where = head;
    PSTRING newadd;
    while (where->next != NULL)
    {
        where = where->next;
    }
    if (newadd = (PSTRING)malloc(sizeof(STRING)))
    {
        where->next = newadd;
        newadd->val = val;
        newadd->next = NULL;
        head->length++;
        return OK;
    }
    return ERROR;
}

//BF算法
_Bool bf_arr(PSTRING ed, PSTRING ing)
{
    PSTRING main_arr = ed;   //指向被匹配头字符
    PSTRING minor_arr = ing; //指向匹配字符
    PSTRING headdel;         //指向被匹配字符
    int edlength = 0;        
    int inglength = 0;
    while (edlength - 1 < (ed->length) - (ing->length))
    {
        //初始化，从头开始遍历
        minor_arr = ing;
        inglength = 0;
        headdel = main_arr;
        while (inglength < ing->length)
        {
            if (headdel->next->val != minor_arr->next->val)
            {
                break;
            }
            headdel = headdel->next;
            minor_arr = minor_arr->next;
            inglength++;
        }
        if (inglength == ing->length)
        {
            return OK;
        }
        main_arr = main_arr->next;
        edlength++;
    }
    return ERROR;
}