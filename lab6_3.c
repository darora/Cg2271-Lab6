#include <stdio.h>
#include <pthread.h>
#include "pcomm.h"

pq_t *queue;

void *reader(void *p)
{
  // Read and print integers from the queue.

  int i, sum=0, val;
  printf("READER thread created\n");

  for(i=0; i<50; i++)
    {
      val=pq_get(queue);
      printf("Read %d from the queue\n", val);
      sum+=val;
    }

  printf("Final sum of numbers read from the queue is %d\n", sum);
  pthread_exit(NULL);
}

void *writer(void *p)
{
  int i, n;
  printf("Writer thread %d created\n", p);
  for(i=0; i<10; i++)
    {
      // Thread 0 will write 0 to 9, thread 1 will write 10 to 19, etc.
      n=(int) p * 10 + i;
      pq_put(queue, n);
      sleep(1);
    }
  printf("Writer thread %d exiting\n", p);
  pthread_exit(NULL);
}

int main()
{
  int i;
  pthread_t read_thread;
  pthread_t write_threads[5];

  // Create the queue
  queue=pq_create(10);

  pthread_create(&read_thread, NULL, reader, NULL);

  // Launch threads 
  for(i=0; i<5; i++)
    pthread_create(&write_threads[i], NULL, writer, (void *) i);

  //pq_destroy(queue);
  pthread_exit(NULL);
  return 0;
}
