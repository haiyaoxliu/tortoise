#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "main.h"

#define wipe printf("\033[H\033[J")
#define NTOKS 32
//#define NCMDS 1

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

char* ops[] = {
  ";",
  "|",
  ">",
  "<"
};

void (*opfs[]) (char**, char*) = {
  &semicolon,
  &ppe,
  &rdirect,
  &ldirect
};

void semicolon(char** first, char* rest) {
  run(first);
  first = NULL;
  interpret(first, rest);
  return;
}

void ppe(char** first, char* rest) {
  return;
}

void rdirect() {
  return;
}

void ldirect() {
  return;
}

char* builtins[] = {
  "cd",
  "exit"
};

int (*funcs[]) (char**) = {
  &tcd,
  &texit
};

int main(int argc, char **argv) {

  init();
  loop();
  
  return 0;
}

void init() {
  wipe;
}

void loop() {

  char* input; //input string
  char** args; //arguments
  char** cmds; //separate commands;
  char dir[64];
  //int i;
 

  while(17) {
    getcwd(dir,sizeof(dir));
    
    printf("%s$ ", dir);
    input = readline();
    
    //int size = NTOKS; //# of tokens
    char** tokens = malloc(NTOKS * sizeof(char*));
    printf("loop ok so far\n\n");
    interpret(tokens, input);
  }
}

void interpret(char** tokens, char* input) {
  printf("inside interpret\n\n");
  //char* delim;
  //strcpy(delim, " \n\t");
  char* token = strtok(input, " \n\t"); //get first token
  
  int i = 0;

  
  while(token) {
    printf("interpret loop\n\n");
    int size = sizeof(tokens)/sizeof(char*);
    //if token is |<>; then exec(|<>;, tokens, address token+token length)
    int j;
    for(j = 0; j < sizeof(ops)/sizeof(char*); j++) {
      printf("inside ops loop\n\n");
      if(!strcmp(token,ops[j])) {
	printf("correct op\n\n");
	tokens[i] = NULL;
	//printf("%s\n\n\n",*(token+strlen(token)));
	execute(token,tokens,strtok(NULL,""));//*(&token+strlen(token))); //something like this - check
	return;
      }
    }

    //else just add token
    tokens[i] = token;
    i++;
    printf("token added\n\n");

    if( i >= size ) {
      size += NTOKS;
      tokens = realloc(tokens, size * sizeof(char*));
    }
    
    //next token
    token = strtok(NULL, " \n\t");
  }
  
  //if end is reached then just exec("",tokens,"")
  tokens[i] = NULL;
  execute(NULL,tokens,NULL);
}

void execute(char* op, char** cmd, char* rest) {
  int i;
  if(op) {
    for(i = 0; i < sizeof(ops)/sizeof(char*); i++) {
      if(!strcmp(op,ops[i])) {
	(*opfs)(cmd, rest);
	return;
      }
    }
  }
  else {
    run(cmd);
  }
  return;
};

void run(char** args) {
  int i;

  if(args[0] == NULL) {
    perror("empty command");
    return;
  }
    
  //non forkable commands
  for(i = 0; i < sizeof(builtins)/sizeof(char*); i++) {
    if(!strcmp(args[0],builtins[i])) {
      (*funcs[i])(args);
      return;
    }
  }
  
  exc(args);
  return;
}
    
void exc(char** args) {

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

  return;
}

char* readline() {
  char *input = NULL;

  size_t size = 0;
  getline(&input, &size, stdin);
  
  return input;
}
