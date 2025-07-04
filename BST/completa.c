#include <stdlib.h>
#include <stdio.h>
#include "BST.h"   // Contém as declarações de BST, BST_node e suas funções
#include "Queue.h" // Contém as declarações de Queue e suas funções

// --- Funções Auxiliares de Comparação e Impressão para Inteiros ---

// Função de comparação para inteiros, usada pela BST.
// Retorna:
//   < 0 se *a < *b
//   > 0 se *a > *b
//     0 se *a == *b
int cmpInt(void *a, void *b) {
    int *valor1 = (int*)a;
    int *valor2 = (int*)b;
    return *valor1 - *valor2;
}

// Função de impressão para inteiros, usada para exibir os nós da árvore.
void print_int(void *a) {
    int *num = a;
    printf("%d ", *num);
}

// --- Função para Verificar se um Nó é Folha ---

// Retorna 1 se o nó for uma folha (não tem filhos), 0 caso contrário.
// Um nó NULL não é considerado uma folha.
int verifica_se_folha(BST_node *no) {
    if (no == NULL) {
        return 0;
    }
    return (no->left == NULL && no->right == NULL);
}

// --- Função para Contar as Folhas da Árvore ---

// Conta e imprime o número de nós folha em uma árvore binária
// usando uma travessia em nível (BFS) com uma fila.
void conta_folhas(BST *arvore) {
    // Lida com árvore vazia ou nula
    if (arvore == NULL || arvore->root == NULL) {
        printf("Essa arvore esta vazia e nao possui nenhum no\n");
        printf("0 nos folha\n");
        return;
    }

    // Aloca a fila. O tamanho é o número total de nós da árvore (arvore->n),
    // o que garante espaço suficiente para a maior largura possível de um nível.
    Queue *fila = Queue_alloc(arvore->n); 
    
    // Verifica se a alocação da fila falhou.
    if (fila == NULL) {
        fprintf(stderr, "Erro: Nao foi possivel alocar memoria para a fila.\n");
        return;
    }

    int cont = 0; // Inicializa o contador de folhas

    // Enfileira a raiz da árvore para começar a travessia BFS.
    Queue_push(fila, arvore->root);
    
    // Loop principal da BFS: continua enquanto houver nós na fila para processar.
    while (!Queue_isEmpty(fila)) {
        // Desenfileira o nó atual para processamento.
        BST_node *current_node = (BST_node *)Queue_pop(fila); 
        
        // Processa o nó: verifica se é uma folha e incrementa o contador.
        if (verifica_se_folha(current_node)) {
            cont++;
        }

        // Enfileira os filhos do nó atual (se existirem) para processamento futuro.
        if (current_node->left != NULL) {
            Queue_push(fila, current_node->left);
        }
        if (current_node->right != NULL) {
            Queue_push(fila, current_node->right);
        }
    }
    
    // Libera a memória da fila após a travessia.
    Queue_free(fila);

    // Imprime o número total de nós folha encontrados.
    printf("%d nos folha\n", cont);
}

// --- Função para Calcular a Altura da Árvore ---
// A altura de uma árvore com um único nó é 0. A altura de uma árvore vazia é -1.
int calcular_altura(BST_node *no) {
    if (no == NULL) {
        return -1;
    }
    int altura_esquerda = calcular_altura(no->left);
    int altura_direita = calcular_altura(no->right);
    return (altura_esquerda > altura_direita ? altura_esquerda : altura_direita) + 1;
}

// --- Função para Verificar se uma Árvore Binária é Perfeita ---
// Uma árvore binária perfeita possui o número máximo de nós possível em todos os seus níveis.
int eh_arvore_perfeita(BST *arvore) {
    // Lida com árvore vazia ou nula: não é considerada perfeita.
    if (arvore == NULL || arvore->root == NULL) {
        return 0;
    }

    // Calcula a altura esperada da árvore.
    int altura_esperada = calcular_altura(arvore->root);

    // Aloca a fila para a travessia BFS.
    Queue *fila = Queue_alloc(arvore->n); 
    if (fila == NULL) {
        fprintf(stderr, "Erro: Nao foi possivel alocar memoria para a fila.\n");
        return 0;
    }

    // Enfileira a raiz para iniciar a BFS.
    Queue_push(fila, arvore->root);
    
    int nivel_atual = 0; // Começa no nível 0 (raiz)

    // Loop BFS: continua enquanto a fila não estiver vazia.
    while (!Queue_isEmpty(fila)) {
        // Calcula o número de nós atualmente na fila para o nível atual.
        // A sua Queue.c não expõe Queue_size, então vamos calcular usando begin/end.
        int nos_no_nivel_atual;
        if (fila->begin <= fila->end) {
            nos_no_nivel_atual = fila->end - fila->begin + 1;
        } else { // Fila circular "virou"
            nos_no_nivel_atual = fila->size - fila->begin + fila->end + 1;
        }

        // Calcula o número de nós esperado para uma árvore perfeita neste nível (2^nivel_atual).
        long long int nos_esperados_no_nivel = 1LL << nivel_atual;

        // Verifica se o número real de nós no nível corresponde ao esperado.
        if (nos_no_nivel_atual != nos_esperados_no_nivel) {
            Queue_free(fila);
            return 0; // Não é perfeita, pois o nível não está totalmente preenchido.
        }

        // Processa todos os nós no nível atual.
        for (int i = 0; i < nos_no_nivel_atual; i++) {
            // Desenfileira o nó atual.
            BST_node *current_node = (BST_node *)Queue_pop(fila);

            // Verifica as propriedades dos filhos com base no nível.
            if (nivel_atual < altura_esperada) { // Se não estamos no último nível
                // Todos os nós nestes níveis DEVEM ter exatamente dois filhos para uma árvore perfeita.
                if (current_node->left == NULL || current_node->right == NULL) {
                    Queue_free(fila);
                    return 0; // Nó interno não tem dois filhos, então não é perfeita.
                }
                // Enfileira ambos os filhos para o próximo nível.
                Queue_push(fila, current_node->left);
                Queue_push(fila, current_node->right);
            } else { // Este é o último nível (nivel_atual == altura_esperada)
                // Todos os nós no último nível DEVEM ser folhas (não ter filhos).
                if (current_node->left != NULL || current_node->right != NULL) {
                    Queue_free(fila);
                    return 0; // Nó no último nível não é folha.
                }
            }
        }
        nivel_atual++; // Avança para o próximo nível.
    }

    // Libera a memória da fila.
    Queue_free(fila);

    // Se todas as verificações passaram e a altura processada coincide com a esperada, é perfeita.
    return (nivel_atual - 1) == altura_esperada;
}

