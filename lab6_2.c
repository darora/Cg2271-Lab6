#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
sem_t sema1;
void *child(void *p)
{
  sem_wait(&sema1);
  printf("Child %d woken up!\n", p);
  pthread_exit(NULL);
}
int main()
{
  pthread_t threads[10];
  int i;
  sem_init(&sema1, 0, 1);
  for(i=0; i<10; i++)
    pthread_create(&threads[i], NULL, child, (void *) i);
  for(i=0; i<10; i++)
    {
      printf("Sending wake up call number %d\n", i);
      sem_post(&sema1);
    }
  sem_destroy(&sema1);
  pthread_exit(NULL);
}
