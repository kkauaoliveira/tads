#include <stdlib.h>
#include <stdio.h>
#include "Queue.h"

struct Queue {
	int size;
	int begin;
	int end;
	void **items;
};

Queue *Queue_alloc(int size) { 
  Queue *q = malloc(sizeof(Queue));

  if (q) {
    q->size  = size;
    q->begin = -1;
    q->end   = -1;
    q->items = calloc(size, sizeof(void*));

    if (q->items == NULL) {
       free(q);
       q = NULL;
    }
  }
  
  return q;
}

void Queue_free(Queue *q) { 
  if (q) {
    free(q->items);
    free(q);
  }
}

int Queue_isEmpty(Queue *q) {
  if (q)
    return q->begin == -1 && q->end == -1;
  
  return 1;
}

int Queue_next(Queue *q, int index) {
  if (q && index >= 0) 
    return (index + 1) % q->size;    

  return 0;
}

int Queue_isFull(Queue *q) { 
  if (q)
    return Queue_next(q, q->end) == q->begin;
  
  return 0;
}

void Queue_push(Queue *q, void *item) { 
  if (q) {
    if (!Queue_isFull(q)) {

       if (Queue_isEmpty(q))
          q->begin = q->end = 0;
       else
          q->end = Queue_next(q, q->end);
       
       q->items[q->end] = item;
    }  
  }
}

void *Queue_pop(Queue *q) {
  void *item = NULL;
  
  if (q) {
    if (!Queue_isEmpty(q)) {
      item = q->items[q->begin];

      if (q->begin == q->end)
        q->begin = q->end = -1;
      else
        q->begin = Queue_next(q, q->begin);
    }
  }

  return item;
}

void *Queue_begin(Queue *q) { 
  if (q && !Queue_isEmpty(q))
    return q->items[q->begin];

  return NULL;
}

void *Queue_end(Queue *q) { 
  if (q && !Queue_isEmpty(q))
    return q->items[q->end];

  return NULL;
}

void Queue_print(Queue *q, void (*print)(void *)) {
  int i;

  if (q && !Queue_isEmpty(q)) {
    
    for (i=q->begin; i != q->end; i = Queue_next(q, i)) 
      print(q->items[i]);
    
    print(q->items[i]);
    printf("\n");
  }
}






