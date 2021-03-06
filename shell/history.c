#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM 5

char * newHist() {
  return (char *)malloc( NUM * 1024 * sizeof(char));
}

void addHist(char *A,char *line) {
  static int i = 0;
  if (i == 0) {
    strcpy(A , line);
    i++;
  }
  else {
    for(int j = i;j > 0; j--) {
      strcpy(A + 1024 * j , A + 1024 * (j -1));
    }
    strcpy(A , line);
    i++;
    if (i > 10) i = 10;
  }
}



int main() {
  char *A;
  A = newHist();
  addHist(A, "1test");
  addHist(A, "2test");
  addHist(A, "4test");
  addHist(A, "5test");
  addHist(A, "6test");
  printf("%s\n", A );
  printf("%s\n", A + 5 * 1024);
  return 0;
}
