#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

#define LOCKED 1

int TestAndSet(int * lockPtr) {

  int oldValue;
  oldValue = *lockPtr;
  *lockPtr = LOCKED;
  return oldValue;
}

volatile int lock = 0;



void * child(void * message) {
    while(TestAndSet(&lock) == 1);
    printf("child\n");
    lock = 0;
};


int main(int argc, char **argv) {
  pthread_t t1, t2;
  pthread_create(&t1, NULL, child, NULL);
  pthread_create(&t2, NULL, child, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);

  return 0;
}
