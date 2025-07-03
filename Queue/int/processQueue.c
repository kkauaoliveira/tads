#include <stdio.h>
#include "Queue.h"
#define TIME 3
#define SIZE 4

int main() {
    int p, id, time, procs[SIZE] = {17,25,39,46};
    Queue *q = Queue_alloc(SIZE);
    int i;
    
    for (i = 0; i < SIZE; i++)
        Queue_push(q, procs[i]);
        
    while (!Queue_isEmpty(q)) {
        p = Queue_pop(q);
        id = p / 10;
        time = p % 10
        time -= TIME;
    
        if (time > TIME) {
            p = id*10 + time; 
            Queue_push(q, p);
		}
        else
            printf("Processo %d concluído\n", id);
    }
    Queue_free(q);
    return 0;
}
