#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t mutex;


void * child(void * arg) {
  sem_wait(&mutex);
  char num = ((char *)arg)[0];
  sleep(4);
  printf("child test%c\n", num);
  sem_post(&mutex);
}

int main(int argc, char **argv) {

  sem_init(&mutex, 0, 1);
  
  pthread_t t1, t2;

  char a[1] = {'a'};
  
    pthread_create(&t1, NULL, child, (void *)a);
  pthread_create(&t2, NULL, child, (void *)a);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  printf("main test\n");


  
  
  sem_destroy(&mutex);

  return 0;
  
  

}
