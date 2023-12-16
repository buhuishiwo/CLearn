#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
}Node,*Linklist;

void InitList(Linklist L, int x)
{
 for (int i = 0; i < x; i++)
 {
  Linklist p = (Linklist)malloc(sizeof(Node));
  printf("enter data\n");
  scanf("%d", &p->data);
  p->next = L->next;
  L->next = p;
 }
}

Linklist SortedMerge(Linklist a, Linklist b) {
    struct Node* result = NULL;

    if (a == NULL)
        return(b);
    else if (b==NULL)
        return(a);

    if (a->data < b->data) {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return(result);
}

void printList(Linklist node) {
    while (node!=NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main() {
    struct Node* res = NULL;
    struct Node* a = NULL;
    struct Node* b = NULL;

    InitList(a,3);
    InitList(b,3);

    res = SortedMerge(a, b);

    printf("Merged Linked List is: \n");
    printList(res);

    return 0;
}