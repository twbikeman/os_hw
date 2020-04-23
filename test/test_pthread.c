#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * child() {
  sleep(5);
  printf("test\n");
  return 0;
  
}


int main() {

  pthread_t t;
  pthread_create(&t, NULL, child, NULL);
  pthread_join(t, NULL);
  return 0;
}
