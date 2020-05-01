#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

//二叉树类型定义
typedef struct treeNode
{
    struct treeNode *lchild, *rchild;
    _Bool ltag, rtag;
    char data;
} TREENODE, *PTREENODE;

PTREENODE stTree;
PTREENODE stTree2;

void init_tree(PTREENODE *node, char *ctree, int *count); //凭借先序字符串构造不带线索的树
void init_stTree();                                       //初始化全局变量
void Inorder_Thr(PTREENODE *node);                        //中序线索化二叉树
void InPreorder_Thr(PTREENODE *node);                     //先序线索化二叉树
void InLastorder_Thr(PTREENODE *node);                    //后序线索化二叉树

int main(void)
{
    char *val = "ABD##F##C#E##";
    PTREENODE node;
    int count = 0;
    init_tree(&node, val, &count);
    init_stTree();
    InLastorder_Thr(&node);
    return 0;
}

//凭借字符串构造不带线索的树,标识符在线索化在系统的初始化
void init_tree(PTREENODE *node, char *ctree, int *count)
{
    //若字符为'#'则该节点为空
    if (ctree[*count] != '#')
    {
        //空间分配失败退出
        if (!(*node = (PTREENODE)malloc(sizeof(TREENODE))))
        {
            exit(-1); //空间已满退出程序
        }
        (*node)->data = ctree[*count];             //为节点值域赋值
        (*count)++;                                //字符串向后移动
        init_tree(&(*node)->lchild, ctree, count); //先序创建左子树
        init_tree(&(*node)->rchild, ctree, count); //先序创建右子树
    }
    else
    {
        (*count)++;   //为空字符串向后移动一位
        *node = NULL; //节点赋空
    }
}
//初始化全局变量
void init_stTree()
{
    TREENODE a;
    stTree = NULL;
    stTree2 = &a;
}
//中序线索化二叉树
void Inorder_Thr(PTREENODE *node)
{
    //stTree与stTree(为stTree有子树指针)其值为NULL，将stTree指向前驱
    if (*node)
    {
        Inorder_Thr(&(*node)->lchild); //中序遍历左子树
        if ((*node)->lchild)
        {
            (*node)->ltag = 0;
        }
        else
        {
            (*node)->ltag = 1;
            (*node)->lchild = stTree;
        }
        if (stTree2)
        {
            if (stTree)
                stTree->rtag = 0;
        }
        else
        {
            stTree->rtag = 1;
            stTree->rchild = *node;
        }
        stTree = *node;                //让stTree指向前驱
        stTree2 = stTree->rchild;      //指向stTree右子树位置
        Inorder_Thr(&(*node)->rchild); //中序遍历右子树
    }
}
//先序线索化二叉树
void InPreorder_Thr(PTREENODE *node)
{
    //stTree与stTree(为stTree有子树指针)其值为NULL，将stTree指向前驱
    if (*node) //节点是否为空判断
    {
        PTREENODE left = (*node)->lchild; //存放将要被修改左子树
        if ((*node)->lchild)              //左指针是否为空判断
        {
            (*node)->ltag = 0;
        }
        else
        {
            (*node)->ltag = 1;
            (*node)->lchild = stTree; //将前驱赋值给空的左指针
        }
        if (stTree2) //前驱右指针非空
        {
            if (stTree) //且前驱非空，主要是防止第一次判断出错
                stTree->rtag = 0;
        }
        else
        {
            stTree->rtag = 1;
            stTree->rchild = *node;
        }
        stTree = *node;           //让stTree指向前驱
        stTree2 = stTree->rchild; //指向stTree右子树位置
        InPreorder_Thr(&left);
        InPreorder_Thr(&(*node)->rchild);
    }
}
//后序线索化二叉树
void InLastorder_Thr(PTREENODE *node)
{
    if (*node)
    {
        InLastorder_Thr(&(*node)->lchild);
        InLastorder_Thr(&(*node)->rchild);
        if ((*node)->lchild) //左指针是否为空判断
        {
            (*node)->ltag = 0;
        }
        else
        {
            (*node)->ltag = 1;
            (*node)->lchild = stTree; //将前驱赋值给空的左指针
        }
        if (stTree2) //前驱右指针非空
        {
            if (stTree) //且前驱非空，主要是防止第一次判断出错
                stTree->rtag = 0;
        }
        else
        {
            stTree->rtag = 1;
            stTree->rchild = *node;
        }
        stTree = *node;           //让stTree指向前驱
        stTree2 = stTree->rchild; //指向stTree右子树位置
    }
}