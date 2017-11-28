#include <stdio.h>
#include "shell.h"
#include "tokenizer.h"
#include "func.h"

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

