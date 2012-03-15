#include <stdio.h>
#include <pthread.h>
#define MAX_COUNT 10
pthread_mutex_t ctr_mutex;
pthread_cond_t ctr_cond;
int ctr;
void *add(void *p)
{
  /* Get a mutex to update ctr */
  while(ctr < MAX_COUNT)
    {
      pthread_mutex_lock(&ctr_mutex);
      ctr++;
      printf("ADD: New value of ctr is %d\n", ctr);
      if(ctr>=MAX_COUNT)
        {
          printf("ADD: Reached limit of %d! Waking up print thread\n", MAX_COUNT);
          pthread_cond_signal(&ctr_cond);
        }
      pthread_mutex_unlock(&ctr_mutex);
      sleep(1);
    }
  pthread_exit(NULL);
}
void *print(void *p)
{
  pthread_mutex_lock(&ctr_mutex);
  printf("PRINT: Current value of ctr is %d\n", ctr);
  if(ctr < MAX_COUNT)
    {
      printf("PRINT: ctr is too small. Zzzz.. g'night!\n");
      pthread_cond_wait(&ctr_cond, &ctr_mutex);
      printf("PRINT: ctr is now %d! Exiting thread.\n", ctr);
    }
  pthread_mutex_unlock(&ctr_mutex);
  pthread_exit(NULL);
}
int main()
{
  pthread_t threads[2];
  ctr=0;
  pthread_mutex_init(&ctr_mutex, NULL);
  pthread_cond_init(&ctr_cond, NULL);
  pthread_create(&threads[0], NULL, add, NULL);
  pthread_create(&threads[1], NULL, print, NULL);
  pthread_join(threads[1], NULL);
  pthread_mutex_destroy(&ctr_mutex);
  pthread_cond_destroy(&ctr_cond);
  pthread_exit(NULL);
}
