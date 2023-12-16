#include<stdio.h>
#include<string.h>
int BFM(char ch1[],char ch2[])      //暴力匹配
{
    int i=0,j=0;
    while(i<strlen(ch1)&&j<strlen(ch2))
    {
        if(ch1[i]==ch2[j])
        {
            j++;
            i++;
        }
        else
        {
            i=i-j+1;
            j=0;
        }
    }
    if(j==strlen(ch2))
    {
        return i-j;
    }
    else
    return 0;
}

int main()
{
    char str1[100];
    char str2[100];
    gets(str1);
    printf("enter another string\n");
    gets(str2);
    int n = BFM(str1,str2);
    printf("%d",n+1);
}