#include <stdlib.h>
#include <stdio.h>
#include "QueueInt.h"

struct QueueInt {
	int size;
	int begin;
	int end;
	int *items;
};

QueueInt *QueueInt_alloc(int size) { 
  QueueInt *q = malloc(sizeof(QueueInt));

  if (q) {
    q->size  = size;
    q->begin = -1;
    q->end   = -1;
    q->items = calloc(size, sizeof(int));

    if (q->items == NULL) {
       free(q);
       q = NULL;
    }
  }
  
  return q;
}

void QueueInt_free(QueueInt *q) { 
  if (q) {
    free(q->items);
    free(q);
  }
}

int QueueInt_isEmpty(QueueInt *q) {
  if (q)
    return q->begin == -1 && q->end == -1;
  
  return 1;
}

int QueueInt_next(QueueInt *q, int index) {
  if (q && index >= 0) 
    return (index + 1) % q->size;    

  return 0;
}

int QueueInt_isFull(QueueInt *q) { 
  if (q)
    return QueueInt_next(q, q->end) == q->begin;
  
  return 0;
}

void QueueInt_push(QueueInt *q, int item) { 
  if (q) {
    if (!QueueInt_isFull(q)) {
       if (QueueInt_isEmpty(q))
          q->begin = q->end = 0;
       else
          q->end = QueueInt_next(q, q->end);
       
       q->items[q->end] = item;
    }  
  }
}

int QueueInt_pop(QueueInt *q) {
  int item = 0;  
  if (q) {
    if (!QueueInt_isEmpty(q)) {
      item = q->items[q->begin];

      if (q->begin == q->end)
        q->begin = q->end = -1;
      else
        q->begin = QueueInt_next(q, q->begin);
    }
  }

  return item;
}

int QueueInt_begin(QueueInt *q) { 
  if (q && !QueueInt_isEmpty(q))
    return q->items[q->begin];

  return 0;
}

int QueueInt_end(QueueInt *q) { 
  if (q && !QueueInt_isEmpty(q))
    return q->items[q->end];

  return 0;
}

void QueueInt_print(QueueInt *q) {
  int i;

  if (q && !QueueInt_isEmpty(q)) {
    for (i=q->begin; i != q->end; i = QueueInt_next(q, i)) 
      printf("%d ", q->items[i]);
    
    printf("%d", q->items[i]);
  }
}






