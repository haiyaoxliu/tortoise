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

char* types[] = {
  "|",
  ">",
  "<"
};

int p(char** first, char** rest) {
  int piped[2]; 
  pid_t i, o;
  char* err;
 
  if (pipe(piped) < 0) {
    printf("\nPipe could not be initialized");
    return 0;
  }

  i = fork();

  if(i < 0) {
    perror("fork error");
    return 0;
  }
 
  if(!i) {
    close(piped[0]);
    dup2(piped[1], STDOUT_FILENO);
    close(piped[1]);
 
    if(execvp(first[0], first) < 0) {
      sprintf(err, "failed to execute %s", first[0]);
      perror(err);
      exit(1);
    }

  }

  if(i) {
    o = fork();
 
    if (o < 0) {
      perror("fork error");
      return 0;
    }
 
    if (!o) {
      close(piped[1]);
      dup2(piped[0], STDIN_FILENO);
      close(piped[0]);
      
      if (execvp(rest[0], rest) < 0) {
	printf("\nCould not execute command 2..");
	exit(0);
      }
    }

    wait(NULL);
    wait(NULL);
  }

  return 1;
}

int rr(char** first, char** rest) {
  //code here
  return 0;
}

int lr(char** first, char** rest) {
  //code here
  return 0;
}

int (*typef[]) (char**,char**) = {
  &p,
  &rr,
  &lr
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

int op(char** first, char** rest, char* op) {
  int i;
  //pipe/redirect
  for(i = 0; i < sizeof(types)/sizeof(char*); i++) {
    if(!strcmp(op,types[i])) {
      return (*typef[i])(first, rest);
    }
  }
  
  return 0;
}
