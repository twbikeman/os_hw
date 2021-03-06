#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1


int main() {
  char write_msg[BUFFER_SIZE];
  char read_msg[BUFFER_SIZE];
  char invert_msg[BUFFER_SIZE];
  int fd[2];
  int fd1[2];

  pid_t pid;

  if (pipe(fd) == -1) {
    fprintf(stderr, "Pipe failed");
    return 1;
  }

  if (pipe(fd1) == -1) {
    fprintf(stderr, "Pipe1 failed");
    return 1;
  }

  pid = fork();
  if (pid < 0) {
    fprintf(stderr, "Fork failed");
    return 1;
  }
  
  if (pid > 0) { /* parent process */

    int i = read(0, write_msg, BUFFER_SIZE);
    write_msg[i-1] = '\0'; 

    printf("Parent send: %s\n", write_msg);
    
    close(fd[READ_END]);
    write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
    close(fd[WRITE_END]);


    close(fd1[WRITE_END]);
    read(fd1[READ_END], invert_msg, BUFFER_SIZE);
    printf("Parent receive: %s\n", invert_msg);
    close(fd1[READ_END]);
    

  }
  else { /* child process */
    close(fd[WRITE_END]);
    read(fd[READ_END], read_msg, BUFFER_SIZE);
    printf("Child receive: %s\n", read_msg);
    close(fd[READ_END]);



    

    // XOR 00100000 ==> 0x20
    for(int i = 0; i < strlen(read_msg); i++) {
      if ( ('a' <=read_msg[i] && read_msg[i]<= 'z' )|| ('A' <=read_msg[i] && read_msg[i] <= 'Z'))
      read_msg[i] = read_msg[i] ^ 0x20;
    }



    
    close(fd1[READ_END]);
    write(fd1[WRITE_END], read_msg, strlen(read_msg) + 1);
    printf("Child send : %s\n", read_msg);
    close(fd1[WRITE_END]);

    
  }

  return 0;
  
}
