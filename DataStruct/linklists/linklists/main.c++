#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
}Node,*Linklist;

typedef struct SNode{
    int data;
    struct SNode* llink;
    struct SNode* rlink;
}*LinkedList;

void InitList(Linklist &L, int x)
{
    Linklist r;//创建尾指针
    r=L;//指向头节点
    for(int i=0;i<x;i++)
    {
        Linklist p=new Node;//开辟空间，p为节点
        printf("请输入第%d个数字\n",i+1);
        scanf("%d",&p->data);//别忘取&
        //
        p->next=NULL;
        r->next=p;//将新节点插入r之后
        r=p;//r指向新的尾节点
    }
}



int Max (Linklist L ){
    if(L->next==NULL) return NULL;
    Linklist pmax=L->next;        //假定第一个结点中数据具有最大值
    Linklist p=L->next->next;
    while(p != NULL ){   //如果下一个结点存在
        if(p->data > pmax->data) pmax=p;       //如果p的值大于pmax的值，则重新赋值
        p=p->next;                             //遍历链表
    }
    return pmax->data;
}
void  inverse(Linklist &L)
{                             // 逆置带头结点的单链表 L
    Linklist p=L->next;
    Linklist q;
    L->next=NULL;
    while ( p) {
        q=p->next;            // q指向*p的后继
        p->next=L->next;
        L->next=p;            // *p插入在头结点之后
        p = q;
    }
}
void Delete(Linklist &L, int mink, int maxk) {
    Linklist p=L->next; //首元结点
    Linklist pre = nullptr;
    Linklist q;
    Linklist s;
    while (p && p->data<=mink)
    {
        pre=p;
        p=p->next;
    }             //查找第一个值>mink的结点
    if (p)
    {
        while (p && p->data<maxk)  {
            p=p->next;   // 查找第一个值 ≥maxk的结点
            q=pre->next;
            pre->next=p;        // 修改指针
            while (q!=p)
            {
                s=q->next;  delete q;  q=s;
            } // 释放结点空间
        }//if
    }
}
void  Exchange(LinkedList p)

{
    LinkedList q=p->llink;
    q->llink->rlink=p;
    p->llink=q->llink;
    q->rlink=p->rlink;
    q->llink=p;
    p->rlink->llink=q;
    p->rlink=q;
}

void printList(Linklist node) {
    while (node->next!=NULL) {
        node = node->next;
        printf("%d ", node->data);
        
    }
}

int main() {
    Linklist res = NULL;
    Linklist a = NULL;
    Linklist b = NULL;
    a=(Linklist)malloc(sizeof(Node));
    b=(Linklist)malloc(sizeof(Node));
    res=(Linklist)malloc(sizeof(Node));
    a->next=NULL;
    b->next=NULL;
    res->next=NULL;
    InitList(a,10);
//    InitList(b,3);
    int n=0;
//    printf("%d\n",Max(a));
//    Max(a);
//    printf("%d",n);
//    printf("Merged Linked List is: \n");
//    printList(res);
//    printList(b);
//    inverse(a);
//    printList(a);
    Delete(a,4,6);
    printList(a);
    return 0;
}
