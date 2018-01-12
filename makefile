jeu: monde.o unite.o action.o main.o
	gcc -o jeu monde.o unite.o action.o main.o

monde.o: monde.c header.h
	gcc -o monde.o -c monde.c

unite.o: unite.c header.h
	gcc -o unite.o -c unite.c

action.o: action.c header.h
	gcc -o action.o -c action.c

main.o: main.c header.h
	gcc -o main.o -c main.c
