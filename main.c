#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "tokenizer.h"
#include "func.h"
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#define wipe printf("\033[H\033[J")
#define NTOKS 32
//#define NCMDS 1


int main(int argc, char **argv) {

  init();
  loop();
  
  return 0;
}

void init() {
  //wipe;
  //printf("-----------------------------\ntortoise shell by alex&haiyao\ncurrent user:\t%s\n-----------------------------\n",getenv("USER"));
  //sleep(1);
  wipe;
}

void loop() {

  char* input; //input string
  char** args; //arguments
  char** cmds; //separate commands;
  char dir[64];
  int i;

  while(17) {
    i = 0;
    getcwd(dir,sizeof(dir));
    
    printf("%s$ ", dir);
    input = readline();
      




    cmds = tokenize(input,";");
    while(cmds[i]) {
      args = tokenize(cmds[i]," \n\t");
      i++;
      if(!func(args)) {
	return;
      }
    }
  }
}

char* readline() {
  char *input = NULL;

  size_t size = 0;
  getline(&input, &size, stdin);
  
  return input;
}

char** tokenize(char* input, char* delim) {

  //init 
  int size = NTOKS; //# of tokens
  char** tokens = malloc(size * sizeof(char*));
  char* token = strtok(input, delim); //get first token
  int i = 0; //token tracker
  
  //split input str into tokens
  while(token) {
    tokens[i] = token;
    i++;
    //printf("%s\n", token);

    //if we exceed base token#, add some more
    if( i >= size ) {
      size += NTOKS;
      tokens = realloc(tokens, size * sizeof(char*));
    }
    
    //next token
    token = strtok(NULL, delim);
  }
  
  //terminating NULL
  tokens[i] = NULL;

  return tokens;
}

int tcd(char** args) {
  
  //add error checking
  if(chdir(args[1])) {
    perror("cd error");
  }
  
  return 1;
}

int texit(char** args) {
  return 0;
}

char* extras[] = {
  "cd",
  "exit"
};

int (*funcs[]) (char**) = {
  &tcd,
  &texit
};

//exectue commands
int exc(char** args) {

  pid_t pid;
  pid = fork();

  if( pid == -1 ) {
    perror("fork error");
  }

  if(!pid) {
    if( execvp(args[0],args) == -1 ) {
      perror("failed to execute command");
    }
    exit(1);
  }
 
  if(pid) {
    wait(NULL);
  }

  return 1;
}

//func checker
int func(char** args) {
  int i;
  
  //no command
  if(args[0] == NULL) {
    perror("empty command");
    return 1;
  }
    
  //non forkable commands
  for(i = 0; i < sizeof(extras)/sizeof(char*); i++) {
    if(!strcmp(args[0],extras[i])) {
      return (*funcs[i])(args);
      }
  }
  
  return exc(args);
}

