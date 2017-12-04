#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "tokenizer.h"
#include "func.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h> 
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
  char* user = getenv("USER");
  int i;

  while(17) {
    i = 0;
    getcwd(dir,sizeof(dir));
    
    //read usr input
    printf("%s-%s$ ", dir,user);
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
      //char** first;
      //char** rest;
      /*int j = 4;
      int k = 0;
      char* cmd;
      strcpy(cmd, cmds[i]);
      char** split;
      

      for(j = 0; j < sizeof(ops)/sizeof(char*); j++) {
	split = tokenize(cmd,ops[j]);
	
	while(split[k]) k++;
	if(k>1) {
	  printf("inside, %d\n\n%s\n\n%s\n\n",k,split[0],split[1]);
	  char** f = tokenize(split[0]," \n\t");
 	  char** r = tokenize(split[1]," \n\t");
	  //k = 0;
	  //while(
	  //operate(&cmd,&cmd,"|");
	  printf("tokenized\n\n");

 	  operate(f,r,ops[j]);
	  printf("ran correctly\n\n");
	  j = 4;
	}
      }

      if(j != 4) {*/
      int k = 0;
      char* cmd = cmds[i];
      char** split = tokenize(cmd, "|");
      while(split[k]) k++;
      if(k>1) {
	if(!piped(split[0],split[1])) {
	  return;
	}
	break;
      }

      args = tokenize(cmds[i]," \n\t");
      
      i++;
      if(!func(args)) {
	return;
	//}
      }
    }
  }
}
