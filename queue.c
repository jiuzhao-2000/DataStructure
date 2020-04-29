#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1
#define SIZE 7

typedef int ELEM; //元素定义
typedef struct queue
{
    ELEM *elem; //elem做循环数组首地址
    int front;  //头位置数
    int rear;   //尾位置数
} QUEUE, *pQUEUE;

void init_que(pQUEUE pq);             //队列初始化
_Bool is_null(pQUEUE pq);             //队列是否空判断
_Bool is_full(pQUEUE pq);             //队列满判断
_Bool enter_que(pQUEUE pq, ELEM val); //入队
_Bool leave_que(pQUEUE pq);           //出队
void tra_que(pQUEUE pq);              //遍历

int main(void)
{
    QUEUE queuel;
    init_que(&queuel);
    if (is_null(&queuel))
    {
        printf("It is Null!\n");
    }
    //入队
    enter_que(&queuel, 12);
    enter_que(&queuel, 13);
    enter_que(&queuel, 14);
    enter_que(&queuel, 15);
    enter_que(&queuel, 16);
    enter_que(&queuel, 17);
    //判断是否加满
    is_full(&queuel);
    //遍历确认
    tra_que(&queuel);
    //出队
    for (int i = 0; i <= 7; i++)
    {
        leave_que(&queuel);
    }
    //判断出队是否成功
    if (is_null(&queuel))
    {
        printf("It is Null!\n");
    }
    return 0;
}

//初始化
void init_que(pQUEUE pq)
{
    (pq->elem = (ELEM *)malloc(sizeof(ELEM) * SIZE)) ? (pq->front = pq->rear = 0) : (printf("\nFail!\n"));
}

//队列是否空判断
_Bool is_null(pQUEUE pq)
{
    int val;
    (pq->front == pq->rear) ? (val = 1) : (val = 0);
    return val;
}

//队列满判断
_Bool is_full(pQUEUE pq)
{
    int val;
    (pq->front == (pq->rear + 1) % 7) ? (val = 1, printf("Full!\n")) : (val = 0);
    return val;
}

//入队
_Bool enter_que(pQUEUE pq, ELEM val)
{
    if (is_full(pq))
    {
        return ERROR;
    }
    else
    {
        pq->elem[pq->rear] = val;
        pq->rear = (pq->rear + 1) % 7;
        return OK;
    }
}

//出队
_Bool leave_que(pQUEUE pq)
{
    //合法性检查，是否位空
    if (is_null(pq))
    {
        return ERROR;
    }
    //将头部向后移动一位
    pq->front = (++(pq->front)) % 7;
}

//遍历(从头开始)
void tra_que(pQUEUE pq)
{
    int i = 0;
    while (pq->rear != ((pq->front) + i) % 7)
    {
        printf("%d\n", pq->elem[pq->front + i]);
        i++;
    }
}