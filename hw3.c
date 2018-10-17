//this is the start of my hw3
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



main(){

    
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
        char *word = strtok(line, " ");
        int i = 0;
        while (word) {
            printf("word: %s\n", word);
            //copy a word to the arg array
            strcpy(argsarray[i], word);
            //get next word
            word = strtok(NULL, " ");
            i = i + 1;
        }
        //OPTIONAL: print out our array 
        for (int j=0;j<i;j++){
        printf("argsarray[%d]: %s\n", j, argsarray[j]);

        // reading child's pid
        int pid = fork();
        if (pid == 0){
            printf("PID: %d\n", getpid());
            //exit;
            //TODO: recognize command and execute it
            execv(argsarray[0], argsarray);
        }
        else{
            printf("pid:%d status:&d\n", getpid(), 0);//status?
            int status;
            wait(&status);
            printf("EXIT: %d\n", WEXITSTATUS(status));
        }

        //TODO: set up file redirection
        // dup2(fd1,0) sends output of fd1 to stdin





        //TODO: Ctrl+C triggers SIGINT, and Ctrl+Z triggers SIGSTP



        //print prompt for next command
        printf("\n361>");
        //read line from terminal
        fgets(line, 500, stdin);
    }
    
  }  

}
