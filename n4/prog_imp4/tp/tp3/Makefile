CC     = gcc
CFLAGS = -Wall -Wextra -std=c99

LIB = ../tp1/Documents pour le TP n°1 (semaine du 20 janvier 2026)-20260408

OBJS_EXPR = main_expr.o binary_tree.o stack_link.o queue_link.o
OBJS_HEAP = main_heap.o

all: main_expr main_heap

main_expr: $(OBJS_EXPR)
	$(CC) $(CFLAGS) -o main_expr $(OBJS_EXPR)

main_heap: $(OBJS_HEAP)
	$(CC) $(CFLAGS) -o main_heap $(OBJS_HEAP)

main_expr.o: main_expr.c
	$(CC) $(CFLAGS) -I"$(LIB)" -c main_expr.c

main_heap.o: main_heap.c
	$(CC) $(CFLAGS) -c main_heap.c

binary_tree.o: "$(LIB)/binary_tree.c"
	$(CC) $(CFLAGS) -I"$(LIB)" -c "$(LIB)/binary_tree.c"

stack_link.o: "$(LIB)/stack_link.c"
	$(CC) $(CFLAGS) -I"$(LIB)" -c "$(LIB)/stack_link.c"

queue_link.o: "$(LIB)/queue_link.c"
	$(CC) $(CFLAGS) -I"$(LIB)" -c "$(LIB)/queue_link.c"

clean:
	rm -f $(OBJS_EXPR) $(OBJS_HEAP) main_expr main_heap

.PHONY: all clean