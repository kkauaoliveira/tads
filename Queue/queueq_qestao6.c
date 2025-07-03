#include <stdio.h>
#include <stdlib.h>
#include "QueueQ.h"

int main() {
  QueueQ *qq = QueueQ_alloc(4);

  QueueQ_push(qq, 5, 2);
  QueueQ_push(qq, 3, 2);
  QueueQ_push(qq, 1, 2);
  
  QueueQ_push(qq, 8, 1);
  QueueQ_push(qq, 4, 1);

  QueueQ_push(qq, 2, 0);
  QueueQ_push(qq, 1, 0);
  QueueQ_push(qq, 9, 0);
  QueueQ_push(qq, 5, 0);

  QueueQ_push(qq, 3, 3);

  QueueQ_print(qq);
  QueueQ_free(qq);

  return 0;
}





