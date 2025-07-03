#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "List.h"

typedef struct {
  char nome[50];
  int RG;
} Pessoa;

void print(void *a) {
  Pessoa *pess = a;
  printf("(%s %d)-> ", pess->nome, pess->RG);
}

int cmpNome(void *a, void *b) {
  Pessoa *pess = a;
  char *nome = b;
  return strcmp(pess->nome, nome);
}

int cmpRG(void *a, void *b) {
  Pessoa *pess = a;
  int *rg = b;
  return pess->RG - *rg;
}

int main() {
  List *l = List_alloc();
  Pessoa p[] = {
    {"Eva", 9456},
    {"Adao", 1923},
    {"Caim", 3428},
    {"Abel", 9810}  
  };
  Pessoa *x;
  char keyNome[] = "Adao";
  int  keyRG = 9456;

  x = malloc(sizeof(Pessoa));
  strcpy(x->nome, "Lilith");
  x->RG = 8167;

  
  List_insert(l, &p[0]);
  List_insert(l, &p[1]);
  List_insert(l, &p[2]);
  List_insert(l, &p[3]);
  List_insert(l, x);

  List_print(l, print);

  List_removeByIndex(l, 2);
  List_print(l, print);

  x = List_find(l, keyNome, cmpNome);
  print(x);
  printf("\n");
  List_print(l, print);

  List_removeByValue(l, &keyRG, cmpRG);
  List_print(l, print);

  List_free(l);
  return 0;
}





