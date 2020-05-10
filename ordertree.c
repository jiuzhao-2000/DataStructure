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

PTREE init_tree(char *val);                                               //�����ַ���val��ʼ��һ����,val��ʾһ�����������������'#'�ַ���ʾ
void init_inorder(char *val, PTREE *node, int *count);                    //���򴴽����ڲ�ʵ��
int find_val(PTREE tree, char val);                                       //ƥ��tree��val�Ĳ㼶
void InPreorderTraverse(PTREE tree, int *count, char val, _Bool *succes); //�����������һ����ֵ

int main(void)
{
    char *ctree = "AB#DF##G##C#E#H##";
    PTREE head = init_tree(ctree);
    printf("����ƥ���ַ���");
    char val = getchar();
    int where = find_val(head, val);
    if (where != 0)
    {
        printf("�������ַ����㼶Ϊ��%d", where);
    }
    else
    {
        printf("�������ַ�δ�����У�");
    }
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
//ƥ��tree��val�Ĳ㼶��δƥ�䵽��ֵ����0
int find_val(PTREE tree, char val)
{
    int count = 0;
    _Bool success = ERROR;
    InPreorderTraverse(tree, &count, val, &success);
    return count;
}
//�������ƥ��
void InPreorderTraverse(PTREE tree, int *count, char val, _Bool *succes)
{
    //1.�������أ��ǿս����ж�
    //2.�㼶��һ
    //3.���ַ���val����ƥ�䣬
    //4.ƥ��ɹ�������ʶ��succes����Ϊtrue
    //5.ƥ��ʧ������������������������������
    //6.����������������ʶ��Ϊfalse���㼶��1����ʶ��Ϊtrue�㼶���䣬��return
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