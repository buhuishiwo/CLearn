#include <stdio.h>
#include <string.h>
#define MAXSIZE 100
typedef struct stu
{
	char sno[20];
	char sname[20];
	int grade;
}STUDENT;

typedef struct{
	STUDENT  stu[MAXSIZE];
	int length;
}SqList;

void shuru(SqList  &L)
{
	int n;
	printf("请输入学生数量\n");
	scanf("%d",&n);
	L.length=n;
	for(int i=0;i<L.length;i++)
	{
		printf("学号：");
		scanf("%s",L.stu[i].sno);
		printf("姓名：");
		scanf("%s",L.stu[i].sname);
		printf("成绩：");
		scanf("%d",&L.stu[i].grade);
	}

}

void print(SqList  L)
{
	for(int i=0;i<L.length;i++)
	{
		printf("%s  %s   %d\n",L.stu[i].sno,L.stu[i].sname,L.stu[i].grade);
	}
}


int chazhao(SqList  L,STUDENT x)
{
	for(int i=0;i<L.length;i++)
	{
		if(strcmp(L.stu[i].sname,x.sname)==0)
			return i;
	}
	return -1;
}

void insert(SqList  &L,int i,STUDENT x)
{
	for(int j=L.length-1;j>=i;j--)
	{
		L.stu[j+1]=L.stu[j];
	}
	L.stu[i]=x;
	L.length++;
	
}

void unionList(SqList  &L1,SqList  &L2)
{
	for(int i=0;i<L2.length;i++)
	{
		STUDENT b=L2.stu[i];
		if(chazhao(L1,b)==-1)
			insert(L1,L1.length,b);

	}

}

int main()
{
	SqList L;
	STUDENT x;
	strcpy(x.sname,"li");
	strcpy(x.sno,"04");
	x.grade=100;
	shuru(L);
//	print(L);
//	if(chazhao(L,x)==-1)
//		printf("no student\n");
//	else
		//	printf("have student\n");

	insert(L,0,x);
	print(L);
	return 0;


}