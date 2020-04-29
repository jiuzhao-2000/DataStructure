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

PTREE init_tree(char *val);                            //�����ַ���val��ʼ��һ����,val��ʾһ�����������������'#'�ַ���ʾ
void init_inorder(char *val, PTREE *node, int *count); //���򴴽����ڲ�ʵ��
void InPreorderTraverse(PTREE tree);                   //�������
void InOrderTraverse(PTREE tree);                      //�������
void InLastTraverse(PTREE tree);                       //�������

int main(void)
{
    char *val = "AB#DF##G##C#E#H##";
    PTREE head;
    head = init_tree(val);
    printf("���������");
    InPreorderTraverse(head);
    printf("\n���������");
    InOrderTraverse(head);
    printf("\n���������");
    InLastTraverse(head);
    return 0;
}

//�����ַ���val��ʼ��һ����,val��ʾһ��������������'#'�ַ���ʾ
PTREE init_tree(char *val)
{
    PTREE head;
    int count = 0;
    init_inorder(val, &head, &count);
    return head;
}
//���򴴽����ڲ�ʵ��
void init_inorder(char *val, PTREE *node, int *count)
{
    //1.�ж��ַ��Ƿ�=='#'
    //2.��ȶԽڵ㸳��ֵ
    //3.����ȴ����ڵ㣬����ֵ
    //4.���򴴽���ڵ㣬�����򴴽��ҽڵ�
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

//�������
void InPreorderTraverse(PTREE tree)
{
    if (tree)
    {
        printf("%c", tree->data);
        InPreorderTraverse(tree->left);
        InPreorderTraverse(tree->right);
    }
}
//�������
void InOrderTraverse(PTREE tree)
{
    if (tree)
    {
        InOrderTraverse(tree->left);
        printf("%c", tree->data);
        InOrderTraverse(tree->right);
    }
}

//�������
void InLastTraverse(PTREE tree)
{
    if (tree)
    {
        InLastTraverse(tree->left);
        InLastTraverse(tree->right);
        printf("%c", tree->data);
    }
}