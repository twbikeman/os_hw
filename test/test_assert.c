#include <assert.h>
#include <string.h>
#include <stdio.h>


int main(int argc, char **argv) {
  int a[3] = {1,2,3};
  int b[3] = {1,2,0};


  assert(memcmp(a, b, 3 *sizeof(int)) == 0);
  
  return 0;
}
