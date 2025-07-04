#include <stdlib.h>
#include <stdio.h>
#include "BST.h"
#include "Queue.h"

int cmpInt(void *a, void *b){
    int *valor1 = (int*)a; // ptr vai ser o *valor1, o a era um ponteiro void
    int *valor2 = (int*)b;
    return *valor1 - *valor2;
}

void print_int(void *a){
    int *num = a;
    printf("%d ", *num);
}

int verifica_se_folha(BST_node *no){
    if (no->left == NULL && no->right == NULL){
        return 1;
    }
    return 0;
}

void conta_folhas(BST *arvore){
    BST_node *arvore_aux = arvore->root;
    Queue *fila = Queue_alloc(arvore->n);

    Queue_push(fila, arvore_aux);
    
    int cont = 0;

    if (arvore_aux != NULL){
        BST_node *n = arvore_aux;
        while (!Queue_isEmpty(fila)){
            if (n->left != NULL && n->right != NULL){
                Queue_push(fila, n->left);
                Queue_push(fila, n->right);
            }else if (n->left != NULL){
                Queue_push(fila, n->left);
            }else if (n->right != NULL){
                Queue_push(fila, n->right);
            }

            cont = cont + verifica_se_folha(n);
            
            Queue_pop(fila);
            n = Queue_begin(fila);
        }
        
    }
    if(arvore_aux == NULL) 
        printf("Essa arvore esta vazia e nao possui nenhum no\n");
    printf("%d nos folha\n", cont);
}

int main(){
    BST *arvore = BST_alloc(cmpInt);
    int vet[9] = {50, 45, 55, 46, 66, 77, 33, 40, 23};

    for (int i = 0; i < 9; i++)
    {
        BST_insert(arvore, &vet[i]); 
    }

    BST_print(arvore, print_int);
    conta_folhas(arvore);

    BST_free(arvore);
    return 0;
}
