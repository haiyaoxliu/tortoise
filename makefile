all: shell.c
	gcc -o turtle shell.c

run: all
	./turtle

clean:
	rm turtle
