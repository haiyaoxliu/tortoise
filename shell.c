#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "tokenizer.h"
#include "func.h"
#include <string.h>
#include <unistd.h>

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
    //exit

    const char * a = "exit";
    if(!(strcmp(args[0], a))){
        exit(0);
    }


    //cd
    const char * b = "cd";
    if(!(strcmp(args[0], b))){
      chdir(args[1]);
    }
    //execute
    else{
      if(!exc(args)) {
        break;
      }
    }
  }
}

