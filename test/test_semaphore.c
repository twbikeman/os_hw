#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void * child(void *arg) {
  sleep(4);
  printf("Just Exisng ...\n");

};



int main(int argc, char ** agrv) {
  pthread_t test;
  pthread_create(&test, NULL, child, NULL);
  pthread_join(test, NULL);
  printf("main\n");
  return 0;
}
