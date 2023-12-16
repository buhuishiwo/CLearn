#include <stdio.h>
#include <stdlib.h>
 
typedef struct Node
{
    int data;
    struct Node* next;
} LNode, * LinkList;
 
void InitList(LinkList L)
{
    L = (LNode*)malloc(sizeof(LNode));
    L->next = NULL;
}
 
void Append(LinkList L, int d)
{
    LNode* cur;
    cur = L;
    while (cur->next != NULL) cur = cur->next;
    LNode* p = (LinkList)malloc(sizeof(LNode));
    p->data = d;
    cur->next = p;
    p->next = NULL;
}
 
void Pprint(LinkList L)
{
    LinkList cur;
    cur = L->next;
    while (cur != NULL)
    {
        printf("%d\n", cur->data);
        cur = cur->next;
    }
}
 
LinkList ListSort(LinkList L1, LinkList L2)
{
    LNode* p1, * p2, * pre=NULL;
    p1 = L1;
    p2 = L2;
    while (p1 != NULL && p2 != NULL)
    {
        if (p1->data <= p2->data)
        {
            pre = p1;
            p1 = p1->next;
        }
        else
        {
            if (pre != NULL) pre->next = p2;
            pre = p2;
            p2 = p2->next;
            pre->next = p1;
        }
    }
    if (p1 == NULL) pre->next = p2;
    return L1->data >= L2->data ? L1 : L2;
}
 
int main()
{
    LinkList L1;
    InitList(L1);
    Append(L1, 4);
    Append(L1, 9);
    Append(L1, 10);
    LinkList L2;
    InitList(L2);
    Append(L2, 3);
    Append(L2, 5);
    Append(L2, 10);
    Append(L2, 15);
    ListSort(L1, L2);
    L1 = ListSort(L1, L2);
    Pprint(L1);
}