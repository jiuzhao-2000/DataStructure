#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 100
#define INCREASE 10
#define OK 1
#define ERROR 0

typedef int ELEM;
typedef struct Node
{
    ELEM * elem;
    int len;
    int size;
}NODE,*pNODE;

_Bool init_Stack(pNODE p);//初始化
void enter_Stack(pNODE p,ELEM val);//进栈
_Bool leave_Stack(pNODE p,ELEM *val);//出栈
_Bool is_Full(pNODE p);//判断是否满
void increase_Size(pNODE p);

int main(void){
    NODE st;
    ELEM val;
    init_Stack(&st);
    enter_Stack(&st,13);
    enter_Stack(&st,14);
    enter_Stack(&st,15);
    enter_Stack(&st,16);
    leave_Stack(&st,&val);
    printf("%10d",val);
    leave_Stack(&st,&val);
    printf("%10d",val);
    leave_Stack(&st,&val);
    printf("%10d",val);
    
    return 0;
}

//初始化
_Bool init_Stack(pNODE p){
    //分配MAX_SIZE个NODE大小的空间
    if(p->elem=(ELEM *)malloc(sizeof(ELEM)*MAX_SIZE))
    {
        p->len=0;
        p->size=MAX_SIZE;
        return OK;
    }
    return ERROR;
}

//进栈
void enter_Stack(pNODE p,ELEM val)
{
    //判断是否满
    if (is_Full(p))
    {
        increase_Size(p);
    }
    p->elem[p->len]=val;
    p->len=p->len+1;
}

//出栈
_Bool leave_Stack(pNODE p,ELEM *val)
{
    if (p->len!=0)
    {
        *val=p->elem[p->len-1];
        p->len--;
        return OK;
    }
    printf("\n出栈失败\n");
    return ERROR;
}

//栈是否满判断函数
_Bool is_Full(pNODE p){
    if (p->len==p->size)
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}

//扩容实现
void increase_Size(pNODE p)
{
    p->size+=INCREASE;
    p->elem=(ELEM *)malloc(sizeof(ELEM)*p->size+INCREASE);
}