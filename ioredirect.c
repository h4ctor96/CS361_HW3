#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
  char buf1[20];
  char buf2[20];
  char buf3[20];
  char buf4[20];
  
  int fd1 = open("sampletext1.txt", O_RDONLY);
  int fd2 = open("sampletext2.txt", O_RDONLY);

  read(fd1, buf1, 19);
  buf1[19] = '\0';
  printf("%s\n", buf1);

  read(fd2, buf2, 19);
  buf2[19] = '\0';
  printf("%s\n", buf2);

  dup2(fd1, fd2);

  read(fd1, buf3, 19);
  buf3[19] = '\0';
  printf("%s\n", buf3);

  read(fd2, buf4, 19);
  buf4[19] = '\0';
  printf("%s\n", buf4);

}
