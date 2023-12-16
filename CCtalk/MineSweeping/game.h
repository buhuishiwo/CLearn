//
//  game.h
//  MineSweeping
//
//  Created by 陈伟 on 2023/10/29.
//

#include<stdio.h>
#include<stdlib.h>
#ifndef game_h
#define game_h

#include <stdio.h>
#define ROW 9
#define COL 9
#define ROWS ROW+2
#define COLS COL+2

void InitBoard(char arr[ROWS][COLS],int rows,int cols,char set);
void DisplayBoard(char arr[ROWS][COLS],int rows, int cols);
void Setmine(char arr[ROWS][COLS],int rows, int cols);
void FindMine(char mine[ROWS][COLS],char show[ROWS][COLS],int row,int col);
int GetMineCount(char mine[ROWS][COLS],int x,int y);
#endif /* game_h */
