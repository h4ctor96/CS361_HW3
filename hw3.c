//this is the start of my hw3
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void sigint_handler(int sig){
  char msg[] = "caught sigint\n";
  write(1, msg, sizeof(msg));
  //exit(0); // this should stop it from exiting
}
void sigstop_handler(int sig){
  char msg[] = "caught sigstp\n";
  write(1, msg, sizeof(msg));
  //exit(0);
}

int main(){
    //TODO: Ctrl+C triggers SIGINT, and Ctrl+Z triggers SIGSTP 
    //neither works
    //signal(SIGINT, sigint_handler);
    //signal(SIGTSTP, sigstop_handler);

    
    //create some space for our strings
    char line[500];

    //print prompt
    printf("361>");
    //read line from terminal
    fgets(line, 500, stdin);

    int length = strlen(line);
    line[length-1] = '\0';

    char* argsarray[20];
    int i = 0;
    for(i=0; i < 20; ++i)
        argsarray[i] = (char*)malloc(100*sizeof(char));

    while(strcmp(line,"exit") != 0)
    {
        //break the string up into words
        for(i=0; i < 20; ++i)
        argsarray[i] = (char*)malloc(100*sizeof(char));

        char* word = strtok(line, " ");
        char* filename;
        i = 0;
        while (word) {
            //printf("word: %s\n", word);
            //copy a word to the arg array
            strcpy(argsarray[i], word);
            //get next word
            word = strtok(NULL, " ");
            i = i + 1;
            //if(*word == '<' || *word == '>'){//word remains as symbol
              //  filename = strtok(NULL, " ");
                //break;
            //}
        }
        argsarray[i] = NULL;
        //OPTIONAL: print out array 
        for (int j=0;j<i;j++)
            printf("argsarray[%d]: %s\n", j, argsarray[j]);

        // reading child's pid
        int pid = fork();
        if (pid == 0){
            //printf("PID: %d\n", getpid());
            //exit(0); //exit for now, redirection might have to go here
            //TODO: recognize command and execute it
            execvp(argsarray[0], argsarray);//!missing (char*)0
        }
        else{
            int status;
            wait(&status);
            printf("pid:%d status:%d\n", pid, WEXITSTATUS(status));
            //printf("EXIT: %d\n", WEXITSTATUS(status));
        }
/*
        //TODO: set up file redirection
        // dup2(fd1,0) sends output of fd1 to stdin
        if(filename){
            if(*word == '>'){ // add >>
                int fd1 = exec(argsarray[0], argsarray);
                int fd2 = open(filename,O_CREAT);
                dup2(fd2, fd1);
                
            }
            if(*word == '<'){
                int fd2 = open(filename, O_RDONLY);
                dup2(fd2, 0);
                exec(argsarray[0], argsarray);

            }
        }*/

        int index = 0;
        for(index=0;index<i;++index)
            free(argsarray[index]);

        //print prompt for next command
        printf("\n361 >");
        //read line from terminal
        fgets(line, 500, stdin);
        
        length = strlen(line);
        line[length-1] = '\0';

        if(strcmp(line,"exit") == 0)
         exit(0);
    }
    
    return 0;
}
