#include <stdio.h>
//#include "game.h"
#include<stdlib.h>
#include<time.h>
#define ROW 9
#define COL 9
#define ROWS ROW+2
#define COLS COL+2
void menu()
{
    printf("*******************\n");
    printf("*******1.开始******\n");
    printf("*******0.退出******\n");
    printf("*******************\n");

}
void InitBoard(char arr[ROWS][COLS],int rows,int cols,char set)
{
    int i = 0;
    
    for (i=0;i<ROWS;i++)
    {
        int j=0;
        for(j=0;j<COLS;j++)
        {
            arr[i][j]=set;
        }
    }
}
void DisplayBoard(char arr[ROWS][COLS],int rows, int cols)
{
    for(int i=0;i<=rows;i++)
    {
        printf("%d ",i);
    }
    printf("\n");
    for(int i=1;i<ROWS-1;i++)
    {
        printf("%d ", i);
        int j=0;
        for(j=1;j<COLS-1;j++)
        {
            printf("%c ",arr[i][j]);
        }
        printf("\n");
    }
}
void Setmine(char arr[ROWS][COLS],int rows, int cols)
{
    int count = 10;
    while(count)
    {
        //布置雷
        //布置好一个，count--
        int x = rand()%rows+1;
        int y = rand()%cols+1;
        if(arr[x][y]=='0')
        {
            arr[x][y] = '1';
            count--;
        }
    }
}
int GetMineCount(char mine[ROWS][COLS],int x,int y)
{
    int count = 0;
    count = mine[x-1][y]+mine[x-1][y-1]+mine[x][y-1]+mine[x+1][y-1]+mine[x+1][y]+mine[x+1][y+1]+mine[x][y+1]+mine[x-1][y+1]-8*'0';
    return count;
}
void FindMine(char mine[ROWS][COLS],char show[ROWS][COLS],int row,int col)
{
    int x=0;
    int y=0;
    int win=0;
    while(win<row*col-10)
    {
        printf("请输入要排查的坐标");
        scanf("%d %d",&x,&y);
        if(x>=1&&x<=row&&y>=1&&y<=col)
        {
            if(mine[x][y]=='1')
            {
                printf("很遗憾，你被炸死了\n");
                DisplayBoard(mine, ROW, COL);
                break;
            }
            else
            {
                //不是雷，统计坐标周围有几个雷
                int n = GetMineCount(mine,x,y);
                show[x][y]=n+'0';
                DisplayBoard(show, ROW, COL);
                win++;
            }
        }
        else
        {
            printf("非法坐标\n");
        }
    }
    if(win==row*col-10)
    {
        printf("恭喜你，扫雷高手\n");
    }
    
}


void game()
{
    char mine[ROWS][COLS];
    char show[ROWS][COLS];
    //初始化棋盘
    InitBoard(mine, ROWS, COLS,'0');
    InitBoard(show, ROWS, COLS,'*');
    DisplayBoard(show,ROW,COL);
    //放雷
    Setmine(mine, ROW,COL);
//    DisplayBoard(mine,ROW,COL);

    //排查雷
    FindMine(mine,show,ROW,COL);
//    System('clc');
}

int main(int argc, const char * argv[]) {
    int input = 0;
    srand((unsigned int)time(NULL));
    do {
        menu();
        printf("请输入");
        scanf("%d",&input);
        switch(input)
        {
            case 1:
                printf("扫雷\n");
                game();
                break;
            case 0:
                printf("退出游戏\n");
                break;
            default:
                printf("错误值\n");
                break;
        }
    } while (input);
}
