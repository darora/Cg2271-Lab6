#include <pthread.h>
#include <stdlib.h>

#include "pcomm.h"

pq_t *pq_create(int size)
{
  pq_t *tmp;

  tmp=(pq_t *) malloc(sizeof(pq_t));
  if(tmp != NULL)
  {
    tmp->q = (int *) calloc((size_t) size, sizeof(int));
    if(tmp->q)
      {
        tmp->head=0;
        tmp->tail=0;
        tmp->size=size;
        tmp->count=0;
      }
    else
      {
        free(tmp);
        tmp=NULL;
      }
  }

  return tmp;
}

void pq_destroy(pq_t *q)
{
  if(q)
  {
    if(q->q)
      free(q->q);
    free(q);
  }
}

void pq_put(pq_t *q, int b)
{
        // Exit if full.
  if(q->count == q->size)
    return;

  // No longer full. Now add in the item
  q->q[q->head]= b;
  q->head = (q->head + 1) % q->size;
  q->count++;
}

int pq_get(pq_t *q)
{
  int ret;

        // Exit if empty
  if(q->count == 0)
    return -999;

  // We now have something to read.
  ret=q->q[q->tail];
  q->tail = (q->tail + 1) % q->size;
  q->count--;

  return ret;
}
