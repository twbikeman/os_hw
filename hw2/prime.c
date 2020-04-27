#include <pthread.h>
#include <stdio.h>
#include <math.h>

int prime(int x) {
  int i;
  for (i = 2; i <= (int)sqrt((double)x); i++)
    if (x % i == 0) return 0;
  return 1;
}


int  calcPrime(int x, int *buf) {
  int i, num = 0;
  for (i = 2; i <= x ; i++)
    if (prime(i) == 1) {
      *buf++ = i;
      num++;
    }   
  return num;
}

void * thread_actions(void *num) {
  int buf_num = *(int *)num;
    int buf[buf_num];
    int result_num;
    result_num = calcPrime(buf_num, buf);
    int i;
    for (i = 0; i < result_num; i++)
      printf("%d\t", buf[i]);
    printf("\n");
}

int main() {
  pthread_t  prime_t;
  int num;
  scanf("%d", &num);
  pthread_create(&prime_t, NULL, thread_actions, (void *)&num);
  pthread_join(prime_t, NULL);
  return 0;
}
