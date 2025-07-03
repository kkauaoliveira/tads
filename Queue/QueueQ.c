#include <stdlib.h>
#include <stdio.h>
#include "QueueQ.h"
#include "Queue.h"
#include "QueueInt.h"

struct QueueQ {
  int size;
  Queue *queues;
};

QueueQ *QueueQ_alloc(int size) { 
  QueueQ *qq = malloc(sizeof(QueueQ));

  if (qq) {
    qq->size = size;
    qq->queues = Queue_alloc(size);

    for (int i=0; i<size; i++) {
      Queue_push(qq->queues, QueueInt_alloc(size));
    }
  }
  
  return qq;
}

void QueueQ_free(QueueQ *qq) { 
  if (qq) {
    Queue_free(qq->queues);
    free(qq);
  }
}

int QueueQ_isEmpty(QueueQ *qq) {
  if (qq)
    return Queue_isEmpty(qq->queues);
  
  return 1;
}

int QueueQ_isFull(QueueQ *qq) {
  if (qq)
    return Queue_isFull(qq->queues);
  
  return 0;
}

void QueueQ_push(QueueQ *qq, int item, int index) { 
  Queue    *qaux = NULL;
  QueueInt *qint = NULL;

  if (qq) {
     qaux = Queue_alloc(qq->size);

     for (int i=0; !Queue_isEmpty(qq->queues); i++) {
        qint = Queue_pop(qq->queues);
        
        if (i == index)
          QueueInt_push(qint, item);
        
        Queue_push(qaux, qint);
     }

     while (!Queue_isEmpty(qaux))
        Queue_push(qq->queues, Queue_pop(qaux));  
  }
}

int QueueQ_pop(QueueQ *qq, int index) {
  void *itemG = NULL;  

  if (qq) {
    
  }

  return 0;
}

int QueueQ_begin(QueueQ *qq) { 
  if (qq && !QueueQ_isEmpty(qq))
    return 0;

  return 0;
}

int QueueQ_end(QueueQ *qq) { 
  if (qq && !QueueQ_isEmpty(qq))
    return 0;

  return 0;
}

void QueueQ_print(QueueQ *qq) {
  Queue    *qaux = NULL;
  QueueInt *qint = NULL;

  if (qq && !QueueQ_isEmpty(qq)) {
     qaux = Queue_alloc(qq->size); 
      
     while (!Queue_isEmpty(qq->queues)) {
        qint = Queue_pop(qq->queues);
        printf("[");
        QueueInt_print(qint);
        printf("] ");
        Queue_push(qaux, qint);
     }
    
     while (!Queue_isEmpty(qaux))
        Queue_push(qq->queues, Queue_pop(qaux));
     
     printf("\n");
  }
}









