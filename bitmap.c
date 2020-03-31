#include <stdio.h>
#include <stdlib.h>


int main() {


  char *ptr = (char *)calloc(10,1);

  int pid = 101;
  int i, j, k;
  i = 101/8;
  j = 101 & (8-1);
  k =  1 << j;
  if ((ptr[i] & k) == 0) // bit is 0
    ptr[i] = ptr[i] | k;
  
  printf("%d\n", ptr[i]);
  
  
  
  return 0;
}
