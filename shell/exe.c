#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define NUM 10

char * newHist() {
  return (char *)calloc( 1, NUM * 1024 * sizeof(char));
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
    if (i > NUM) i = NUM;
  }
}

void showHist(char *A) {
  int pos = 0;
  for (int j = 0; j < NUM; j++) {
    if (*(A + 1024 * j) == '\0') {
      pos = j;
      break;}
  }
  if (pos == 0) pos = NUM;
  

  
  for (int i = 0; i < pos; i++)
    printf("%2d: %s\n", i, A + 1024 * i);
}




void execute(char **argv) {

  pid_t pid;
  int status;

  if ((pid = fork()) < 0) {
    printf("*** ERROR: forking child process failed\n");
    exit(1);

  }
  else if (pid == 0) {
    if (execvp(*argv, argv) < 0) {
      printf("*** ERROR: exec failed\n");
      exit(1);
    }
    
  }
  else {
    while (wait(&status) != pid); 
  }
  
}


void parse(char *line, char **argv) {

  while (*line != '\0') {
    while (*line == ' ' || *line == '\t' || *line == '\n')
      *line++ = '\0';
    *argv++ = line;
    while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n')
      line++;
  }
  *argv = '\0';
 
}





int main(void)  {

  char line[1024];
  char *argv[64];
  char *hist;
  char *pos;
  hist = newHist();
  while (1) {
    printf("SHELL -> ");
    fgets(line, 1023, stdin);
    pos = strchr(line, '\n');
    while (*(pos - 1) == '\t' || *(pos - 1) == ' ')
      pos--;
    *pos = '\0';
    printf("--------------\n");
    
    


    
    if (strcmp(line, "exit") == 0)
      exit(0);
    else if(line[0] == '!') {
      strcpy(line, hist + 1024 * (atoi(&line[1])));
      printf("%s\n",line);
      addHist(hist, line);
      if (strcmp(line, "history") == 0) showHist(hist);
      else {
      parse(line, argv);
      execute(argv);
      }
    }
    else if(strcmp(line, "history") == 0) {
      addHist(hist, line);
      showHist(hist);
      printf("-----------\n");
    }
    else {
      addHist(hist, line);
      parse(line, argv);
      execute(argv);
    }
  }


  /* char prog[] = "cp"; */
  /* char in[] = "this"; */
  /* char out[] = "out"; */
  /* char *argv[4]; */
  /* int status; */
  /* pid_t pid; */

  /* argv[0] = prog; */
  /* argv[1] = in; */
  /* argv[2] = out; */
  /* argv[3] = '\0'; */

  /* execute(argv); */
  

return 0;
}
