all: shell.o tokenizer.o func.o
	gcc -o turtle shell.o tokenizer.o func.o

shell.o: shell.c shell.h
	gcc -c shell.c

tokenizer.o: tokenizer.c tokenizer.h
	gcc -c tokenizer.c

func.o: func.c func.h
	gcc -c func.c

run: all
	./turtle

clean:
	rm turtle
	rm *.o