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

  //init
  pid_t pid; //track child
  int status; //wpid status

  pid = fork();

  //child process
  if(!pid) {
    
    //execute command, error catch
    if( execvp(args[0],args) == -1 ) {
      perror("fork error");
    }

    //kill child process
    exit(0);
  }

  //parent process
  if(pid) {

    //wait for forked child to execute
    waitpid(pid,&status,WUNTRACED);
  }

  return 1;
}

//func checker
int func(char** args) {
//insert a custom catch here for cd, exit, multiple commands, etc
    //exit
  int i;

  if(args[0] == NULL) {
    return 1;
  }

  for(i = 0; i < sizeof(extras)/sizeof(char*); i++) {
    if(!strcmp(args[0],extras[i])) {
      return (*funcs[i])(args);
    }
  }
    
  /*
    const char * a = "exit";
    if(!(strcmp(args[0], a))){
        exit(0);
    }


    //cd
    const char * b = "cd";
    if(!(strcmp(args[0], b))){
      
    }
  */
    
  return exc(args);
  
}

