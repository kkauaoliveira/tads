typedef struct QueueQ QueueQ;

QueueQ *QueueQ_alloc(int size);
void    QueueQ_free(QueueQ *q);
int     QueueQ_isEmpty(QueueQ *q);
int     QueueQ_isFull(QueueQ *q);
void    QueueQ_push(QueueQ *q, int item, int index);
int     QueueQ_pop(QueueQ *q, int index);
int     QueueQ_begin(QueueQ *q);
int     QueueQ_end(QueueQ *q);
void    QueueQ_print(QueueQ *q);
