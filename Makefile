qwirkle.o: qwirkle.c
	gcc -o qwirkle.o  -c qwirkle.c

main: qwirkle.o main.o
	gcc -o main qwirkle.o main.o

all: main

run: main
	./main

clean: 
	rm main.o qwirkle.o

zip: main.c qwirkle.c qwirkle.h Makefile
	zip main.zip Makefile *.c *.h


      





