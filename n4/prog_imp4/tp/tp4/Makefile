CC     = gcc
CFLAGS = -Wall -Wextra -std=c99

OBJS = main_bst.o bst.o bst_cm5_2026.o binary_tree.o stack_link.o queue_link.o

main_bst: $(OBJS)
	$(CC) $(CFLAGS) -o main_bst $(OBJS)

main_bst.o: main_bst.c bst.h binary_tree.h item.h BT.h
	$(CC) $(CFLAGS) -c main_bst.c

bst.o: bst.c bst.h binary_tree.h item.h BT.h
	$(CC) $(CFLAGS) -c bst.c

bst_cm5_2026.o: bst_cm5_2026.c bst.h binary_tree.h item.h BT.h stack_link.h
	$(CC) $(CFLAGS) -c bst_cm5_2026.c

binary_tree.o: binary_tree.c binary_tree.h BT.h item.h stack_link.h queue_link.h
	$(CC) $(CFLAGS) -c binary_tree.c

stack_link.o: stack_link.c stack_link.h BT.h
	$(CC) $(CFLAGS) -c stack_link.c

queue_link.o: queue_link.c queue_link.h BT.h
	$(CC) $(CFLAGS) -c queue_link.c

clean:
	rm -f $(OBJS) main_bst

.PHONY: clean