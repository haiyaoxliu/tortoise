# notatortoise

completed
* binaries, cd, exit
* semicolons
* piping with |
* redirecing stdout with >
* redirecting stdin with <

bugs: after piping, prompt will no longer line up. can be fixed with some redirection, unsure why.

Function headers:

----------------char * readline()-------------------

Reads from stdin

----------------char * *  tokenize(char * input, char * delim)---------------------

Turns a string into tokens split by delim

-----------------void run char * * , int a, int b)-----------------------


Forks off a child, runs. Ints a and b are used to keep track of stdout and stdin, and make sure they stay in the right place in the file table.

-----------------int main()----------------------

Loops, prints out prompt, checks for exit and cd, checks for <, >, and |.



