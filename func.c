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

int piped(char* first, char* rest) {
  printf("in func\n");
  int k = 0;
  /*  while(first[k]) {
    printf("%s\n",first[k]);
    k++;
  }
  k = 0;
  while(rest[k]) {
    printf("%s\n",rest[k]);
    k++;
  }
  */
  FILE* f = popen(first,"w");
  
  /*  int pipefd[2];
  pid_t i, o;
  char* err;
  if (pipe(pipefd) < 0) {
    printf("pipe error");
    return 0;
    }
  pipe(pipefd);

  i = fork();
  printf("forked %d\n",i);
  
  if(i < 0) {
    perror("fork error");
    return 0;
  }
  
  //printf("no fork error\n");
  if(!i) {
    printf("child1\n");
    close(pipefd[0]);
    printf("closed1");
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
 
    printf("about to exec\n");
    if(execvp(first[0], first) < 0) {
      sprintf(err, "failed to execute %s", first[0]);
      perror(err);
      exit(1);
    }

  }
  else {
    //printf("creating child 2\n");
    o = fork();
 
    if (o < 0) {
      perror("fork error");
      return 0;
    }
 
    if (!o) {
      printf("\nchild2\n");
      close(pipefd[1]);
      printf("closed2\n");
      dup2(pipefd[0], STDINFILENO);
      close(pipefd[0]);
      
      if (execvp(rest[0], rest) < 0) {
	printf("failed to execute %s", rest[0]);
	exit(0);
      }
    }
    else {
      wait(NULL);
      wait(NULL);
    }
  }
  */
  return 1;
}


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
  int i = 0;
  
  /*while(args[i]) {
    printf("%s\n",args[i]);
    if(!strcmp(args[i],"|")) {
      printf("pipe found\n");
      args[i] = NULL;
      return piped(args, &args[i+1]);
    }
    i++;
    }*/
  
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

/*int operate(char** first, char** rest, char* op) {
  int i;
  //pipe/redirect
  printf("op\n");
  for(i = 0; i < sizeof(types)/sizeof(char*); i++) {
    if(!strcmp(op,types[i])) {
      //printf("%s\n\n%d\n\n\n",types[i],i);
      printf("the fuck\n");
      return ppp(first, rest);
    }
  }
  
  return 0;
  }*/
