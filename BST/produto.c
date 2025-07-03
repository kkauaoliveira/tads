#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Necessário para a função strcmp
#include "BST.h" 

typedef struct produto {
    char nome[30];
    char marca[30];
    int codigo;
    float preco;
} produto;

int cmpNome(void *a, void *b) {
    produto *p1 = (produto*)a;
    produto *p2 = (produto*)b;
    return strcmp(p1->nome, p2->nome);
}

int cmpMarca(void *a, void *b) {
    produto *p1 = (produto*)a;
    produto *p2 = (produto*)b;
    return strcmp(p1->marca, p2->marca);
}

void printProduto(void *a) {
    produto *p = (produto*)a;
    printf("%s %s %d %.2f\n", p->nome, p->marca, p->codigo, p->preco);
}

int main() {
    FILE *f = fopen("produtos.txt", "r");
    if (f == NULL) {
        perror("Erro ao abrir o arquivo produtos.txt");
        return 1;
    }
    
    produto p[10];
    
    // Lê 10 produtos
    for (int i = 0; i < 10; i++) {
        if (fscanf(f, "%s %s %d %f", p[i].nome, p[i].marca, &p[i].codigo, &p[i].preco) != 4) {
            fprintf(stderr, "Erro ao ler a linha %d do arquivo.\n", i + 1);
            fclose(f);
            return 1;
        }
    }
    fclose(f); // Fecha o arquivo 

    printf("Produtos lidos do arquivo (ordem original):\n");
    printf("%s %s %s %s\n", "NOME", "MARCA", "CODIGO", "PRECO");
    for (int i = 0; i < 10; i++) {
        printProduto(&p[i]);
    }

    printf("\nAgora vamos organizar pelo nome ---------------------\n");
    printf("%s %s %s %s\n", "NOME", "MARCA", "CODIGO", "PRECO");

    BST *arvore_por_nome = BST_alloc(cmpNome);

    for (int i = 0; i < 10; i++) {
        BST_insert(arvore_por_nome, &p[i]);
    }

    // A função BST_print já percorre em ordem (in-order)
    BST_print(arvore_por_nome, printProduto);
    
    BST_free(arvore_por_nome);


    printf("\nAgora vamos organizar pela marca ---------------------\n");
    printf("%s %s %s %s\n", "NOME", "MARCA", "CODIGO", "PRECO");

    BST *arvore_por_marca = BST_alloc(cmpMarca);

    for (int i = 0; i < 10; i++) {
        BST_insert(arvore_por_marca, &p[i]);
    }

    BST_print(arvore_por_marca, printProduto);

    BST_free(arvore_por_marca);
    
    return 0;
}