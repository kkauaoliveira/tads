#include <stdlib.h>
#include <stdio.h>
#include "BST.h"

int cmp(void *a, void *b){
    int *valor1 = a;
    int *valor2 = b;
    return *valor1 - *valor2;
}

void print(void *l){
    int *a = l;
    printf("%d ", *a);
}

int compara_nos(BST_node *a, BST_node *b){
    if (a && b){
        if(a->value == b->value){
            return 1;
        }
    }
    return 0;
}

int compara_bst(BST_node *a, BST_node *b){
    if (a && b){
        if (compara_nos(a, b)){
            compara_bst(a->left, b->left);
            compara_bst(a->right, b->right);
            return 1;
        }
    }
    return 0;
}

int main(){
    BST *b = BST_alloc(cmp);
    BST *g = BST_alloc(cmp);
    int vet1[6] = {66, 6, 77, 43, 22, 69};
    int vet2[6] = {66, 6, 78, 33, 29, 100};

    for (int i = 0; i < 6; i++){
        BST_insert(b, &vet1[i]);
    }
    for (int i = 0; i < 6; i++){
        BST_insert(g, &vet2[i]);
    }

    int resultado = compara_bst(b->root, g->root);

    if (resultado == 1){
        printf("Essas Arvores sao iguais");
    }else{
        printf("Essas Arvores nao sao iguais");
    }
    
    BST_free(b);
    BST_free(g);

    return 0;
}

