#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "LinkStack.h"

int isNumber(char c)
{
    return ('0' <= c) && (c <= '9');
}

int isOperator(char c)
{
    return (c == '+') || (c == '-') || (c == '*') || (c == '/');
}

unsigned long long value(char c)
{
    return (c - '0');
}

unsigned long long express(unsigned long long left, unsigned long long right, char op)
{
    unsigned long long ret = 0;

    switch (op)
    {
    case '+':
        ret = left + right;
        break;
    case '-':
        ret = left - right;
        break;
    case '*':
        ret = left * right;
        break;
    case '/':
        ret = left / right;
        break;
    default:
        break;
    }

    return ret;
}

unsigned long long compute(const char *exp)
{
    LinkStack *stack = LinkStack_Create();
    unsigned long long ret = 0;
    int i = 0;

    while (exp[i] != '\0')
    {
        if (isNumber(exp[i]))
        {
            LinkStack_Push(stack, (void *)value(exp[i]));
        }
        else if (isOperator(exp[i]))
        {
            unsigned long long right = (unsigned long long)LinkStack_Pop(stack);
            unsigned long long left = (unsigned long long)LinkStack_Pop(stack);
            unsigned long long result = express(left, right, exp[i]);

            LinkStack_Push(stack, (void *)result);
        }
        else
        {
            printf("Invalid expression!");
            break;
        }

        i++;
    }

    if ((LinkStack_Size(stack) == 1) && (exp[i] == '\0'))
    {
        ret = (unsigned long long)LinkStack_Pop(stack);
    }
    else
    {
        printf("Invalid expression!");
    }

    LinkStack_Destroy(stack);

    return ret;
}

int main()
{
    printf("9 + (3 - 1) * 5 + 8 / 2 = %lld\n", compute("931-5*+82/+"));

    return 0;
}
