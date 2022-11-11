#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define stacksize 500
#define amax 2047
#define levmax 3
#define cxmax 200

typedef enum
{
    LIT,
    OPR,
    LOD,
    STO,
    CAL,
    INT,
    JMP,
    JPC
}
operator;
typedef struct
{
    operator f;
    int l;
    int a;
} instruction;

instruction code[cxmax];
int p, b, t, s[stacksize];


int base(int l)
{
    int b1;
    b1 = b;
    while (l > 0)
    {
        b1 = s[b1];
        l = l - 1;
    }
    return b1;
}


int retorna_enum(const char *fn) {

    if (strcmp(fn, "LIT") == 0) {
        return LIT;
    }

    if (strcmp(fn, "OPR") == 0) {
        return OPR;
    }

    if (strcmp(fn, "LOD") == 0) {
        return LOD;
    }

    if (strcmp(fn, "STO") == 0) {
        return STO;
    }

    if (strcmp(fn, "CAL") == 0) {
        return CAL;
    }

    if (strcmp(fn, "INT") == 0) {
        return INT;
    }

    if (strcmp(fn, "JMP") == 0) {
        return JMP;
    }

    if (strcmp(fn, "JPC") == 0) {
        return JPC;
    }
}

int main()
{
     char funcs[500][4];
        for (int i = 0; scanf("%s", funcs[i]) != EOF; i++) {

            code[i].f = retorna_enum(funcs[i]);
            scanf("%d %d\n", &code[i].l, &code[i].a);
        }
    instruction i;
    printf("Start pl/0\n");
    t = 0;
    b = 1;
    p = 0;
    s[1] = 0;
    s[2] = 0;
    s[3] = 0;
    do
    {
        i = code[p];
        printf("\nt = %d, b = %d, p = %d |", t, b, p);
        printf("%s %d %d ", funcs[p], i.l, i.a);
        p = p + 1;

        switch (i.f)
        {
        case LIT:
            t = t + 1;
            s[t] = i.a;
            break;
        case OPR:
            switch (i.a){
                case 0:
                    t=b-1;
                    p=s[t+3];
                    b=s[t+2];
                    break;
                case 1:
                    s[t]=-s[t];
                    break;
                case 2:
                    t=t-1;
                    s[t]=s[t]+s[t+1];
                    break;
                case 3:
                    t=t-1;
                    s[t]=s[t]-s[t+1];
                    break;
                case 4:
                    t=t-1;
                    s[t]=s[t]*s[t+1];
                    break;
                case 5:
                    t=t-1;
                    s[t]=s[t]/s[t+1];
                    break;
                case 6:
                    if(s[t]%2!=0)
                        s[t]=1;
                    else
                        s[t]=0;
                    break;
                case 8:
                    t--;
                    s[t]=s[t]==s[t+1];
                  
                    break;
                case 9:
                    t=t-1;
                    if(s[t]!=s[t+1])
                        s[t]=1;
                    else
                        s[t]=0;
                    break;
                case 10:
                    t=t-1;
                    if(s[t]<s[t+1])
                        s[t]=1;
                    else
                        s[t]=0;
                    break;
                case 11:
                    t=t-1;
                    if(s[t]>=s[t+1])
                        s[t]=1;
                    else
                        s[t]=0;
                    break;
                case 12:
                    t=t-1;
                    if(s[t]>s[t+1])
                        s[t]=1;
                    else
                        s[t]=0;
                    break;
                case 13:
                    t=t-1;
                    if(s[t]<=s[t+1])
                        s[t]=1;
                    else
                        s[t]=0;
                    break;
            }
            break;
        case LOD:
            t = t + 1;
            s[t] = s[base(i.l) + i.a];
            break;
        case STO:
            s[base(i.l) + i.a] = s[t];
            t=t-1;
            break;
        case CAL:
            s[t + 1] = base(i.l);
            s[t + 2] = b;
            s[t + 3] = p;
            b = t + 1;
            p = i.a;
            break;
        case INT:
            t = t + i.a;
            break;
        case JMP:
            p = i.a;
            break;
        case JPC:
            if (s[t] == 0){
                p = i.a;
            }
            t--;
            break;
        }
        if(t!=0){
            printf("| Pilha de dados:");
            for(int i=1;i<=t;i++){
                printf("[%d] ",s[i]);
            }
        }
    }while (p!=0);
    printf("\n\n");
   
    printf("End pl/0\n");
    return 0;
}