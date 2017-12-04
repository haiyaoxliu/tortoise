all: 
	gcc main.c
shell.o: shell.c shell.h
	gcc -c shell.c

tokenizer.o: tokenizer.c tokenizer.h
	gcc -c tokenizer.c

func.o: func.c func.h
	gcc -c func.c

run: all
	make
	./a.out

clean:
	rm turtle
	rm *.o
