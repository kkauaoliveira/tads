#include <stdlib.h>
#include <stdio.h>
#include "BST.h" // Escreva uma função recursiva que conta o número de folhas em uma árvore binária.

int cmp(void *a, void *b){
    int *value1 = a;
    int *value2 = b;
    return *value1 - *value2;
}

void print(void *bst){
    int *a = bst;
    printf("%d ", *a);
}

int contafolhas(BST_node *bst){
    if (bst != NULL){
        if (bst->left == NULL && bst->right == NULL)
            return 1;
        else
            return contafolhas(bst->left) + contafolhas(bst->right);
    }
    return 0;
}

int main(){
    BST *b = BST_alloc(cmp);
    int vet[6] = {4, 3, 5, 1, 7, 8};

    for (int i = 0; i < 6; i++){
        BST_insert(b, &vet[i]);
    }


    BST_print(b, print);
    printf("%d", contafolhas(b->root));
    BST_free(b);
    return 0;
}