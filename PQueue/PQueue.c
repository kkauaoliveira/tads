#include <stdlib.h>
#include <stdio.h>
#include "PQueue.h"

PQueue *PQueue_alloc(int length) {
    PQueue *q = malloc(sizeof(PQueue));

    if (q && length > 0) {
        q->keys = calloc(length, sizeof(int));
        q->n = 0;
        q->length = length;
    }

    return q;
}

void PQueue_free(PQueue *q) {
    if (q) {
        free(q->keys);
        free(q);
    }
}

int PQueue_getMax(PQueue *q) {
    if (q)
        return q->keys[0];

    return 0;
}

void fixDown(int A[], int n, int i) {
    int j = i, f, aux;
    while (2*j+1 < n) {
        f = 2*j+1;
        if ((f <= n-2) && (A[f] < A[f+1]))
            f++;
        if (A[j] >= A[f])
            j = n-1;
        else {
            aux = A[j];
            A[j] = A[f];
            A[f] = aux;
            j = f;
        }
    }
}

int PQueue_removeMax(PQueue *q) {
    int max = 0;
    if (q) {
        max = q->keys[0];
        q->keys[0] = q->keys[q->n-1];
        q->n--;
        fixDown(q->keys, q->n, 0);
    }

    return max;
}

void fixUp(int A[], int m) {
    int i = m, aux;
    while (i >= 0 && A[(i-1)/2] < A[i]) {
        aux = A[(i-1)/2];
        A[(i-1)/2] = A[i];
        A[i] = aux;
        i = (i-1)/2;
    }
}

void PQueue_insert(PQueue *q, int key) {
    if (q) {
        if (q->n < q->length) {
            q->keys[q->n] = key;
            q->n++;
            fixUp(q->keys, q->n-1);
        }
    }
}

void PQueue_increase(PQueue *q, int i, int key) {
    if (q && i >= 0 && i < q->n) {
        if (key > q->keys[i]) {
            q->keys[i] = key;
            fixUp(q->keys, i);
        }
    }
}

void PQueue_decrease(PQueue *q, int i, int key) {
    if (q && i >= 0 && i < q->n) {
        if (key < q->keys[i]) {
            q->keys[i] = key;
            fixDown(q->keys, q->n, i);
        }
    }
}

int pow2(int e) {
    int prod = 1;
    for (int i=0; i<e; i++)
        prod *= 2;
    return prod;
}

void PQueue_print(PQueue *q) {
    if (q) {
        for (int i=0, nivel=0, j=1; i<q->n; i++) {
            printf("%d ", q->keys[i]);

            if (pow2(nivel) == j) {
                printf("\n");
                j = 1;
                nivel++;
            }
            else
                j++;
        }
        printf("\n");
    }
}

int main() {
    int v[9] = {10,5,2, 23,1,9, 2,19,54};
    PQueue *q = PQueue_alloc(20);

    for (int i=0; i<9; i++)
        PQueue_insert(q, v[i]);

    PQueue_print(q);

    for (int i=0; i<9; i++)
        printf("%d ", PQueue_removeMax(q));
    printf("\n");
    return 0;
}