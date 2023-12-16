#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MAX_DIGITS 4
#define MAX_TMP 10000
#define MAX_NODE 100
int a = 0;
//定义二叉树
typedef struct BiTNode{
    char data;
    struct BiTNode *lchild,*rchild;
}BitNode,*BiTree;


//定义所需栈
typedef struct StackNode{
    BitNode *data;
    struct StackNode *next;
}StackNode;

typedef struct Stack{
    StackNode *top;
}*LinkStack;


//创建栈
LinkStack createStack() {
    LinkStack stack = (LinkStack)malloc(sizeof(LinkStack));
    stack->top = NULL;
    return stack;
}

//判断空
int isStackEmpty(Stack* stack) {
    return (stack->top == NULL);
}

//将二叉树放入栈
void push(LinkStack stack, BitNode *node) {
    StackNode* stackNode = (StackNode*)malloc(sizeof(StackNode));
    stackNode->data = node;
    stackNode->next = stack->top;
    stack->top = stackNode;
}


BitNode* pop(LinkStack stack) {
    if (isStackEmpty(stack)) {
        printf("Stack underflow\n");
        return NULL;
    }
    StackNode* stackNode = stack->top;
    BitNode* node = stackNode->data;
    stack->top = stackNode->next;
    free(stackNode);
    return node;
}


//创建二叉树
void CreateBiTree(BiTree &T)
{
    char data;
    scanf(" %c",&data);
    if(data=='#') T=NULL;
    else
    {
        T=(BitNode*)malloc(sizeof(BitNode));
        T->data=data;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

//中序遍历
void recinorderTraversal(BiTree T)
{
    if(T)
    {
        recinorderTraversal(T->lchild);
        printf("%c ",T->data);
        recinorderTraversal(T->rchild);
    }
}

//后序遍历
void recpostorderTraversal(BiTree T)
{
    if(T)
    {
        recpostorderTraversal(T->lchild);
        recpostorderTraversal(T->rchild);
        printf("%c ",T->data);
    }
}

//前序遍历
void recpreorderTraversal(BiTree T)
{
    if(T)
    {
        printf("%c ",T->data);
        recpreorderTraversal(T->lchild);
        recpreorderTraversal(T->rchild);
    }
}

//非递归遍历算法
void inorderTraversal(BiTree T) {
    if (T == NULL) {
        return;
    }
    Stack* stack = createStack();
    BiTree current = T;
    while (current != NULL || !isStackEmpty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->lchild;
        }
        current = pop(stack);
        printf("%c ", current->data);
        current = current->rchild;
    }
    free(stack);
}
//计算节点数
int Count(BiTree T)
{
    if(T==NULL) return 0;
    else return Count(T->lchild)+Count(T->rchild)+1;
}
//计算深度
int TreeDepth(BiTree T)
{
    int m,n;
    if(T==NULL) return 0;
    else
    {
        m=TreeDepth(T->lchild);
        n=TreeDepth(T->rchild);
        return 1+(m>n?m:n);
    }
}
//计算叶子数
int countLeaves(BiTree T) {
    if (T == NULL) {
        return 0;
    }
    if (T->lchild == NULL && T->rchild == NULL) {
        return 1;
    }
    return countLeaves(T->lchild) + countLeaves(T->rchild);
}

int BreakTree(BiTree &T,BiTree &L,BiTree &R)
{
    if(T == NULL) return -1;
    L=T->lchild;
    R=T->rchild;
    
    return 0;
}
void saveInTraversal(BiTree root,int *term)
{
    if(!root)
        return;
    else
    {
        saveInTraversal(root->lchild,term);
        term[a++]=root->data;
        saveInTraversal(root->rchild,term);
    }
}
int count(BiTree T,int num)
{
    if(!T)
        return num;
    else
    {
        num=count(T->lchild,num);
        num=count(T->rchild,num);
    }
    num++;
    return num;
}
int findNum(int *term, int x, int n)
{
    for(int i=0;i<n;i++)
        if(term[i]==x)
            return i+1;
    return -1;
}

int digits(int x)
{
    int num=0;
    while(x!=0)
    {
        x/=10;
        num++;
    }
    return num;
}

void display(BiTree root)
{
    int absotiveDistance[2];//绝对距离，[1]表示上一个兄弟节点，[0]-[1]用于计算节点的相对距离
    int array[MAX_NODE]={0};//用于储存搜索二叉树的中序遍历序列
    int relativeDistance=0;//相对距离
    
    //定义标志节点N，节点的子孩子为空时用于占位识别
    BiTree N;
    N=(BiTree)malloc(sizeof(BitNode));
    N->data=-1;
    N->lchild=NULL;
    N->rchild=NULL;

    int deep=TreeDepth(root);
    saveInTraversal(root, array);

    //临时变量，用于层序遍历
    int k=0;
    int j=1;
    int n=1;

    BiTree term[MAX_NODE]={NULL};//指针数组，储存树节点，用于层序遍历
    term[0]=root;
    while(n!=deep+1)    //层序遍历
    {
        absotiveDistance[0]=0;
        absotiveDistance[1]=0;
        if(term[k]->lchild!=NULL&&term[k]->lchild!=N)   //左节点不为空或#
            term[j++]=term[k]->lchild;
        else
            term[j++]=N;
        if(term[k]->rchild!=NULL&&term[k]->rchild!=N)   //右节点不为空或#
            term[j++]=term[k]->rchild;
        else
            term[j++]=N;
        k++;
        if(k==pow(2,n)-1)
        {
            for(int i=pow(2,n-1)-1;i<k;i++)
            {
                absotiveDistance[0]=findNum(array, term[i]->data, count(root, 0))*MAX_DIGITS;
                if(absotiveDistance[0]==-MAX_DIGITS)
                    continue;
                relativeDistance=absotiveDistance[0]-absotiveDistance[1];

                absotiveDistance[0]+=digits(term[i]->data)+2;

                absotiveDistance[1]=absotiveDistance[0];
                for(int m=0;m<relativeDistance;m++)
                {
                    printf(" ");
                }
                if(term[i]!=N)
                {
                    printf("%c",term[i]->data);
                }
            }
            printf("\n");
            printf("\n");
            n++;
        }
    }
}

int main()
{
    BiTree T;
    CreateBiTree(T);
    display(T);
    inorderTraversal(T);
    printf("\n");
    recinorderTraversal(T);
    printf("\n");
    recpreorderTraversal(T);
    printf("\n");
    recpostorderTraversal(T);
    printf("\n");
    printf("节点数%d\n",Count(T));
    printf("子节点数%d\n",count(T, 0));
    printf("深度是%d\n",TreeDepth(T));
    printf("叶子数是%d\n",countLeaves(T));
    return 0;
}
