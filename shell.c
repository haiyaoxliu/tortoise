#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"


int main(int argc, char **argv) {
  //main shell loop
  loop();
  
  return 0;
}

//loop
void loop() {

  //init
  char *input; //input string
  char **args; //arguments

  while(1) {
    
    //read usr input
    printf("notatortoise$ ");
    input = readline();

    //tokenize input
    args = tokenize(input);
    
    //insert a custom catch here for cd, exit, multiple commands, etc
    //execute
    if(!exc(args)) {
      break;
    }
  }
}

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
  int size = 32; //# of tokens
  char **tokens = malloc(size * sizeof(char*));
  char *token = strtok(input, " \n\t"); //get first token
  int i = 0; //pos tracker
  
  //split input str into tokens
  while(token) {
    tokens[i] = token;
    i++;
    
    //if we exceed base token#, add some more
    if( !(i - size) ) {
      size += 32;
      tokens = realloc(tokens, size * sizeof(char*));
    }
    
    //next token
    token = strtok(NULL, " \n\t");
  }
  
  //terminating NULL
  tokens[i] = NULL;

  return tokens;
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

