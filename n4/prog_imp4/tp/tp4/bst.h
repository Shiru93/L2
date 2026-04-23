#ifndef BST_H
#define BST_H

#include "stack_link.h"
#include "item.h"
#include "binary_tree.h"
#include "queue_link.h"

// bst_cm5_2026.c
link search_BST(link h, item v);
link insert_BST(link h, item v);
link insert_BST_it(link h, item v);
link select_BST(link h, int k);
link rotate_right(link h);
link rotate_left(link h);
link insert_BST_root(link h, item v);

// bst.c
link insert_BST_root_it(link h, item v);
link partition_BST(link h, int k);
link join_BST(link L, link R);
link delete_node_BST(link h, item v);
link balance_BST(link h);

// Utilitaire
int same_tree(link a, link b);

#endif