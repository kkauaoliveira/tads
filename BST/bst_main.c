#include <stdlib.h>
#include <stdio.h>
#include "BST.h"

int cmpInt(void *a, void *b) {
    int *n1 = a;
    int *n2 = b;

    return *n1 - *n2;
}

void printInt(void *a) {
    int *n = a;
    printf("%d ", *n);
}

int main() {
    int n[10] = {56,12,89,32,11, 47,43,22,19,91};
    BST *b = BST_alloc(cmpInt);

    for (int i=0; i<10; i++)
        BST_insert(b, &n[i]);

    BST_print(b, printInt);
    return 0;
}