#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int num)
{
    stack[++top] = num;
}

int pop()
{
    return stack[top--];
}

int main()
{
    char postfix[MAX];

    printf("Enter postfix expression: ");
    scanf("%99s", postfix);

    for (int i = 0; i < strlen(postfix); i++)
    {
        // If it is a number
        if (isdigit(postfix[i]))
        {
            int num = 0;

            while (isdigit(postfix[i]))
            {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }

            push(num);
        }

        // '#' means end of number
        else if (postfix[i] == '#')
        {
            continue;
        }

        // Operator
        else
        {
            int b = pop();
            int a = pop();

            int result;

            if (postfix[i] == '+')
            {
                result = a + b;
            }
            else if (postfix[i] == '-')
            {
                result = a - b;
            }
            else if (postfix[i] == '*')
            {
                result = a * b;
            }
            else if (postfix[i] == '/')
            {
                result = a / b;
            }

            push(result);
        }
    }

    printf("Result = %d\n", pop());

    return 0;
}
