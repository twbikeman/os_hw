#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MIN_PID 10
#define MAX_PID 20

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




int main() {
  int init;
  init = allocate_map();
  int allocate;
  
  allocate = allocate_pid_index(10);
  allocate = allocate_pid_index(11);
  allocate = release_pid(10);

  
  
  printf("--------------------------\n");
  allocate_pid_show();
  printf("--------------------------\n");
  
  allocate = allocate_pid();
  printf("allocate pid is %d\n", allocate);
  allocate = allocate_pid();
  printf("allocate pid is %d\n", allocate);
  allocate = allocate_pid();
  printf("allocate pid is %d\n", allocate);
  allocate = allocate_pid();
  printf("allocate pid is %d\n", allocate);
  allocate = allocate_pid();
  printf("allocate pid is %d\n", allocate);
  allocate = allocate_pid();
  printf("allocate pid is %d\n", allocate);
  allocate = allocate_pid();
  printf("allocate pid is %d\n", allocate);
  allocate = allocate_pid();
  printf("allocate pid is %d\n", allocate);
  allocate = allocate_pid();
  printf("allocate pid is %d\n", allocate);
  allocate = allocate_pid();
  printf("allocate pid is %d\n", allocate);
  allocate = allocate_pid();
  printf("allocate pid is %d\n", allocate);
  allocate = allocate_pid();
  printf("allocate pid is %d\n", allocate);
  allocate = allocate_pid();
  printf("allocate pid is %d\n", allocate);
  allocate = allocate_pid();
  printf("allocate pid is %d\n", allocate);
  allocate = allocate_pid();
  printf("allocate pid is %d\n", allocate);
  allocate = allocate_pid();
  printf("allocate pid is %d\n", allocate);
  allocate = allocate_pid();
  printf("allocate pid is %d\n", allocate);
  allocate = allocate_pid();
  printf("allocate pid is %d\n", allocate);
  allocate = allocate_pid();
  printf("allocate pid is %d\n", allocate);



  printf("--------------------------\n");
  allocate_pid_show();
  printf("--------------------------\n");
  

  return 0;
}
