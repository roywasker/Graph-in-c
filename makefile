CC=gcc
OBJECT_MAIN=main.o
FLAGS= -Wall -g

all: run

run: $(OBJECT_MAIN) algo.o graph.o
	$(CC) $(FLAGS) -o run $(OBJECT_MAIN) algo.o graph.o

main.o: main.c graph.h algo.h
	$(CC) $(FLAGS) -c main.c

graph.o: graph.c graph.h algo.h
	$(CC) $(FLAGS) -c graph.c

algo.o: algo.c algo.h graph.h
	$(CC) $(FLAGS) -c algo.c

.PHONY: clean all

clean:
	rm -f *.o *.a run