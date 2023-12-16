#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
#define OVERFLOW -2

typedef struct 
{
	int *base;
	int *top;
	int stacksize;
}sqstack;

void InitStack(sqstack &s)
{
	s.base=(int*)malloc(MAXSIZE);
	s.top=s.base;
	s.stacksize=MAXSIZE;
}

void Push(sqstack &s,int e)
{
	if(s.top-s.base==s.stacksize) exit(-1);
	*s.top++=e;
}

void Pop(sqstack &s,int &e){
    if(s.top==s.base) exit(1);
	e=*--s.top;         
}



void GetTop(sqstack s)
{
	if(s.top!=s.base)
	{
		printf("%d",*(s.top-1));
	}
}

int main()
{
	sqstack s;
	InitStack(s);
	int e=2;
	for(int i=10;i<20;i++)
	{
		Push(s,i);	
	}
    Pop(s,e);
    printf("%d",e);
	GetTop(s);
}