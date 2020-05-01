#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

//���������Ͷ���
typedef struct treeNode
{
    struct treeNode *lchild, *rchild;
    _Bool ltag, rtag;
    char data;
} TREENODE, *PTREENODE;

PTREENODE stTree;
PTREENODE stTree2;

void init_tree(PTREENODE *node, char *ctree, int *count); //ƾ�������ַ������첻����������
void init_stTree();                                       //��ʼ��ȫ�ֱ���
void Inorder_Thr(PTREENODE *node);                        //����������������
void InPreorder_Thr(PTREENODE *node);                     //����������������
void InLastorder_Thr(PTREENODE *node);                    //����������������

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

//ƾ���ַ������첻����������,��ʶ������������ϵͳ�ĳ�ʼ��
void init_tree(PTREENODE *node, char *ctree, int *count)
{
    //���ַ�Ϊ'#'��ýڵ�Ϊ��
    if (ctree[*count] != '#')
    {
        //�ռ����ʧ���˳�
        if (!(*node = (PTREENODE)malloc(sizeof(TREENODE))))
        {
            exit(-1); //�ռ������˳�����
        }
        (*node)->data = ctree[*count];             //Ϊ�ڵ�ֵ��ֵ
        (*count)++;                                //�ַ�������ƶ�
        init_tree(&(*node)->lchild, ctree, count); //���򴴽�������
        init_tree(&(*node)->rchild, ctree, count); //���򴴽�������
    }
    else
    {
        (*count)++;   //Ϊ���ַ�������ƶ�һλ
        *node = NULL; //�ڵ㸳��
    }
}
//��ʼ��ȫ�ֱ���
void init_stTree()
{
    TREENODE a;
    stTree = NULL;
    stTree2 = &a;
}
//����������������
void Inorder_Thr(PTREENODE *node)
{
    //stTree��stTree(ΪstTree������ָ��)��ֵΪNULL����stTreeָ��ǰ��
    if (*node)
    {
        Inorder_Thr(&(*node)->lchild); //�������������
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
        stTree = *node;                //��stTreeָ��ǰ��
        stTree2 = stTree->rchild;      //ָ��stTree������λ��
        Inorder_Thr(&(*node)->rchild); //�������������
    }
}
//����������������
void InPreorder_Thr(PTREENODE *node)
{
    //stTree��stTree(ΪstTree������ָ��)��ֵΪNULL����stTreeָ��ǰ��
    if (*node) //�ڵ��Ƿ�Ϊ���ж�
    {
        PTREENODE left = (*node)->lchild; //��Ž�Ҫ���޸�������
        if ((*node)->lchild)              //��ָ���Ƿ�Ϊ���ж�
        {
            (*node)->ltag = 0;
        }
        else
        {
            (*node)->ltag = 1;
            (*node)->lchild = stTree; //��ǰ����ֵ���յ���ָ��
        }
        if (stTree2) //ǰ����ָ��ǿ�
        {
            if (stTree) //��ǰ���ǿգ���Ҫ�Ƿ�ֹ��һ���жϳ���
                stTree->rtag = 0;
        }
        else
        {
            stTree->rtag = 1;
            stTree->rchild = *node;
        }
        stTree = *node;           //��stTreeָ��ǰ��
        stTree2 = stTree->rchild; //ָ��stTree������λ��
        InPreorder_Thr(&left);
        InPreorder_Thr(&(*node)->rchild);
    }
}
//����������������
void InLastorder_Thr(PTREENODE *node)
{
    if (*node)
    {
        InLastorder_Thr(&(*node)->lchild);
        InLastorder_Thr(&(*node)->rchild);
        if ((*node)->lchild) //��ָ���Ƿ�Ϊ���ж�
        {
            (*node)->ltag = 0;
        }
        else
        {
            (*node)->ltag = 1;
            (*node)->lchild = stTree; //��ǰ����ֵ���յ���ָ��
        }
        if (stTree2) //ǰ����ָ��ǿ�
        {
            if (stTree) //��ǰ���ǿգ���Ҫ�Ƿ�ֹ��һ���жϳ���
                stTree->rtag = 0;
        }
        else
        {
            stTree->rtag = 1;
            stTree->rchild = *node;
        }
        stTree = *node;           //��stTreeָ��ǰ��
        stTree2 = stTree->rchild; //ָ��stTree������λ��
    }
}