#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *f = fopen("arquivo.txt", "a"); //"a"para adicionar

    fputs("Esse texto foi add com o a e fputs\n", f);
    fprintf(f, "Esse daqui foi com o a e fprintf\n");

    fclose(f);
    return 0;
}