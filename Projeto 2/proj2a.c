#include <stdio.h>
#include <string.h>
#define STACKSIZE 1000

char stack[STACKSIZE];
int top = -1;

int indice0fDad = 0;
char aas[9999999];
int qtdOcorrE;
int qtdOcorrX;


int findIndiceOfDad(char c){
    int qtdOcorr=0;
    for (int i = 0; i < 9999999; i++)
    {
        if (aas[i] == c)
        {
            //verifica se E tem filho
           if(c == 'E'){
            if(i != 21){
                if(aas[i*12+1] == '\0'){
                    return i;
                }

            }

            }
            else if(c == 'X'){
                if(aas[i*12+1] == '\0'){
                    return i;
                }
            }
            else if(c =='C'){
                if(aas[i*12+1] == '\0'){
                    return i;
                }
            }
            else{
                return i;
            }

        }
    }
    return -1;
}

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
    aas[indice0fDad] = 'S';
    goto q1;
q1:
    token = word[posicao];

// ! p1: S → M
    if ((token == 'm') && (stack[top] == 'S'))
    {
        pop();
        push('M');
        indice0fDad = findIndiceOfDad('S')*12+1;
        aas[indice0fDad] = 'M';
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
        push(')');
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
        push('}');
        indice0fDad = findIndiceOfDad('M')*12+12;
        aas[indice0fDad] = '}';  

        push(';');
        indice0fDad = findIndiceOfDad('M')*12+11;
        aas[indice0fDad] = ';';  

        push(')');
        indice0fDad = findIndiceOfDad('M')*12+10;
        aas[indice0fDad] = ')';

        push('E');
        indice0fDad = findIndiceOfDad('M')*12+9;
        aas[indice0fDad] = 'E';  

        push('(');
        indice0fDad = findIndiceOfDad('M')*12+8;
        aas[indice0fDad] = '(';  

        push('r');
        indice0fDad = findIndiceOfDad('M')*12+7;
        aas[indice0fDad] = 'r';  

        push(';');
        indice0fDad = findIndiceOfDad('M')*12+6;
        aas[indice0fDad] = ';';  

        push('C');
        indice0fDad = findIndiceOfDad('M')*12+5;
        aas[indice0fDad] = 'C';  

        push('{');
        indice0fDad = findIndiceOfDad('M')*12+4;
        aas[indice0fDad] = '{'; 

        push(')');
        indice0fDad = findIndiceOfDad('M')*12+3;
        aas[indice0fDad] = ')';  


        push('(');
        indice0fDad = findIndiceOfDad('M')*12+2;
        aas[indice0fDad] = '(';  

        push('m');
        indice0fDad = findIndiceOfDad('M')*12+1;
        aas[indice0fDad] = 'm';
        goto q1;
    }
    //p7 : E → 0 | 1 | x | y | (EXE)
    else if ((token == '0') && (stack[top] == 'E'))
    {
        pop();
        push('0');
        indice0fDad = findIndiceOfDad('E')*12+1;
        aas[indice0fDad] = '0';
        goto q1;
    }
    else if ((token == '1') && (stack[top] == 'E'))
    {
        pop();
        push('1');
        indice0fDad = findIndiceOfDad('E')*12+1;
        aas[indice0fDad] = '1';
        goto q1;
    }
    else if ((token == 'x') && (stack[top] == 'E'))
    {
        pop();
        push('x');
        indice0fDad = findIndiceOfDad('E')*12+1;
        aas[indice0fDad] = 'x';
        goto q1;
    }
    else if ((token == 'y') && (stack[top] == 'E'))
    {
        pop();
        push('y');
        indice0fDad = findIndiceOfDad('E')*12+1;
        aas[indice0fDad] = 'y';
        goto q1;
    }
    //p11: E -> (EXE)
    else if ((token == '(') && (stack[top] == 'E'))
    {
        printf("E->(EXE)");
        pop();
        push(')');
        indice0fDad = findIndiceOfDad('E')*12+5;
        aas[indice0fDad] = ')';

        push('E');
        indice0fDad = findIndiceOfDad('E')*12+4;
        aas[indice0fDad] = 'E';

        push('X');
        indice0fDad = findIndiceOfDad('E')*12+3;
        aas[indice0fDad] = 'X';

        push('E');
        indice0fDad = findIndiceOfDad('E')*12+2;
        aas[indice0fDad] = 'E';
        push('(');
        indice0fDad = findIndiceOfDad('E')*12+1;
        printf("indice0fDad: %d", indice0fDad);
        aas[indice0fDad] = '(';
        goto q1;
    }
    //p:12 X → + | - | * | /
    else if ((token == '+') && (stack[top] == 'X'))
    {
        pop();
        push('+');
        indice0fDad = findIndiceOfDad('X')*12+1;
        aas[indice0fDad] = '+';
        goto q1;
    }
    else if ((token == '-') && (stack[top] == 'X'))
    {
        pop();
        push('-');
        indice0fDad = findIndiceOfDad('X')*12+1;
        aas[indice0fDad] = '-';
        goto q1;
    }
    else if ((token == '*') && (stack[top] == 'X'))
    {
        pop();
        push('*');
        indice0fDad = findIndiceOfDad('X')*12+1;
        aas[indice0fDad] = '*';
        goto q1;
    }
    else if ((token == '/') && (stack[top] == 'X'))
    {
        pop();
        push('/');
        indice0fDad = findIndiceOfDad('X')*12+1;
        aas[indice0fDad] = '/';
        goto q1;
    }

    //p16: C -> h=E | i=E | j=E | k=E | z=E
    else if ((token == 'h') && (stack[top] == 'C'))
    {
        pop();
        push('E');
        indice0fDad = findIndiceOfDad('C')*12+3;
        aas[indice0fDad] = 'E';
        push('=');
        indice0fDad = findIndiceOfDad('C')*12+2;
        aas[indice0fDad] = '=';

        push('h');
        indice0fDad = findIndiceOfDad('C')*12+1;
        aas[indice0fDad] = 'h';
        goto q1;
    }
    else if ((token == 'i') && (stack[top] == 'C'))
    {
        pop();
        push('E');
        push('=');
        push('i');
        goto q1;
    }
    else if ((token == 'j') && (stack[top] == 'C'))
    {
        pop();
        push('E');
        push('=');
        push('j');
        goto q1;
    }
    else if ((token == 'k') && (stack[top] == 'C'))
    {
        pop();
        push('E');
        push('=');
        push('k');
        goto q1;
    }
    else if ((token == 'z') && (stack[top] == 'C'))
    {
        pop();
        push('E');
        push('=');
        push('z');
        goto q1;
    }

    // p21: C -> (EXE)
    else if ((token == '(') && (stack[top] == 'C'))
    {
        pop();
        push(')');
        indice0fDad = findIndiceOfDad('C')*12+5;
        aas[indice0fDad] = ')';

        push('E');
        indice0fDad = findIndiceOfDad('C')*12+4;
        aas[indice0fDad] = 'E';
        push('X');
        indice0fDad = findIndiceOfDad('C')*12+3;
        aas[indice0fDad] = 'X';
        push('E');
        indice0fDad = findIndiceOfDad('C')*12+2;
        aas[indice0fDad] = 'E';
        push('(');
        indice0fDad = findIndiceOfDad('C')*12+1;
        aas[indice0fDad] = '(';
        goto q1;
    }
    //p22: C -> w(E){ C; }
    else if ((token == 'w') && (stack[top] == 'C'))
    {
        pop();
        push('}');
        push(';');
        push('C');
        push('{');
        push(')');
        push('E');
        push('(');
        push('w');
        goto q1;
    }

    // p23:  C -> f(E){ C; }
    else if ((token == 'f') && (stack[top] == 'C'))
    {
        pop();
        push('}');
        push(';');
        push('C');
        push('{');
        push(')');
        push('E');
        push('(');
        push('f');
        goto q1;
    }

    // p24: C -> o(E; E; E){ C; }
    else if ((token == 'o') && (stack[top] == 'C'))
    {
        pop();
        push('}');
        indice0fDad = findIndiceOfDad('C')*12+12;
        aas[indice0fDad] = '}';
        push(';');
        indice0fDad = findIndiceOfDad('C')*12+11;
        aas[indice0fDad] = ';';
        push('C');
        indice0fDad = findIndiceOfDad('C')*12+10;
        aas[indice0fDad] = 'C';
        push('{');
        indice0fDad = findIndiceOfDad('C')*12+9;
        aas[indice0fDad] = '{';
        push(')');
        indice0fDad = findIndiceOfDad('C')*12+8;
        aas[indice0fDad] = ')';
        push('E');
        indice0fDad = findIndiceOfDad('C')*12+7;
        aas[indice0fDad] = 'E';
        push(';');
        indice0fDad = findIndiceOfDad('C')*12+6;
        aas[indice0fDad] = ';';
        push('E');
        indice0fDad = findIndiceOfDad('C')*12+5;
        aas[indice0fDad] = 'E';
        push(';');
        indice0fDad = findIndiceOfDad('C')*12+4;
        aas[indice0fDad] = ';';
        push('E');
        indice0fDad = findIndiceOfDad('C')*12+3;
        aas[indice0fDad] = 'E';
        push('(');
        indice0fDad = findIndiceOfDad('C')*12+2;
        aas[indice0fDad] = '(';
        push('o');
        indice0fDad = findIndiceOfDad('C')*12+1;
        aas[indice0fDad] = 'o';
        goto q1;
    }

    //fazer produções que consumam (identifiquem) os terminais m,r,0,1,x,y,(,),+,-,*,/,h,i,j,k,z,w,{,},;,f,=,o
    else if ((token == 'm') && (stack[top] == 'm'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == 'r') && (stack[top] == 'r'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == '0') && (stack[top] == '0'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == '1') && (stack[top] == '1'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == 'x') && (stack[top] == 'x'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == 'y') && (stack[top] == 'y'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == '(') && (stack[top] == '('))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == ')') && (stack[top] == ')'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == '+') && (stack[top] == '+'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == '-') && (stack[top] == '-'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == '*') && (stack[top] == '*'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == '/') && (stack[top] == '/'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == 'h') && (stack[top] == 'h'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == 'i') && (stack[top] == 'i'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == 'j') && (stack[top] == 'j'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == 'k') && (stack[top] == 'k'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == 'z') && (stack[top] == 'z'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if((token == 'w') && (stack[top] == 'w'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if((token == '{') && (stack[top] == '{'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if((token == '}') && (stack[top] == '}'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if((token == ';') && (stack[top] == ';'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if((token == 'f') && (stack[top] == 'f'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if((token == '=') && (stack[top] == '='))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if((token == 'o') && (stack[top] == 'o'))
    {
        pop();
        posicao++;
        goto q1;
    }
    
    



    else if (stack[top] == '\0' && token == '\0')
    {
        printf("palavra consumida\n\n");
        for (int i = 0; i < 9999999; i++)
        {
            if(aas[i] != '\0'){
                printf("indice %d | %c\n", i, aas[i]);

            }
        }
    }
    else
    {
        printf("\nerro Sintático\n\n");
        return 1;
    }
}