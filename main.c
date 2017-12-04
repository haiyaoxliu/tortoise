#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "tokenizer.h"
#include "func.h"
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#define wipe printf("\033[H\033[J")
#define NTOKS 32
//#define NCMDS 1

void run(char**, int, int);
int main() {

  init();
  char dir[64];

  char * input;
  while(17){
    getcwd(dir, sizeof(dir));
    printf("%s$ ", dir);
    input = readline();
    input[strlen(input)-1] ='\0'; //credit to michael lee for assistance, null terminate string 
    if (strcmp(input, "exit")==0){
      exit(1);
    }
   else if (strstr(input, "cd")){
      char ** args = tokenize(input, " ");
      chdir(args[1]);
    }
    else{
      //loop with strsep through all the semicolons
      char * hermes;
      hermes = strsep(&input, ";");
      //check for redirect stdout
      if(strchr(hermes, '>')){
        char * bashpart;
        bashpart = strsep(&hermes, ">");
        char ** args = tokenize(bashpart, " ");
        while(hermes[0] == ' '){
          hermes++;
        }
        int fd = creat(hermes, 0777);
        int a = dup(1);
        dup2(fd, 1);
        run(args, a, 0);
      }
      if(strchr(hermes, '<')){
        char* bashpart;
        bashpart = strsep(&hermes, "<");
        char** args = tokenize(bashpart, " ");
        while(hermes[0] == ' '){
          hermes++;
        }
        int fd;
        fd = open(hermes, O_RDONLY | O_CREAT, 0777);
        int b = dup(0);
        dup2(fd, 0);
        run(args, 1, b);
    }


  else{
    char** args = tokenize(hermes, " ");
    run(args, 1, 0);
  }




    }
  }
return 0;  
}


void init() {
  //wipe;
  //printf("-----------------------------\ntortoise shell by alex&haiyao\ncurrent user:\t%s\n-----------------------------\n",getenv("USER"));
  //sleep(1);
  wipe;
}

void loop() {

  char* input; //input string
  char** args; //arguments
  char** cmds; //separate commands;
  char dir[64];
  int i;

  while(17) {
    i = 0;
    getcwd(dir,sizeof(dir));
    
    printf("%s$ ", dir);
    input = readline();

    if(strcmp(input, "exit") == 0){
      exit(0);
    }
    if(strstr(input, "cd")){
      args = tokenize(input, "cd");
      chdir(args[1]);
      }  
    else{
    cmds = tokenize(input,";");
     while(cmds[i]) {


      printf("test1\n");
       if(strchr(cmds[i], ">") != NULL){
         char* bashpart = strsep(&cmds[i], ">");
         char** moddedargs = tokenize(cmds[i], " ");
         printf("test\n");
         while(cmds[i][0] == ' '){
           cmds[i]++; //creds to michael lee for helping me fix bug w spaces at front 
         }
         int fd = open(cmds[i], O_WRONLY | O_CREAT | O_TRUNC, 0777);
         int a = dup(1);
         dup2(fd, 1);
         if(!fork()){
           execvp(moddedargs[0], moddedargs);
         }
         else{
           int status;
           wait(&status);
           if(a != 1){
             dup2(a, 1);
           }
         }
       }

      if(strchr(cmds[i], "<")){
        char* bashpart = strsep(&cmds[i], "<");
        char** moddedargs = tokenize(cmds[i], " ");
        while(cmds[i][0] == ' '){
          cmds[i]++; 
        }
        if(!(strcmp(moddedargs[0], ""))){
          return;
        }
        int fd = open(cmds[i], O_RDONLY | O_CREAT, 0777);
        int b = dup(0);
        dup2(fd, 0);
        if(!fork()){
          execvp(moddedargs[0], moddedargs);
        }
        else{
          int status;
          wait(&status);
          if(b != 0){
            dup2(b, 0);
          }
        }
      }

      else{

      args = tokenize(cmds[i]," \n\t");
      if(!fork()){
        execvp(args[0], args);
      }
      else{
        int status;
        wait(&status);
      }
      }
      i++;
      
     }
     }
  }
}

char* readline() {
  char *input = NULL;

  size_t size = 0;
  getline(&input, &size, stdin);
  
  return input;
}

char** tokenize(char* input, char* delim) {

  //init 
  int size = NTOKS; //# of tokens
  char** tokens = malloc(size * sizeof(char*));
  char* token = strtok(input, delim); //get first token
  int i = 0; //token tracker
  
  //split input str into tokens
  while(token) {
    tokens[i] = token;
    i++;
    //printf("%s\n", token);

    //if we exceed base token#, add some more
    if( i >= size ) {
      size += NTOKS;
      tokens = realloc(tokens, size * sizeof(char*));
    }
    
    //next token
    token = strtok(NULL, delim);
  }
  
  //terminating NULL
  tokens[i] = NULL;

  return tokens;
}

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

  pid_t pid;
  pid = fork();

  if( pid == -1 ) {
    perror("fork error");
  }

  if(!pid) {
    if( execvp(args[0],args) == -1 ) {
      perror("failed to execute command");
    }
    exit(1);
  }
 
  if(pid) {
    wait(NULL);
  }

  return 1;
}

void run(char ** args, int a, int b){
  if(!fork()){
    execvp(args[0], args);
  }
  else{
    int status;
    wait(&status);
    if(a != 1){
      dup2(a, 1);
    }
    if(b != 0){
      dup2(b, 0);
    }
  }
}
//func checker
int func(char** args) {
  int i;
  
  //no command
  if(args[0] == NULL) {
    perror("empty command");
    return 1;
  }
    
  //non forkable commands
  for(i = 0; i < sizeof(extras)/sizeof(char*); i++) {
    if(!strcmp(args[0],extras[i])) {
      return (*funcs[i])(args);
      }
  }
  
  return exc(args);
}

