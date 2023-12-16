#include<iostream>
using namespace std;
const char oper[7] = { '+', '-', '*', '/', '(', ')', '#' };

#define OK 1
#define ERROR 0
#define OVERFLOW -2

typedef char SElemType;
typedef int Status;


//链栈的存储结构
typedef struct SNode
{
    int data;
    struct SNode *next;
} SNode, *LinkStack;


//链栈的初始化
Status InitStack(LinkStack &S)
{//构造一个空栈，栈顶指针置空
    S = NULL;
    return OK;
}
bool StackEmpty(LinkStack S)
{
    if (!S)
        return true;
    return false;
}


//链栈的入栈
Status Push(LinkStack &S, SElemType e)
{//在栈顶插入元素e
    SNode *p = new SNode;
    if (!p) {
        return OVERFLOW;
    }
    p->data = e;
    p->next = S;
    S = p;
    return OK;
}


//链栈的出栈
Status Pop(LinkStack &S, SElemType &e)
{//删除S的栈顶元素，用e返回其值
    SNode *p;
    if (!S)
        return ERROR;        //栈空
    e = S->data;        //将栈顶元素赋给元素e
    p = S;    //用p临时保存栈顶元素空间，以备释放
    S = S->next;        //修改栈顶指针
    delete p;    //释放原栈顶元素的空间
    return OK;
}


//取出链栈的栈顶元素
Status GetTop(LinkStack &S)
{//返回S的栈顶元素，不修改栈顶指针
    if (!S)
        return ERROR;        //栈非空

    return S->data;    //返回栈顶元素的值，栈顶指针不变
}
bool In(char ch)
{//判断ch是否为运算符
    for (int i = 0; i < 7; i++) {
        if (ch == oper[i]) {
            return true;
        }
    }
    return false;
}



char Precede(char theta1, char theta2)
{//判断运算符优先级
    if ((theta1 == '(' && theta2 == ')') || (theta1 == '#' && theta2 == '#'))
    {
        return '=';
    }
    else if (theta1 == '(' || theta1 == '#' || theta2 == '(' || (theta1
            == '+' || theta1 == '-') && (theta2 == '*' || theta2 == '/'))
    {
        return '<';
    }
    else
        return '>';
}



char Operate(char first, char theta, char second)
{//计算两数运算结果
    switch (theta)
    {
    case '+':
        return (first - '0') + (second - '0') + 48;
    case '-':
        return (first - '0') - (second - '0') + 48;
    case '*':
        return (first - '0') * (second - '0') + 48;
    case '/':
        return (first - '0') / (second - '0') + 48;
    }
    return 0;
}


//算法3.22　表达式求值
char EvaluateExpression()
{//算术表达式求值的算符优先算法，设OPTR和OPND分别为运算符栈和操作数栈
    LinkStack OPTR, OPND;
    char ch, theta, a, b, x, top;
    InitStack(OPND); //初始化OPND栈
    InitStack(OPTR); //初始化OPTR栈
    Push(OPTR, '#'); //将表达式起始符“#”压入OPTR栈
    cin >> ch;
    while (ch != '#' || (GetTop(OPTR) != '#')) //表达式没有扫描完毕或OPTR的栈顶元素不为“#”
    {
        if (!In(ch)) {
            Push(OPND, ch);
            cin >> ch;
        } //ch不是运算符则进OPND栈
        else
            switch (Precede(GetTop(OPTR), ch)) //比较OPTR的栈顶元素和ch的优先级
            {
            case '<':
                Push(OPTR, ch);
                cin >> ch; //当前字符ch压入OPTR栈，读入下一字符ch
                break;
            case '>':
                Pop(OPTR, theta); //弹出OPTR栈顶的运算符
                Pop(OPND, b);
                Pop(OPND, a); //弹出OPND栈顶的两个运算数
                Push(OPND, Operate(a, theta, b)); //将运算结果压入OPND栈
                break;
            case '=': //OPTR的栈顶元素是 “(” 并且ch是 “)”
                Pop(OPTR, x);
                cin >> ch; //弹出OPTR栈顶的 “(” ，读入下一字符ch
                break;
            } //switch
    } //while
    return GetTop(OPND); //OPND栈顶元素即为表达式求值结果
}
int menu() {
    int c;
    cout << "\n\t 多项式计算\n" << endl;
    cout << "\t---------------------" << endl;
    cout << "\t       1.计算" << endl;
    cout << "\t       0.退出" << endl;
    cout << "\t---------------------" << endl;
    cout << "请选择：";
    cin >> c;
    return c;
}

int main() {
    while (1) {
        switch (menu()) {
        case 1: {
            cout << "请输入要计算的表达式（操作数和结果都在0-9的范围内，以#结束）：\n" << endl;
            char res = EvaluateExpression();//算法3.22　表达式求值
            cout << "\n计算结果为:" << res - 48 << endl << endl;
        }
            break;
        case 0:
            cout << "退出成功\n" << endl;
            exit(0);
        default:
            break;
        }
        system("pause");
        //system("cls");
    }
}

