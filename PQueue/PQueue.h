typedef struct PQueue PQueue;

struct PQueue {
    int *keys;
    int n;
    int length;
};

PQueue *PQueue_alloc(int length);
void    PQueue_free(PQueue *q);
int     PQueue_getMax(PQueue *q);
int     PQueue_removeMax(PQueue *q);
void    PQueue_insert(PQueue *q, int key);
void    PQueue_increase(PQueue *q, int i, int key);
void    PQueue_decrease(PQueue *q, int i, int key);
void    PQueue_print(PQueue *q);
