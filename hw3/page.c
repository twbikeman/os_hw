#include <stdio.h>
#include <stdlib.h>


int main(int argc, char ** argv) {
  unsigned int address = atoi(argv[1]);
  int page = address / (1024 * 4);
  int offset = address % (1024 * 4);
  printf("The address %d contains:\n", address);
  printf("page number = %d\n",page );
  printf("offset = %d\n", offset);
  return 0;
}
