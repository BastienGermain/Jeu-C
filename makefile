all: jeu

jeu: monde.o unite.o main.o
	gcc -o jeu monde.o unite.o main.o

monde.o: monde.c header.h
	gcc -o monde.o -c monde.c -ansi -pedantic

unite.o: unite.c header.h
	gcc -o unite.o -c unite.c -ansi -pedantic

main.o: main.c header.h
	gcc -o main.o -c main.c -ansi -pedantic

clean:
	rm -rf *.o

mrproper: clean
	rm -rf jeu
				
