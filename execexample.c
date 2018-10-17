#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

  char *argsarray[] = {"/bin/ls", "-l", (char *)0};
  
  int pid = fork();
  if (pid == 0) {
    printf("Child with pid %d, about to exec ls\n", getpid());
    execv(argsarray[0], argsarray);
  } else {
    printf("I am the parent.  I am waiting for my child %d to die.\n", pid);
    int status;
    wait(&status);
    printf("My child has died with status %d. :(\n", WEXITSTATUS(status));
  }
}
