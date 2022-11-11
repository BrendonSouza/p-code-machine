
#include    <stdio.h>
#include    <string.h>
#include <stdlib.h>


//ler arquivo por linha de comando
int main(int argc, char *argv[]) {
    FILE *fp;
    char *line = NULL;
    char linha[100];
    size_t len = 100;
    ssize_t read;

    fp = fopen(argv[1], "r");
        //for ate o final de argv  
    if (fp == NULL)
        return 1;

   
    while (!feof(fp)) {
  
       line = fgets(linha, len, fp);
        printf("%s", line);
    }

    // fclose(fp);
    // if (line)
    //     free(line);
    
}