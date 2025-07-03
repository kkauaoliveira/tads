typedef struct QueueInt QueueInt;

QueueInt *QueueInt_alloc(int size);
void   QueueInt_free(QueueInt *q);
int    QueueInt_isEmpty(QueueInt *q);
int    QueueInt_isFull(QueueInt *q);
void   QueueInt_push(QueueInt *q, int item);
int    QueueInt_pop(QueueInt *q);
int    QueueInt_begin(QueueInt *q);
int    QueueInt_end(QueueInt *q);
void   QueueInt_print(QueueInt *q);
