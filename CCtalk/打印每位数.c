#include<stdio.h>

void Print(int n)
{
    if(n>9)
    {
        Print(n/10);
    }
    printf("%d ",n%10);
}
int main()
{
    int n;
    scanf("%d",&n);
    Print(n);
    return 0;
}
