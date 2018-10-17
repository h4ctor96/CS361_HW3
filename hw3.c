//this is the start of my hw3
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void sigint_handler(int sig){
  char msg[] = "caught sigint\n";
  write(1, msg, sizeof(msg));
  //exit(0); // this should stop it from exiting
}
void sigstp_handler(int sig){
  char msg[] = "caught sigstp\n";
  write(1, msg, sizeof(msg));
  //exit(0);
}

main(){
    //TODO: Ctrl+C triggers SIGINT, and Ctrl+Z triggers SIGSTP 
    //neither works
    signal(SIGINT, sigint_handler);
    signal(SIGSTP, sigstp_handler);

    
    //create some space for our strings
    char line[500];

    //print prompt
    printf("361>");
    //read line from terminal
    fgets(line, 500, stdin);

    while(line != "exit")
    {
        //break the string up into words
        char argsarray[20][100];
        char* word = strtok(line, " ");
        char* filename;
        int i = 0;
        while (word) {//! need to add condition for < and >
            printf("word: %s\n", word);
            //copy a word to the arg array
            strcpy(argsarray[i], word);
            //get next word
            word = strtok(NULL, " ");
            i = i + 1;
            if(*word == '<' || *word == '>'){//word remains as symbol
                filename = strtok(NULL, " ");
                break;
            }
        }
        //OPTIONAL: print out array 
        for (int j=0;j<i;j++)
            printf("argsarray[%d]: %s\n", j, argsarray[j]);

        // reading child's pid
        int pid = fork();
        if (pid == 0){
            printf("PID: %d\n", getpid());
            //exit(0); //might want to execute later
            //TODO: recognize command and execute it
            fd1 = execv(argsarray[0], argsarray);//!missing (char*)0
        }
        else{
            printf("pid:%d status:&d\n", getpid(), 0);//?status?
            int status;
            wait(&status);
            printf("EXIT: %d\n", WEXITSTATUS(status));
        }

        //TODO: set up file redirection
        // dup2(fd1,0) sends output of fd1 to stdin
        if(filename){ //* this probably goes where the exec happens
            if(*word == '>'){ // add >>
                fd2 = open(filename,O_CREAT);
                dup2(fd2, fd1);
                //?should I use execv here?
            }
            if(*word == '<'){
                fd2 = open(filename,O_RDONLY);
                dup2(fd1, fd2);
                //?should I use execv here?
            }
        }


        //print prompt for next command
        printf("\n361>");
        //read line from terminal
        fgets(line, 500, stdin);
    }
    
  }  

}
