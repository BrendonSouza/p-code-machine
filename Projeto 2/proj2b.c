#include <stdio.h>
#include <string.h>
char token;

S(){
    if (token == 'M')
    {
        M();
    }
    else
    {
        M();
    }
}

M()
{
    if (token == 'm')
    {
        lex();
        if (token == '(')
        {
            lex();
            if (token == ')')
            {
                lex();
            }
            if (token == '{')
            {
                C();
                if (token == ';')
                {
                    lex();
                    if (token == '(')
                    {
                        E();
                        if (token == ')')
                        {
                            lex();
                            if (token == ';')
                            {
                                lex();
                                if (token == '}')
                                {
                                    lex();
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void lex()
{
    return 0;
}

int main(int argc, char *argv[])
{
}