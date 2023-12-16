#include<stdio.h>
#include<stdlib.h>
 
typedef struct StackNode{
    char data;
    struct StackNode *next;
}StackNode,*LinkStack;
 
void InitStack(LinkStack &S){
    S = NULL;
}
 
void Pop(LinkStack &S, char &ch){
    LinkStack p;
    ch=S->data;
    p=S;
    S=S->next;
    free(p);
}
 
void Push(LinkStack &S, char ch){
    LinkStack node = (LinkStack)malloc(sizeof(LinkStack));
    node->data = ch;
    node->next = S;
    S = node;
}
 
char GetTop(LinkStack S){
    return S->data;
}
 
int In(char ch){
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '#'){
        return 1;
    }else{
        return 0;
    }
}
 
char Precede(char a, char b){                    //判断运算符的优先级
    if (a == '+' || a == '-'){
        if (b == '+' || b == '-' || b == ')' || b == '#'){
            return '>';
        }else{
            return '<';
        }
    }else if (a == '*' || a == '/'){
        if (b == '+' || b == '-' || b == '*' || b == '/' || b == ')' || b == '#'){
            return '>';
        }else{
            return '<';
        }
    }else if (a == '('){
        if (b == ')'){
            return '=';
        }else if (b == '#'){                    //表达式错误
            return '?';
        }else{
            return '<';
        }
    }else if (a == '#'){
        if (b == '#'){
            return '=';
        }else if (b == ')'){                    //表达式错误
            return '?';
        }else {
            return '<';
        }
    }
    return 0;
}
 
char Operate(char a, char theta, char b){                   //运算操作
    switch (theta)
    {
    case '+':
        return (a - '0') + (b - '0') + 48;
    case '-':
        return (a - '0') - (b - '0') + 48;
    case '*':
        return (a - '0') * (b - '0') + 48;
    case '/':
        return (a - '0') / (b - '0') + 48;
    }
    return 0;
}
 
char EvaluateExpression(){
    LinkStack OPTR,OPND;
    OPTR = (LinkStack)malloc(sizeof(LinkStack));            //存放运算符
    OPND = (LinkStack)malloc(sizeof(LinkStack));            //存放操作数
    InitStack(OPTR);
    InitStack(OPND);
    Push(OPTR, '#');
    char ch;
    scanf("%c", &ch);
    while(ch != '#' || GetTop(OPTR) != '#'){
        if (!In(ch)){
            Push(OPND, ch);        //将运算符压入 OPND 栈
            scanf("%c", &ch);
        }else{
            switch(Precede(GetTop(OPTR), ch)){
                case '<':
                    Push(OPTR,ch);
                    scanf("%c", &ch);
                    break;
                case '>':
                    char theta,a,b;
                    Pop(OPTR,theta);
                    Pop(OPND,b);
                    Pop(OPND,a);
                    Push(OPND,Operate(a,theta,b));
                    break;
                case '=':
                    char temp;
                    Pop(OPTR,temp);
                    scanf("%c", &ch);
                    break;
                case '?':
                    printf("表达式错误！");
                    return -1;
            }
        }
    }
    return GetTop(OPND);
}
 
int main()
{
    printf("请输入一个表达式(以#结束)：");
    char result = EvaluateExpression();
    printf("%d\n",result-48);           //将字符转换为数字
}
