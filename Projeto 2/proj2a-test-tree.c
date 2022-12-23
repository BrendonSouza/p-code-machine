#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STACKSIZE 1000

char stack[STACKSIZE];
int top = -1;

int indice0fSon = 0;

#define MAX_CHILDREN 12

typedef struct Node
{
    char value;
    struct Node *children[MAX_CHILDREN];
    int visited;
} Node;

Node *createNode(char value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        newNode->children[i] = NULL;
        newNode->visited = 0;
    }
    return newNode;
}

void insertNode(Node *root, int value)
{


    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        if (root->children[i] == NULL)
        {
            root->children[i] = createNode(value);
            printf("Inserted node with value %d\n", value);
            return;
        }

    }

    printf("No more space to insert node with value %d\n", value);
}

Node* root;

// find the first node with an value that is not visited
Node* findFirstUnvisitedNode(Node* root, char value) {
    if (root == NULL) {
        return NULL;
    }

    if (root->value == value && root->visited == 0) {
        return root;
    }

    for (int i = 0; i < MAX_CHILDREN; i++) {
        Node* node = findFirstUnvisitedNode(root->children[i], value);
        if (node != NULL) {
            return node;
        }
    }

    return NULL;
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

void print_tree(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%c ", root->value);

    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        print_tree(root->children[i]);
    }
}

void bfs(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%c ", root->value);

    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        bfs(root->children[i]);
    }
}

void dfs(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    printf("%c ", root->value);

    for (int i = 0; i < MAX_CHILDREN; i++)
    {
        dfs(root->children[i]);
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
    //insert S as root
    root = createNode('S');
    goto q1;
q1:
    token = word[posicao];

    // ! p1: S → M
    if ((token == 'm') && (stack[top] == 'S'))
    {
        pop();
        push('M');
        //insert M as child of S
        insertNode(root, 'M');
        //visited S
        root->visited = 1;
        goto q1;
    }
    // p2: S -> G M
    else if ((token == 'G') && (stack[top] == 'S'))
    {
        pop();
        push('M');
        //insert M as child of S
        insertNode(root, 'M');
        push('G');
        //insert G as child of S
        insertNode(root, 'G');
        goto q1;
    }
    // p3: S -> F G M
    else if ((token == 'F') && (stack[top] == 'S'))
    {
        pop();
        push('M');
        push('G');
        push('F');
        goto q1;
    }
    // p4: F → f(){ C; r(E); }
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
        Node *no = findFirstUnvisitedNode(root, 'M');
        pop();
        push('}');
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
        push('m');
        insertNode(no, 'm');
        insertNode(no, '(');
        insertNode(no, ')');
        insertNode(no, '{');
        insertNode(no, 'C');
        insertNode(no, ';');    
        insertNode(no, 'r');
        insertNode(no, '(');    
        insertNode(no, 'E');
        insertNode(no, ')');
        insertNode(no, ';');
        insertNode(no, '}');


        //insert m as child of M
        
        goto q1;
    }
    // p7 : E → 0 | 1 | x | y | (EXE)
    else if ((token == '0') && (stack[top] == 'E'))
    {
        Node *no = findFirstUnvisitedNode(root, 'E');
        pop();
        push('0');
        insertNode(no, '0');
        goto q1;
    }
    else if ((token == '1') && (stack[top] == 'E'))
    {
         Node *no = findFirstUnvisitedNode(root, 'E');
        pop();
        push('1');
        insertNode(no, '1');
        goto q1;
    }
    else if ((token == 'x') && (stack[top] == 'E'))
    {
         Node *no = findFirstUnvisitedNode(root, 'E');
        pop();
        push('x');
        insertNode(no, 'x');
        goto q1;
    }
    else if ((token == 'y') && (stack[top] == 'E'))
    {
         Node *no = findFirstUnvisitedNode(root, 'E');
        pop();
        push('y');
        insertNode(no, 'y');
        goto q1;
    }
    // p11: E -> (EXE)
    else if ((token == '(') && (stack[top] == 'E'))
    {
         Node *no = findFirstUnvisitedNode(root, 'E');
        printf("E->(EXE)");
        pop();
        push(')');

        push('E');
        push('X');
        push('E');
        push('(');
        insertNode(no, '(');
        insertNode(no, 'E');
        insertNode(no, 'X');
        insertNode(no, 'E');
        insertNode(no, ')');
        goto q1;
    }
    // p:12 X → + | - | * | /
    else if ((token == '+') && (stack[top] == 'X'))
    {
         Node *no = findFirstUnvisitedNode(root, 'X');
        pop();
        push('+');

        insertNode(no, '+');
        goto q1;
    }
    else if ((token == '-') && (stack[top] == 'X'))
    {
        Node *no = findFirstUnvisitedNode(root, 'X');
        pop();
        push('-');
        insertNode(no, '-');
        goto q1;
    }
    else if ((token == '*') && (stack[top] == 'X'))
    {
        Node *no = findFirstUnvisitedNode(root, 'X');
        pop();
        push('*');
        insertNode(no, '*');
        goto q1;
    }
    else if ((token == '/') && (stack[top] == 'X'))
    {
        Node *no = findFirstUnvisitedNode(root, 'X');
        pop();
        push('/');
        insertNode(no, '/');
        goto q1;
    }

    // p16: C -> h=E | i=E | j=E | k=E | z=E
    else if ((token == 'h') && (stack[top] == 'C'))
    {
        Node *no = findFirstUnvisitedNode(root, 'C');
        pop();
        push('E');
        push('=');

        push('h');
        insertNode(no, 'h');
        insertNode(no, '=');
        insertNode(no, 'E');
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

        push('E');
        push('X');
        push('E');
        push('(');
        goto q1;
    }
    // p22: C -> w(E){ C; }
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
        push(';');
        push('C');
        push('{');
        push(')');
        push('E');
        push(';');
        push('E');
        push(';');
        push('E');
        push('(');
        push('o');
        goto q1;
    }

    // fazer produções que consumam (identifiquem) os terminais m,r,0,1,x,y,(,),+,-,*,/,h,i,j,k,z,w,{,},;,f,=,o
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
    else if ((token == 'w') && (stack[top] == 'w'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == '{') && (stack[top] == '{'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == '}') && (stack[top] == '}'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == ';') && (stack[top] == ';'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == 'f') && (stack[top] == 'f'))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == '=') && (stack[top] == '='))
    {
        pop();
        posicao++;
        goto q1;
    }
    else if ((token == 'o') && (stack[top] == 'o'))
    {
        pop();
        posicao++;
        goto q1;
    }

    else if (stack[top] == '\0' && token == '\0')
    {
        printf("palavra consumida\n\n");
        dfs(root->children[0]->children[4]);

    }
    else
    {
        printf("\nerro Sintático\n\n");
        return 1;
    }
}

