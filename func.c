#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

//func checker
int func(char** args) {
  
}

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

