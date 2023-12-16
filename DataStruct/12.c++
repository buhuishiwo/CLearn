#include <stdio.h> 
#include <string.h>
#define MAXLEN 255
typedef struct
{
    char ch[MAXLEN + 1];
    int length;
} SString;

void Enter(SString &s)
{
    char newchar[MAXLEN + 1];
    printf("输入字符串\n");
    scanf("%s", newchar);
    s.length = strlen(newchar);
    strcpy(s.ch, newchar);
}
void getNext(SString s, int *next)
{
    int n = s.length;
    int k = -1, j = 0;
    next[0] = -1;
    while (j < n - 1)
    {
        if (k == -1 || s.ch[j] == s.ch[k])
        {
            ++k;
            ++j;
            if (s.ch[j] != s.ch[k])
            {
                next[j] = k;
            }
            else
            {
                next[j] = next[k];
            }
        }
        else
        {
            k = next[k];
        }
    }
}

int kmp(SString s, SString t)
{
    int m = s.length;
    int n = t.length;
    int i = 0, j = 0;
    int next[n];
    getNext(s, next);
    while (i < m && j < n)
    {
        if (j == -1 || s.ch[i] == s.ch[j])
        {
            ++i;
            ++j;
        }
        else
        {
            j = next[j];
        }
    }
    return (j == n) ? i - j : -1;
}

int main()
{
    SString s;
    SString t;
    Enter(s);
    Enter(t);
    printf("%d\n", kmp(s, t)); // Output: 15 return 0; 
}