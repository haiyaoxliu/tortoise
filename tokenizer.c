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
#define NTOKS 32 
#define NCMDS 1

char* readline() {
  char *input = NULL;

  size_t size = 0;
  getline(&input, &size, stdin);
  
  return input;
}

char** tokenize(char* input) {

  //init 
  int size = NTOKS; //# of tokens
  char** tokens = malloc(size * sizeof(char*));
  char* token = strtok(input, " \n\t"); //get first token
  int i = 0; //token tracker
  
  //split input str into tokens
  while(token) {
    tokens[i] = token;
    i++;
    printf("%s\n", token);

    //if we exceed base token#, add some more
    if( i >= size ) {
      size += NTOKS;
      tokens = realloc(tokens, size * sizeof(char*));
    }
    
    //next token
    token = strtok(NULL, " \n\t");
  }
  
  //terminating NULL
  tokens[i] = NULL;

  return tokens;
}

char*** parse(char* input) {
  
  printf("b");
  int size = NCMDS;
  char*** cmds = malloc(size * sizeof(char**));
  char* cmd = strtok(input, ";");
  int i = 0;
  printf("bb");
  while(cmd) {
    cmds[i] = tokenize(cmd);
    printf("");
    i++;

    if( i >= size ) {
      size += NCMDS;
      cmds = realloc(cmds, size * sizeof(char**));
    }

    cmd = strtok(NULL,";");
  }

  cmds[i] = NULL;
  return cmds;
  
}
