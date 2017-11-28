/* TOKENIZER

functions

readline():
  read user command line input
  
tokenize(char*):
  splits input line from readline on whitespace - " \t\n"

definitions:

TOKSIZE:
  intial tokens** length

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TOKSIZE 32 

//read input str
char* readline() {

  //input str
  char *input = NULL;
 
  //getline auto allocates
  size_t size = 0;
  getline(&input, &size, stdin);
  
  return input;
}

//tokenize input string
char** tokenize(char *input) {

  //init 
  int size = TOKSIZE; //# of tokens
  char **tokens = malloc(size * sizeof(char*));
  char *token = strtok(input, " \n\t"); //get first token
  int i = 0; //pos tracker
  
  //split input str into tokens
  while(token) {
    tokens[i] = token;
    i++;
    
    //if we exceed base token#, add some more
    if( !(i - size) ) {
      size += TOKSIZE;
      tokens = realloc(tokens, size * sizeof(char*));
    }
    
    //next token
    token = strtok(NULL, " \n\t");
  }
  
  //terminating NULL
  tokens[i] = NULL;

  return tokens;
}
