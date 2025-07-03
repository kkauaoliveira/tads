#include <stdlib.h>
#include <stdio.h>
#include "BST.h"

int compara_int(void *a, void *b){
    int *valor1 = a;
    int *valor2 = b;

    return *valor1 - *valor2;
}

void print_int(void *numero){
    int *valor = numero;
    printf("%d ", *valor);
}

int comp_menor(void *BST_node, int value){

}

 void *BST_min(BST *bst){
    BST_node *n = bst->root;
    if (bst == NULL || bst->root == NULL){
        return NULL;
    }
    while(n->left != NULL){
        n = n->left;
    }
    return n->value;
 }

int main(){
    BST *t = BST_alloc(compara_int);
    int vet[9] = {87, 5, 6, 7, 4, 13, 45, 66, 10};

    for (int i = 0; i < 9; i++){
        BST_insert(t, &vet[i]);
    };

    BST_print(t, print_int);

    int *ptr = BST_min(t);

    printf("%d", *ptr);

    BST_free(t);

    return 0;
}