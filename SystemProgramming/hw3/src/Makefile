all: main hw3 scheduler.o

main: main.c
	gcc main.c -o main

hw3: hw3.c scheduler.o
	gcc hw3.c scheduler.o -o hw3

scheduler.o: scheduler.c
	gcc -c scheduler.c -o scheduler.o
clean:
	rm -f main hw3 scheduler.o
