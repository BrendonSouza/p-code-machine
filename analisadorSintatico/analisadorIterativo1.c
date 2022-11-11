#include <stdio.h>
#include <string.h>
#define STACKSIZE 1000

char stack[STACKSIZE];
int top = -1;

void push(char c)
{
    if (top < STACKSIZE)
    {
        stack[++top] = c;
    }
}

void pop()
{
    if (top >= 0)
    {
        top--;
    }
}

int main(int argc, char *argv[])
{
    int posicao = 0;
    char token;

    FILE *fp;
    char *word = NULL;
    char linha[100];
    size_t len = 100;
    ssize_t read;

    fp = fopen(argv[1], "r");
    // for ate o final de argv
    if (fp == NULL)
        return 1;

    while (!feof(fp))
    {

        word = fgets(linha, len, fp);
    }

q0:
    push('S');
    goto q1;
q1:
    token = word[posicao];
    printf("token == %c\n", token);
    printf("stackTop == %c\n", stack[top]);

// ! p1: S → M
    if ((token == 'M') && (stack[top] == 'S'))
    {
        pop();
        push('M');
        goto q1;
    }
    // p2: S -> G M
    else if ((token == 'G') && (stack[top] == 'S'))
    {
        pop();
        push('M');
        push('G');
        goto q1;
    }
    //p3: S -> F G M
    else if ((token == 'F') && (stack[top] == 'S'))
    {
        pop();
        push('M');
        push('G');
        push('F');
        goto q1;
    }
    //p4: F → f(){ C; r(E); }
    else if ((token == 'f') && (stack[top] == 'F'))
    {
        pop();
        push(';');
        push(')');
        push('E');
        push('(');
        push('r');
        push(';');
        push('C');
        push('{');
        push(')');
        push('(');
        push('f');
        goto q1;
    }
    // p5: G → g(){ C; r(E); }
    else if ((token == 'g') && (stack[top] == 'G'))
    {
        pop();
        push(';');
        push(')');
        push('E');
        push('())');
        push('r');
        push(';');
        push('C');
        push('{');
        push(')');
        push('(');
        push('g');
        goto q1;
    }
    // p6: M → m(){ C; r(E); }
    else if ((token == 'm') && (stack[top] == 'M'))
    {
        pop();
        
        push(')');
        push('C');
        push(';');
        push('E');
        push('r');
        push('(');
        push('{');
        push('m');
        goto q1;
    }

    // else if ((token == '(')&&(stack[top]=='S')) { pop(); push(')'); push('S'); push('X');push('S');push('('); goto q1; }
    // else if ((token == '+')&&(stack[top]=='X')) { pop(); push('+'); goto q1; }
    // else if ((token == '-')&&(stack[top]=='X')) { pop(); push('-'); goto q1; }
    // else if ((token == '*')&&(stack[top]=='X')) { pop(); push('*'); goto q1; }
    // else if ((token == '/')&&(stack[top]=='X')) { pop(); push('/'); goto q1;}
    // else if ((token == '(')&&(stack[top]=='(')) { pop(); posicao++;goto q1;}
    // else if ((token == ')')&&(stack[top]==')')) { pop();posicao++;goto q1; }
    // else if ((token == '+')&&(stack[top]=='+')) { pop();posicao++;goto q1; }
    // else if ((token == '-')&&(stack[top]=='-')) { pop();posicao++;goto q1;  }
    // else if ((token == '*')&&(stack[top]=='*')) { pop();posicao++;goto q1; }
    // else if ((token == '/')&&(stack[top]=='/')) { pop();posicao++;goto q1; }
    // else if ((token == '0')&&(stack[top]=='0')) { pop();posicao++;goto q1; }
    // else if ((token == '1')&&(stack[top]=='1')) { pop();posicao++;goto q1;  }
    else if (stack[top] == '\0' && token == '\0')
    {
        printf("palavra consumida");
    }
    else
    {
        printf("erro\n\n");
        printf("token == %c\n", token);
        printf("stackTop == %c\n", stack[top]);
        printf("stack == %s\n", stack);
        return 1;
    }
}