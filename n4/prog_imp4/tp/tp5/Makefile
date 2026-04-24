CC     = gcc
CFLAGS = -Wall -Wextra -std=c99

OBJS = main_llrbt.o llrbt.o

main_llrbt: $(OBJS)
	$(CC) $(CFLAGS) -o main_llrbt $(OBJS)

main_llrbt.o: main_llrbt.c llrbt.h
	$(CC) $(CFLAGS) -c main_llrbt.c

llrbt.o: llrbt.c llrbt.h
	$(CC) $(CFLAGS) -c llrbt.c

clean:
	rm -f $(OBJS) main_llrbt

.PHONY: clean
