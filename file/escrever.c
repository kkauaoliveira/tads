#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *f = fopen("arquivo.txt", "w");

    fprintf(f, "Isso foi escrito usando fprintf kaua\n");
    //ou
    fputs("isso foi escrito usando fputs kaua gatp\n", f);

    fclose(f);

    return 0;

}