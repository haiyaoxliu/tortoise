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
  char** args; //arguments
  char** cmds; //separate commands;
  char dir[64];
  int i;

  while(17) {
    i = 0;
    getcwd(dir,sizeof(dir));
    
    //read usr input
    printf("%s$ ", dir);
    input = readline();

    /*
    if(strchr(input, ';')) {
      char* goteinput;
      char** goteargs;
      char** gotegote;
      int i = 0;
      while(input) {
        goteinput = strsep(&input, ";");
        goteargs = tokenize(goteinput);
        if(!func(goteargs)){
          break;
        }
        i++;
      }
    }
    */

    //else {
    cmds = tokenize(input,";");
    //printf("parsed\n");
    //execute
    while(cmds[i]) {
      args = tokenize(cmds[i]," \n\t");
      i++;
      if(!func(args)) {
	return;
      }
    }
  }
}