// --- Função Principal ---

int main() {
    // Caso de Teste 1: Seu array original (esperado: NÃO perfeita)
    BST *arvore1 = BST_alloc(cmpInt);
    int vet1[9] = {50, 45, 55, 46, 66, 77, 33, 40, 23};

    printf("--- Teste Arvore 1 ---\n");
    printf("Inserindo elementos: ");
    for (int i = 0; i < 9; i++) {
        printf("%d ", vet1[i]);
        BST_insert(arvore1, &vet1[i]); 
    }
    printf("\n");

    printf("Elementos da arvore 1 (Travessia Em Ordem): ");
    BST_print(arvore1, print_int);
    printf("Contagem de nos folhas na Arvore 1:\n");
    conta_folhas(arvore1); // Chama sua função corrigida de contagem de folhas

    if (eh_arvore_perfeita(arvore1)) {
        printf("A arvore 1 E perfeita (completa na sua definicao).\n");
    } else {
        printf("A arvore 1 NAO E perfeita (completa na sua definicao).\n");
    }
    BST_free(arvore1); // Libera a memória da arvore1

    printf("\n");

    // Caso de Teste 2: Uma árvore binária perfeita de altura 2 (7 nós)
    //         10
    //       /    \
    //      5      15
    //     / \    /  \
    //    2   7  12  18
    BST *arvore2 = BST_alloc(cmpInt);
    int vet2[7] = {10, 5, 15, 2, 7, 12, 18};

    printf("--- Teste Arvore 2 (Esperado: Perfeita) ---\n");
    printf("Inserindo elementos: ");
    for (int i = 0; i < 7; i++) {
        printf("%d ", vet2[i]);
        BST_insert(arvore2, &vet2[i]);
    }
    printf("\n");
    BST_print(arvore2, print_int);
    printf("Contagem de nos folhas na Arvore 2:\n");
    conta_folhas(arvore2);
    if (eh_arvore_perfeita(arvore2)) {
        printf("A arvore 2 E perfeita (completa na sua definicao).\n");
    } else {
        printf("A arvore 2 NAO E perfeita (completa na sua definicao).\n");
    }
    BST_free(arvore2); // Libera a memória da arvore2

    printf("\n");

    // Caso de Teste 3: Uma árvore perfeita de altura 0 (1 nó - apenas a raiz)
    BST *arvore3 = BST_alloc(cmpInt);
    int vet3[1] = {100};

    printf("--- Teste Arvore 3 (Esperado: Perfeita - nó único) ---\n");
    printf("Inserindo elemento: %d\n", vet3[0]);
    BST_insert(arvore3, &vet3[0]);
    BST_print(arvore3, print_int);
    printf("Contagem de nos folhas na Arvore 3:\n");
    conta_folhas(arvore3);
    if (eh_arvore_perfeita(arvore3)) {
        printf("A arvore 3 E perfeita (completa na sua definicao).\n");
    } else {
        printf("A arvore 3 NAO E perfeita (completa na sua definicao).\n");
    }
    BST_free(arvore3); // Libera a memória da arvore3

    printf("\n");

    // Caso de Teste 4: Árvore vazia
    BST *arvore4 = BST_alloc(cmpInt);
    printf("--- Teste Arvore 4 (Esperado: Nao Perfeita - Vazia) ---\n");
    BST_print(arvore4, print_int); // Não imprimirá nada
    printf("Contagem de nos folhas na Arvore 4:\n");
    conta_folhas(arvore4);
    if (eh_arvore_perfeita(arvore4)) {
        printf("A arvore 4 E perfeita (completa na sua definicao).\n");
    } else {
        printf("A arvore 4 NAO E perfeita (completa na sua definicao).\n");
    }
    BST_free(arvore4); // Libera a memória da arvore4

    return 0;
}