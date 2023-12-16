#include <stdio.h>
#include<string.h>
void getNext(char *p, int *next)
{
    int j = 0;
    next[0] = 0; // 第一个字符没有前后缀
    for (int i = 1; i < strlen(p); i++)
    {
        while (j > 0 && p[i] != p[j])
        {
            j = next[j - 1];
        }
        if (p[i] == p[j])
        {
            j++;
        }
        next[i] = j;
    }
}

int kmp(char s[], char t[])
{
    int j = 0;
    int n = strlen(t);
    int next[n];
    getNext(t, next);
    for (int i = 0; i < strlen(s); i++)
    {
        while (j > 0 && s[i] != t[j])
        {
            j = next[j - 1];
        }
        if(s[i]==t[j])
        {
            j++;
        }
        if (j == strlen(t))
        {
            return i - j+1;
        }
    }
    return -1;
}

int main()
{
    char s[10];
    scanf("%s",s);
    char t[10];
    scanf("%s",t);
    getchar();
    printf("%d\n", kmp(s, t) + 1);
    return 0;
}