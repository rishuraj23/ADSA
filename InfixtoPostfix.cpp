#include <stdio.h>
#include <ctype.h>

#define MAX 100

// STACK FOR INFIX TO POSTFIX


char Stack[MAX];
int top = -1;

void push(char ch)
{
    Stack[++top] = ch;
}

char pop()
{
    return Stack[top--];
}

char peek()
{
    return Stack[top];
}


int precedence(char op)
{
    if (op == '*' || op == '/')
        return 2;

    if (op == '+' || op == '-')
        return 1;

    return 0;
}



int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}


// INFIX TO POSTFIX


void infixToPostfix(char infix[], char postfix[], int n)
{
    int j = 0;

    for (int i = 0; i < n; i++)
    {
        // Operand
        if (isdigit(infix[i]))
        {
            postfix[j++] = infix[i];
        }

        // Opening parenthesis
        else if (infix[i] == '(')
        {
            push(infix[i]);
        }

        // Closing parenthesis
        else if (infix[i] == ')')
        {
            while (top != -1 && peek() != '(')
            {
                postfix[j++] = pop();
            }

            if (top != -1 && peek() == '(')
            {
                pop();
            }
        }

        // Operator
        else if (isOperator(infix[i]))
        {
            while (top != -1 &&
                   peek() != '(' &&
                   precedence(peek()) >= precedence(infix[i]))
            {
                postfix[j++] = pop();
            }

            push(infix[i]);
        }
    }

    // Pop remaining operators
    while (top != -1)
    {
        postfix[j++] = pop();
    }

    // VERY IMPORTANT
    postfix[j] = '\0';
}



// STACK FOR POSTFIX EVALUATION

int Stackvalue[MAX];
int valueTop = -1;

void pushValue(int value)
{
    Stackvalue[++valueTop] = value;
}

int popValue()
{
    return Stackvalue[valueTop--];
}



// POSTFIX EVALUATION


int Postfixevaluate(char postfix[])
{
    int i = 0;

    while (postfix[i] != '\0')
    {
        // Operand
        if (isdigit(postfix[i]))
        {
            int value = postfix[i] - '0';

            pushValue(value);
        }

        // Operator
        else if (isOperator(postfix[i]))
        {
            int b = popValue();
            int a = popValue();

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
            else
            {
                result = a / b;
            }

            pushValue(result);
        }

        i++;
    }

    return popValue();
}




int main()
{
    int n;

    printf("Enter the infix expression size: ");
    scanf("%d", &n);

    char infix[MAX];
    char postfix[MAX];

    printf("Enter the expression: ");

    getchar();

    for (int i = 0; i < n; i++)
    {
        scanf("%c", &infix[i]);
    }

    // Convert
    infixToPostfix(infix, postfix, n);

    printf("\nPostfix expression: %s\n", postfix);

    // Evaluate
    int result = Postfixevaluate(postfix);

    printf("Result = %d\n", result);

    return 0;
}
