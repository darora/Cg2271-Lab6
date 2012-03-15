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
        pthread_mutex_init(&(tmp->mutex), NULL);
        pthread_cond_init(&(tmp->empty), NULL);
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
    if(q->q) {
      free(q->q);
      pthread_mutex_destroy(&(q->mutex));
      pthread_cond_destroy(&(q->empty));
    }
    free(q);
  }
}

void pq_put(pq_t *q, int b)
{
  pthread_mutex_lock(&(q->mutex));
  while (q->count == q->size)
    pthread_cond_wait(&(q->empty), &(q->mutex));

  // No longer full. Now add in the item
  q->q[q->head]= b;
  q->head = (q->head + 1) % q->size;
  q->count++;
  if (q->count == 1)
    pthread_cond_broadcast(&(q->empty));
  pthread_mutex_unlock(&(q->mutex));
}

int pq_get(pq_t *q)
{
  pthread_mutex_lock(&(q->mutex));
  int ret;
  while (q->count == 0)
    pthread_cond_wait(&(q->empty), &(q->mutex));

  // We now have something to read.
  ret=q->q[q->tail];
  q->tail = (q->tail + 1) % q->size;
  q->count--;
  if (q->count == q->size-1)
    pthread_cond_broadcast(&(q->empty));
  pthread_mutex_unlock(&(q->mutex));
  return ret;
}
