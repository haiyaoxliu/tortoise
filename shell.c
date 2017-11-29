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
    
    //execute
    
    if(!func(args)) {
        break;
    }
  }
}
