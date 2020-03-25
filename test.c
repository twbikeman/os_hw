#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

//extern errno;

int main() {
  int i;
  char input[80];
  char output[80];

  char prompt[] = "input: ";
  char prompt2[] = "source: ";

  write(0, prompt, sizeof(prompt));
  
  i = read(0, input, 79);
  input[i-1] = '\0';

  write(0, prompt2, sizeof(prompt2));

  i = read(0, output, 79);
  output[i-1] = '\0';

  

   int sour = open(input, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR); 
   int dest = open(output, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR); 

 char buf[512]; 
 i = read(sour, buf, 512); 
 while(i != 0) {
   write(dest, buf, i);
   i = read(sour, buf, 512);
 }
 close(dest);
 close(sour);


 return 0;
}
