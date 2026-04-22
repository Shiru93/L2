CC     = gcc
CFLAGS = -Wall -Wextra -std=c99

OBJS = main_expr.o fonctions.o binary_tree.o stack_link.o queue_link.o

main_expr: $(OBJS)
	$(CC) $(CFLAGS) -o main_expr $(OBJS)

main_expr.o: main_expr.c
	$(CC) $(CFLAGS) -c main_expr.c

fonctions.o: fonctions.c
	$(CC) $(CFLAGS) -c fonctions.c

binary_tree.o: binary_tree.c
	$(CC) $(CFLAGS) -c binary_tree.c

stack_link.o: stack_link.c
	$(CC) $(CFLAGS) -c stack_link.c

queue_link.o: queue_link.c
	$(CC) $(CFLAGS) -c queue_link.c

clean:
	rm -f $(OBJS) main_expr

.PHONY: clean