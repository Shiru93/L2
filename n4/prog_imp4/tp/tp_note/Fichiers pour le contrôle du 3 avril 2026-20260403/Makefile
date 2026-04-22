all: main_bst.o bst.o binary_tree.o stack_link.o queue_link.o
	gcc main_bst.o bst.o binary_tree.o stack_link.o queue_link.o -o prog_BST

queue_link.o: queue_link.c queue_link.h BT.h item.h
	gcc -c -Wall -pedantic -Wfatal-errors queue_link.c

stack_link.o: stack_link.c stack_link.h BT.h item.h
	gcc -c -Wall -pedantic -Wfatal-errors stack_link.c

binary_tree.o: binary_tree.c binary_tree.h BT.h item.h
	gcc -c -Wall -pedantic -Wfatal-errors binary_tree.c

bst.o: bst.c bst.h binary_tree.h
	gcc -c -Wall -pedantic -Wfatal-errors bst.c

main_bst.o: main_bst.c bst.h 
	gcc -c -Wall -pedantic -Wfatal-errors main_bst.c

clean:
	rm *.o prog_BST
