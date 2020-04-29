#include <stdio.h>

int moveThing(int n); //汉诺塔递归实现

int main(void)
{
    int n;
    printf("请输入数字：\n");
    if (1 == scanf("%d", &n) && n > 0)
    {
        printf("结果为：%d\n", moveThing(n));
    }
    return 0;
}

//传入n值，计数次数
int moveThing(int n)
{
    int val; //返回值
    if (n == 1)
    {
        return 1;
    }
    else
    {
        val = 1 + 2 * moveThing(n - 1);
    }
    return val;
}