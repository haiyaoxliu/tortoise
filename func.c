#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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

