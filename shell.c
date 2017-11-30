#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "tokenizer.h"
#include "func.h"
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {


  init();
  //main shell loop
  loop();
  
  return 0;
}

void init() {
  printf("\033[H\033[J");
}

//loop
void loop() {

  //init
  char* input; //input string
  char** args; //arguments
  char dir[64];

  while(1) {
    getcwd(dir,sizeof(dir));
    
    //read usr input
    printf("%s$ ", dir);
    input = readline();

    //tokenize input
    args = tokenize(input);
    //printf("\n\n%s\n\n",input);

    //execute
    if(!func(args)) {
        break;
    }
  }
}
