#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "tokenizer.h"
#include "func.h"
#include <string.h>
#include <unistd.h>

//clear
#define wipe printf("\033[H\033[J")


int main(int argc, char **argv) {

  init();
  loop();
  
  return 0;
}

void init() {
  //wipe;
  //printf("-----------------------------\ntortoise shell by alex&haiyao\ncurrent user:\t%s\n-----------------------------\n",getenv("USER"));
  //sleep(1);
  wipe;
}

//loop
void loop() {

  //init
  char* input; //input string
  char*** args; //arguments
  char dir[64];
  int i = 0;

  while(1) {
    getcwd(dir,sizeof(dir));
    
    //read usr input
    printf("%s$ ", dir);
    input = readline();

    //tokenize input
    args = parse(input);
    //printf("\n\n%s\n\n",input);
    while(args[i]) {
      //execute
      if(!func(args[i])) {
        break;
      }
      i++;
   }
  }
}
