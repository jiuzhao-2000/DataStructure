#include <stdio.h>
#include <stdlib.h>

#define ERROR 0
#define OK 1

typedef struct tree
{
    struct tree *left;
    struct tree *right;
    char data;
} TREE, *PTREE;

PTREE init_tree(char *val);                                               //根据字符串val初始化一个树,val表示一个先序二叉树，空用'#'字符表示
void init_inorder(char *val, PTREE *node, int *count);                    //先序创建的内部实现
int find_val(PTREE tree, char val);                                       //匹配tree中val的层级
void InPreorderTraverse(PTREE tree, int *count, char val, _Bool *succes); //先序遍历传进一个零值

int main(void)
{
    char *ctree = "AB#DF##G##C#E#H##";
    PTREE head = init_tree(ctree);
    printf("输入匹配字符：");
    char val = getchar();
    int where = find_val(head, val);
    if (where != 0)
    {
        printf("您输入字符串层级为：%d", where);
    }
    else
    {
        printf("您输入字符未在树中！");
    }
    return 0;
}

//根据字符串val初始化一个树,val表示一个二叉树，空用'#'字符表示
PTREE init_tree(char *val)
{
    PTREE head;
    int count = 0;
    init_inorder(val, &head, &count);
    return head;
}
//先序创建的内部实现
void init_inorder(char *val, PTREE *node, int *count)
{
    //1.判断字符是否=='#'
    //2.相等对节点赋空值
    //3.不相等创建节点，并赋值
    //4.先序创建左节点，在先序创建右节点
    if (val[*count] == '#')
    {
        *node = NULL;
        (*count)++;
    }
    else
    {
        *node = (PTREE)malloc(sizeof(TREE));
        (*node)->data = val[*count];
        (*count)++;
        init_inorder(val, &((*node)->left), count);
        init_inorder(val, &((*node)->right), count);
    }
}
//匹配tree中val的层级，未匹配到该值返回0
int find_val(PTREE tree, char val)
{
    int count = 0;
    _Bool success = ERROR;
    InPreorderTraverse(tree, &count, val, &success);
    return count;
}
//先序遍历匹配
void InPreorderTraverse(PTREE tree, int *count, char val, _Bool *succes)
{
    //1.空树返回，非空进行判断
    //2.层级加一
    //3.对字符串val进行匹配，
    //4.匹配成功，将标识符succes设置为true
    //5.匹配失败先序遍历左子树，先序遍历右子树
    //6.遍历左子树后，若标识符为false，层级减1，标识符为true层级不变，并return
    (*count)++;
    if (tree)
    {
        if (tree->data == val)
        {
            *succes=OK;
            return ;
        }
        InPreorderTraverse(tree->left, count, val,succes);
        if (*succes==OK)
        {
            return;
        }
        else
        {
            (*count)--;
        }
        InPreorderTraverse(tree->right, count, val,succes);
        if (*succes==OK)
        {
            return;
        }
        else
        {
            (*count)--;
        }
    }
}