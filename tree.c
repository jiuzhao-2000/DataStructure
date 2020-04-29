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

PTREE init_tree(char *val);                            //根据字符串val初始化一个树,val表示一个先序二叉树，空用'#'字符表示
void init_inorder(char *val, PTREE *node, int *count); //先序创建的内部实现
void InPreorderTraverse(PTREE tree);                   //先序遍历
void InOrderTraverse(PTREE tree);                      //中序遍历
void InLastTraverse(PTREE tree);                       //后序遍历

int main(void)
{
    char *val = "AB#DF##G##C#E#H##";
    PTREE head;
    head = init_tree(val);
    printf("先序遍历：");
    InPreorderTraverse(head);
    printf("\n中序遍历：");
    InOrderTraverse(head);
    printf("\n后序遍历：");
    InLastTraverse(head);
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

//先序遍历
void InPreorderTraverse(PTREE tree)
{
    if (tree)
    {
        printf("%c", tree->data);
        InPreorderTraverse(tree->left);
        InPreorderTraverse(tree->right);
    }
}
//中序遍历
void InOrderTraverse(PTREE tree)
{
    if (tree)
    {
        InOrderTraverse(tree->left);
        printf("%c", tree->data);
        InOrderTraverse(tree->right);
    }
}

//后序遍历
void InLastTraverse(PTREE tree)
{
    if (tree)
    {
        InLastTraverse(tree->left);
        InLastTraverse(tree->right);
        printf("%c", tree->data);
    }
}