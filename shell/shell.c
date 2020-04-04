#include <stdio.h>

void makeToken(char *line, char **argv) {
    while(*line != '\0') {

    while (*line == '\t' || *line == ' ' || *line == '\n'){
      *line++ = '\0';
    }
    *argv++ = line;
    while(*line != '\0' && *line != '\t' && *line != ' ' && *line != '\n'){
      line++;
    }  
  }
  *argv = '\0';
}


int main() {
  char a[] = " 123 234 567";
  char *b[5];

  makeToken(a, b);

  int i = 0;

  while(1) {
    if (b[i] == 0) break;
    i++;
  }
  printf("%d\n", i);
  
  printf("%s\n", b[0]);
  printf("%s\n", b[1]);
  printf("%s\n", b[2]);

   
  return 0;
}
