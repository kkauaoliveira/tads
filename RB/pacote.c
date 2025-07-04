#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#include "RB.h"     // Suas definições e protótipos da Red-Black Tree
#include "Queue.h"  // Suas definições e protótipos da Fila

// --- Definição da Estrutura Pacote ---
typedef struct {
    int ordem;
    char info;
} Pacote;

// --- Funções Auxiliares para Pacote ---
int cmpPacote(const void *a, const void *b) {
    const Pacote *p1 = (const Pacote*)a;
    const Pacote *p2 = (const Pacote*)b;
    return p1->ordem - p2->ordem; 
}

void printPacote(void *a) {
    Pacote *p = (Pacote*)a;
    printf("(%d,%c) ", p->ordem, p->info);
}

// --- Funções para Árvore RB e Fila ---
RB *criarArvoreRBComPacotes(Pacote *vetor_pacotes, int num_pacotes) {
    RB *arvore_pacotes = RB_alloc(cmpPacote);
    if (arvore_pacotes == NULL) {
        perror("Erro ao alocar a arvore RB");
        return NULL;
    }
    for (int i = 0; i < num_pacotes; i++) {
        RB_insert(arvore_pacotes, &vetor_pacotes[i]);
    }
    return arvore_pacotes;
}

static void _percorrerInOrderEEnfileirarRB(RB_node *node, Queue *fila_pacotes) {
    if (node == NULL) {
        return;
    }
    _percorrerInOrderEEnfileirarRB(node->left, fila_pacotes);
    Queue_push(fila_pacotes, node->item); 
    _percorrerInOrderEEnfileirarRB(node->right, fila_pacotes);
}

Queue *percorrerArvoreRB_E_Enfileirar(RB *arvore_rb) {
    if (arvore_rb == NULL || arvore_rb->root == NULL) {
        return NULL;
    }
    Queue *fila_ordenada = Queue_alloc(arvore_rb->n); 
    if (fila_ordenada == NULL) {
        perror("Erro ao alocar a fila para pacotes ordenados");
        return NULL;
    }
    _percorrerInOrderEEnfileirarRB(arvore_rb->root, fila_ordenada);
    return fila_ordenada;
}

// --- Função Principal ---
int main() {
    FILE *fp;
    
    int capacidade_pacotes = 10; 
    Pacote *vetor_pacotes_brutos = (Pacote*)malloc(capacidade_pacotes * sizeof(Pacote));
    if (vetor_pacotes_brutos == NULL) {
        perror("Erro ao alocar vetor_pacotes_brutos");
        return 1;
    }
    int num_pacotes_brutos = 0;

    fp = fopen("mensagem.txt", "r");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo mensagem.txt. Certifique-se de que ele exista na mesma pasta do executável.");
        free(vetor_pacotes_brutos);
        return 1;
    }

    printf("Lendo pacotes do mensagem.txt (formato '%%d %%c'):\n");
    int ordem_lida;
    char info_lida;
    
    while (fscanf(fp, "%d %c", &ordem_lida, &info_lida) == 2) {
        if (num_pacotes_brutos == capacidade_pacotes) {
            capacidade_pacotes *= 2; 
            Pacote *temp_vetor = (Pacote*)realloc(vetor_pacotes_brutos, capacidade_pacotes * sizeof(Pacote));
            if (temp_vetor == NULL) {
                perror("Erro ao realocar vetor_pacotes_brutos. Pacotes restantes serao ignorados.");
                break; 
            }
            vetor_pacotes_brutos = temp_vetor;
        }

        vetor_pacotes_brutos[num_pacotes_brutos].ordem = ordem_lida;
        // Não faz mais a substituição do '_' por espaço.
        vetor_pacotes_brutos[num_pacotes_brutos].info = info_lida;
        
        printf("Pacote lido: (%d,%c)\n", ordem_lida, vetor_pacotes_brutos[num_pacotes_brutos].info); 
        num_pacotes_brutos++;

        int c_dummy;
        while ((c_dummy = fgetc(fp)) != EOF && c_dummy != '\n'); 
    }
    
    fclose(fp);
    printf("Total de pacotes brutos lidos: %d\n\n", num_pacotes_brutos);

    // --- Simulação da Transmissão ---
    printf("--- Simulacao da Transmissao da Mensagem ---\n");

    RB *arvore_ordenada_sem_replicas = criarArvoreRBComPacotes(vetor_pacotes_brutos, num_pacotes_brutos);
    if (arvore_ordenada_sem_replicas == NULL) {
        free(vetor_pacotes_brutos);
        return 1;
    }
    printf("Arvore RB preenchida com %d nos (apos eliminacao de replicas, se houver).\n", arvore_ordenada_sem_replicas->n);
    printf("\n");

    Queue *fila_mensagem_final = percorrerArvoreRB_E_Enfileirar(arvore_ordenada_sem_replicas);
    if (fila_mensagem_final == NULL) {
        RB_free(arvore_ordenada_sem_replicas);
        free(vetor_pacotes_brutos);
        return 1;
    }
    printf("Fila de mensagem final criada. %d pacotes ordenados.\n", arvore_ordenada_sem_replicas->n);
    printf("\n");

    printf("Passo 3: Imprimindo a mensagem original completa e na ordem correta:\n");
    
    int tamanho_max_mensagem = 69 + 1; // Para caracteres de 1 a 69, e o '\0'
    char *mensagem_reconstruida = (char*)calloc(tamanho_max_mensagem, sizeof(char));
    if (mensagem_reconstruida == NULL) {
        perror("Erro ao alocar mensagem_reconstruida");
        Queue_free(fila_mensagem_final);
        RB_free(arvore_ordenada_sem_replicas);
        free(vetor_pacotes_brutos);
        return 1;
    }

    for(int i = 0; i < tamanho_max_mensagem - 1; i++){
        mensagem_reconstruida[i] = ' '; 
    }
    mensagem_reconstruida[tamanho_max_mensagem - 1] = '\0';

    while (!Queue_isEmpty(fila_mensagem_final)) {
        Pacote *p = (Pacote*)Queue_pop(fila_mensagem_final);
        if (p != NULL) {
            // A ordem é 1-based, então o índice do array é (ordem - 1)
            if (p->ordem >= 1 && p->ordem <= 69) { 
                mensagem_reconstruida[p->ordem - 1] = p->info;
            } else {
                fprintf(stderr, "Aviso: Pacote com ordem %d fora do intervalo [1, 69]. Ignorado.\n", p->ordem);
            }
        }
    }

    printf("MENSAGEM RECONSTRUIDA: %s\n", mensagem_reconstruida);

    // Liberar a memória alocada
    Queue_free(fila_mensagem_final);
    RB_free(arvore_ordenada_sem_replicas);
    free(vetor_pacotes_brutos); 
    free(mensagem_reconstruida); 

    return 0;
}