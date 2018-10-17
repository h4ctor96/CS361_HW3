#include <stdio.h>
#include <string.h>

int main(){

  //create some space for our strings
  char line[500];
  char argsarray[20][100];

  //print prompt
  printf("Please enter a string: ");
  //read line from terminal
  fgets(line, 500, stdin);

  //break the string up into words
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

  //print out our array
  int j=0; 
  for (;j<i;j++){
    printf("argsarray[%d]: %s\n", j, argsarray[j]);
  }  
}
