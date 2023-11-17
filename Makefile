prog: main.o roboter.o karte.o
	gcc -o prog main.o roboter.o karte.o
main.o: main.c
	gcc -c main.c

roboter.o: roboter.c
	gcc -c roboter.c

karte.o: karte.c
	gcc -c karte.c
