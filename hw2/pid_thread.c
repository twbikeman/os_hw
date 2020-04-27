#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define MIN_PID 300
#define MAX_PID 5000
#define NUM_USERS 100

int *map;

int allocate_map() {
  map = (int *)calloc(1, (MAX_PID - MIN_PID + 1) / 8 + ((MAX_PID - MIN_PID + 1) % 8 != 0));
  return 1;
}


int allocate_pid_index(int pid) {

  if (pid < MIN_PID || pid > MAX_PID)
    return -1;
  else pid = pid - MIN_PID;
  
  int row = pid / (sizeof(int) * 8);
  int col = pid % (sizeof(int) * 8);
  bool check = false;
  check = ((*(map + row) & (1 << col)) != 0)? true : false;
  if (check == false) {
  *(map + row) = *(map + row) | (1 << col);
  return 1;
  }
  else {
  return -1;
  }
}

int release_pid(int pid) {


  if (pid < MIN_PID || pid > MAX_PID)
    return -1;
  else pid = pid - MIN_PID;
  
  int row = pid / (sizeof(int) * 8);
  int col = pid % (sizeof(int) * 8);
  bool check = false;
  check = ((*(map + row) & (1 << col)) != 0)? true : false;
  if (check == true) {
    *(map + row) = *(map + row) & (-1 ^(1 << col));
    return 1;
  }
  else {
  return -1;
  }
}

    
int allocate_pid_show() {

  for (int pid = 0; pid < 20; pid++) {
    int row = pid / (sizeof(int) * 8);
    int col = pid % (sizeof(int) * 8);
    bool check = false;
    check = ((*(map + row) & (1 << col)) != 0)? true : false;
    if (check)
      printf("pid[%4d] : occupied\n", pid + MIN_PID);
  }
  
}

int allocate_pid() {

  for (int pid = 0; pid < MAX_PID - MIN_PID + 1; pid++) {
    int row = pid / (sizeof(int) * 8);
    int col = pid % (sizeof(int) * 8);
    bool check = false;
    check = ((*(map + row) & (1 << col)) != 0)? true : false;
    if (check == false) {
      allocate_pid_index(pid + MIN_PID);
      return pid + MIN_PID;
    }
  }
  return -1;
  

}



void * thread_actions() {
  int pid_num;
  pid_num = allocate_pid();
  printf("pid %d is occupied.\n", pid_num );
  sleep(rand() % 20);
  release_pid(pid_num);
  printf("pid %d is release.\n", pid_num );
}


int main() {
  int init;
  init = allocate_map();

  srand((unsigned)time(NULL));
  pthread_t threads[NUM_USERS];
  int i;
  for (i = 0; i < NUM_USERS; i++)
    pthread_create(&threads[i], NULL, thread_actions, NULL);
  
  for (i = 0; i <NUM_USERS; i++)
    pthread_join(threads[i], NULL);
  
  
  
  
  return 0;
}
