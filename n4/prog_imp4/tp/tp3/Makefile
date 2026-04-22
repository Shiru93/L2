CC     = gcc
CFLAGS = -Wall -Wextra -std=c99

OBJS_HEAP = main_heap.o fonctions.o

all: main_heap

main_heap: $(OBJS_HEAP)
	$(CC) $(CFLAGS) -o main_heap $(OBJS_HEAP)

main_heap.o: main_heap.c
	$(CC) $(CFLAGS) -c main_heap.c

fonctions.o: fonctions.c
	$(CC) $(CFLAGS) -c fonctions.c

clean:
	rm -f $(OBJS_HEAP) main_heap

.PHONY: all clean