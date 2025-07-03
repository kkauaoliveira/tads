#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

typedef struct {
  char nome[20];
  int idade;
}Pessoa;

void printPessoa(void *a) {
  Pessoa *p = a;
  printf("%s %d\n", p->nome, p->idade);
}

int main() {
  Queue *s = Queue_alloc(4);

  Pessoa p[4] = {
      {"Tigas", 78},
      {"Bartolomeu", 34},
      {"Jonatas", 23},
      {"Leonardo", 51}
  };

  Queue_push(s, &p[0]);
  Queue_push(s, &p[1]);
  Queue_push(s, &p[2]);
  Queue_push(s, &p[3]);
  Queue_push(s, &p[3]);

  Queue_print(s, printPessoa);

  Queue_free(s);

  return 0;
}





