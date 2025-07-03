#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#define DIM 9

enum {BRANCO, VERDE, CINZA, AMARELO, AZUL};

void color(int);
void show(int [DIM][DIM]);
int pixel(int, int);
void coloringArea(int img[DIM][DIM], int i, int j, int n);

int main() {
    int img[DIM][DIM] = {{0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 1, 0, 0, 0, 0},
                         {0, 0, 0, 1, 1, 1, 0, 0, 0},
                         {0, 0, 1, 1, 1, 1, 1, 0, 0},
                         {0, 1, 1, 1, 1, 1, 1, 1, 0},
                         {0, 0, 2, 0, 0, 0, 2, 0, 0},
                         {0, 0, 2, 0, 0, 0, 2, 0, 0},
                         {0, 0, 2, 2, 2, 2, 2, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0}};
    show(img);
    int x, y, cor;    
    printf("Selecione o pixel (x,y): ");
    scanf("%d%d", &x, &y);
    printf("a Selecione cor:\n\t0 BRANCO\n\t1 VERDE\n\t2 CINZA\n\t3 AMARELO\n\t4 AZUL\n:");
    scanf("%d", &cor);
    coloringArea(img, x, y, cor);
    show(img);
    return 0;
}

void color(int color) {
    switch (color) {
        case BRANCO  : printf("\e[107m  \e[m"); break;
        case VERDE   : printf("\e[102m  \e[m"); break;
        case CINZA   : printf("\e[100m  \e[m"); break;
        case AMARELO : printf("\e[103m  \e[m"); break;
        case AZUL    : printf("\e[104m  \e[m"); break;
    }
}

void show(int img[DIM][DIM]) {
  int i, j;
  printf("  0 1 2 3 4 5 6 7 8\n");    
  for (i = 0; i < DIM; i++) {
        printf("%d ", i);
        for (j = 0; j < DIM; j++) {
            color(img[i][j]);
        }
        printf("\n");
    }
}

int pixel(int i, int j) {
    return i * DIM + j;
}

void coloringArea(int img[DIM][DIM], int i, int j, int n) {
    Queue *q = Queue_alloc(DIM*DIM);
    int p, a = img[i][j];

    img[i][j] = n;
    Queue_push(q, pixel(i, j));
        
    while (!Queue_isEmpty(q) && a != n) {
        p = Queue_pop(q);
        i = p / DIM;
        j = p % DIM;
        
        if (img[i][j+1] == a) { 
            img[i][j+1] = n; 
            Queue_push(q, pixel(i, j+1));
        }
        if (img[i+1][j] == a) { 
            img[i+1][j] = n; 
            Queue_push(q, pixel(i+1, j));
        }
        if (i > 0)
            if (img[i-1][j] == a) { 
                img[i-1][j] = n; 
                Queue_push(q, pixel(i-1, j));
            }
        if (j > 0)
            if (img[i][j-1] == a) { 
                img[i][j-1] = n; 
                Queue_push(q, pixel(i, j-1));
            } 
    }
    
    Queue_free(q);
}
