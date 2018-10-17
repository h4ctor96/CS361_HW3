#include <stdio.h>
#include <stdlib.h>

int main() {

  int pid = fork();
  if (pid == 0) {
    printf("I am the child!  I have pid %d.\n", getpid());
    exit(6);
  } else {
    printf("I am the parent.  I am waiting for my child %d to die.\n", pid);
    int status;
    wait(&status);
    printf("My child has died with status %d. :(\n", WEXITSTATUS(status));
  }
}
