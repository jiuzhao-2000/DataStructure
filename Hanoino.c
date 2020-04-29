#include <stdio.h>

#define ERROR 0
#define OK 1

//使用栈将递归转化成非递归
typedef struct stack
{
    int data;           //数据域
    struct stack *next; //指向下一节点
} STACK, *PSTACK;

void init_stack();          //初始化一个栈
void enter(PSTACK node);    //进栈
int goout(STACK node);      //出栈
_Bool is_null(PSTACK node); //判断栈是否为空
int calculator(int num);    //计算次数

int main(void)
{
    int num;
    printf("这是汉诺塔的递归算法用栈转化为非递归算法的实现：\n");
    printf("输入层数：");
    if (scanf("%d", &num) == 1)
    {
        printf("%d", calculator(num));
    }
}

//非递归演示
int calculator(int num)
{
    STACK st; //存放递归记录
    int no;
    while (num != 0 && st.data == 0)
    {
        if (num == 0)
        {
            no = 1 + 2 * goout(st);
        }
        else
        {
            num--;
        }
    }

    return no;
}