#include <stdlib.h>
#include <stdio.h>
#include "BST.h"

typedef struct Pessoa {
    char nome[100];
    int idade;
} Pessoa;

int cmpPessoa(void *a, void *b) {
    Pessoa *p1 = a;
    Pessoa *p2 = b;
    return p1->idade - p2->idade;
}

void printPessoa(void *a) {
    Pessoa *p = a;
    if (p)
        printf("%d %s\n", p->idade, p->nome);
}

int main() {
    BST *b = BST_alloc(cmpPessoa);
    Pessoa *p;
    Pessoa x;
    FILE *f = fopen("name_age.txt", "r");

    for (int i=0; i<50; i++) {
        p = malloc(sizeof(Pessoa));
        fscanf(f, "%s%d", p->nome, &p->idade);
        BST_insert(b, p);
    }

    //BST_print(b, printPessoa);

    x.idade = 12;
    p = BST_search(b, &x);
    printPessoa(p);

    BST_free(b);
    return 0;
}