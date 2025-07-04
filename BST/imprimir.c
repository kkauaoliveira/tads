#include "BST.h"   // Inclui o cabecalho da sua Arvore Binaria de Busca
#include "Stack.h" // Inclui o cabecalho da sua Pilha
#include <stdio.h> // Para printf, fprintf, NULL
#include <stdlib.h> // Para malloc, free, exit

// --- Funcoes Auxiliares de Comparacao e Impressao (Exemplos para inteiros) ---

// Funcao de comparacao para inteiros, usada pela BST.
// Retorna negativo se 'a' < 'b', zero se 'a' == 'b', positivo se 'a' > 'b'.
int compararInteiros(void *elementoA, void *elementoB) {
    int *intA = (int*)elementoA;
    int *intB = (int*)elementoB;
    return *intA - *intB;
}

// Funcao de impressao para inteiros, usada para exibir os nos da BST.
void imprimirInteiro(void *elemento) {
    int *inteiro = (int*)elemento;
    printf("%d ", *inteiro);
}

// --- Funcao de impressao nao recursiva (em ordem) para BST ---
// Esta funcao utiliza o TAD Pilha fornecido.
// Nome da funcao agora sem acentos
void imprimirBSTNaoRecursivoEmOrdem(BST *arvore, void (*funcaoImprimir)(void*)) {
    // A estrutura BST e BST_node ainda usam os nomes em ingles do seu BST.h original.
    // Portanto, devemos usar 'root', 'left', 'right', 'value' aqui.
    if (arvore == NULL || arvore->root == NULL) { // Corrigido: 'raiz' para 'root'
        printf("[Arvore Vazia]\n");
        return;
    }

    // A estrutura Stack em Stack.h ainda usa 'Stack', nao 'Pilha'.
    // Portanto, devemos usar 'Stack' aqui.
    Stack *pilha = Stack_alloc(arvore->n > 0 ? arvore->n : 10); // Corrigido: 'Pilha' para 'Stack'
    if (pilha == NULL) {
        fprintf(stderr, "Erro: Nao foi possivel alocar a pilha para travessia.\n");
        exit(EXIT_FAILURE); 
    }

    // A estrutura BST_node usa 'left' e 'right', nao 'esquerda' e 'direita'.
    // E 'value' ao inves de 'valor'.
    BST_node *atual = arvore->root; // Corrigido: 'raiz' para 'root'

    while (atual != NULL || !Stack_isEmpty(pilha)) { // Stack_isEmpty espera 'Stack *'
        while (atual != NULL) {
            Stack_push(pilha, atual); // Stack_push espera 'Stack *'
            atual = atual->left;      // Corrigido: 'esquerda' para 'left'
        }

        atual = (BST_node *)Stack_pop(pilha); // Stack_pop espera 'Stack *'
        
        if (atual != NULL) { 
            funcaoImprimir(atual->value); // Corrigido: 'valor' para 'value'
        }

        atual = atual->right; // Corrigido: 'direita' para 'right'
    }

    Stack_free(pilha); // Stack_free espera 'Stack *'
    printf("\n");      // Imprime uma nova linha apos a conclusao da impressao
}

// --- Funcao Principal ---
int main() {
    BST *minhaArvore = BST_alloc(compararInteiros);

    int valores[] = {50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65, 75, 85};
    int numeroValores = sizeof(valores) / sizeof(valores[0]);

    for (int i = 0; i < numeroValores; i++) {
        BST_insert(minhaArvore, &valores[i]);
    }

    printf("Impressao em ordem (nao recursiva):\n");
    imprimirBSTNaoRecursivoEmOrdem(minhaArvore, imprimirInteiro);
    printf("\n"); 

    BST_free(minhaArvore); 
    
    return 0; 
}