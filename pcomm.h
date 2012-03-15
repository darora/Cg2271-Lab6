#ifndef PCOMM
#define PCOMM

typedef struct t
{
  int head, tail;
  int size;
  int count;
  int *q;
} pq_t;

pq_t *pq_create(int);
void pq_put(pq_t *, int);
int pq_get(pq_t *);
void pq_destroy(pq_t *);
#endif
