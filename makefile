jeu: monde.o unite.o action.o tour.o partie.o mlv.o main.o
	gcc -o jeu monde.o unite.o action.o tour.o partie.o mlv.o main.o -g -O2 -Wall -Werror `pkg-config --cflags MLV` `pkg-config --libs MLV`

monde.o: monde.c header.h
	gcc -o monde.o -c monde.c

unite.o: unite.c header.h
	gcc -o unite.o -c unite.c

action.o: action.c header.h
	gcc -o action.o -c action.c

tour.o: tour.c header.h
	gcc -o tour.o -c tour.c	

partie.o: partie.c header.h
	gcc -o partie.o -c partie.c

mlv.o: mlv.c header.h
	gcc -o mlv.o -c mlv.c

main.o: main.c header.h
	gcc -o main.o -c main.c
