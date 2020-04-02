#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

int main(int argc, const char *argv[]) {

  int fdread = open(argv[1], O_RDONLY);
  int fdwrite = open(argv[2], O_APPEND | O_WRONLY | O_CREAT, 0666);

  char *buff;
  ssize_t  size;




  // for(;;) { 
  //size = read(fdread, buff, 1); 
  // if (size !=1) break; 
  //write(fdwrite, buff, 1);
  // }


  for (;;) {
     size = read(fdread, buff, 1);
     if (size != 1) break;
     write(fdwrite, buff, 1);
    }
  

  return 0;
} 
