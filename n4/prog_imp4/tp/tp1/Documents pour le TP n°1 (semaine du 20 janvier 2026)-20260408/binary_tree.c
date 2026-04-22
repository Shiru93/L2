#include <stdio.h>
#include <stdlib.h>

#include "item.h"
#include "BT.h"
#include "stack_link.h"
#include "queue_link.h"

/********************************************************************/
/*  In the sequel, "tree" always stands for "(rooted) binary tree"  */
/********************************************************************/

/** "Creates" an empty tree and returns its address */
link empty_tree(){
    link tree = NULL;
    return tree;
}

/*
link empty_tree(){
    return NULL;
}
*/

/* Constructs a binary tree from a label and two binary trees */
/* (allocates memory and returns the allocated block's address) */
link cons_binary_tree(item h, const link tree1, const link tree2){
    link tree = malloc(sizeof(struct binary_tree));

    if(!tree) return NULL;

    tree->label = h;
    tree->left = tree1;
    tree->right = tree2;

    return tree;
}

/* Frees all memory allocated to a tree and its subtrees */
void delete_binary_tree(link * bt){
    if(!bt || *bt == NULL){
        return;
    }

    delete_binary_tree(&((*bt)->left));
    delete_binary_tree(&((*bt)->right));

    free(*bt);

    *bt = NULL;
}

/** Returns the left subtree of a tree */
/* (requires that the tree be non-empty) */
link left(const link bt) {
    return bt->left;
}

/** Returns the right subtree of a tree */
/* (requires that the tree be non-empty) */
link right(const link bt){
    return bt->right;
}

/** Returns the label of the root of a tree */
/* (requires that the tree be non-empty) */
item get_binary_tree_root(const link bt){
    return bt->label;
}

/** Tests a tree for emptyness */
int is_empty_binary_tree(const link bt){
    return !bt;
}

/*
int is_empty_binary_tree(const link bt) {
    return (bt == NULL) ? 1 : 0;
}
*/

/** Computes recursively and returns the size of a tree */
int size_binary_tree(const link bt){
    if(is_empty_binary_tree(bt)) 
        return 0;

    return 1 + size_binary_tree(bt->left) + size_binary_tree(bt->right);
}

/** Computes recursively and returns the height of a tree */
/* N.B. height(empty tree) = -1, height(one-node tree) = 0 */
int height_binary_tree(const link bt){
    if(is_empty_binary_tree(bt)) 
        return -1;
    
    int h_left = height_binary_tree(bt->left);
    int h_right = height_binary_tree(bt->right);

    return 1 + (h_left > h_right ? h_left : h_right);
}

/** Displays information attached to the root */
void print_label(const link bt){
    if(!is_empty_binary_tree(bt)) 
        display(bt->label);
}

/** Prints a tree (rotated by -\pi/2) */
void show_binary_tree(const link bt, int lvl){
    if(is_empty_binary_tree(bt))
        return;

    show_binary_tree(bt->right, lvl +1);
    for(int i = 0; i < lvl; i++)
        printf("    ");
    printf("%c\n", bt->label);

    show_binary_tree(bt->left, lvl +1);
}

/** Traverses recursively a tree according to inorder */
void traverse_inorder_binary_tree(link h, void (*visit)(link)){
    if(is_empty_binary_tree(h)) 
        return;

    traverse_inorder_binary_tree(h->left, visit);
    (*visit) (h);
    traverse_inorder_binary_tree(h->right, visit);
}

/** Traverses recursively a tree according to preorder */
void traverse_preorder_binary_tree(link bt, void (*visit)(link)){
    if(is_empty_binary_tree(bt))
        return;

    (*visit) (bt);
    traverse_preorder_binary_tree(bt->left, visit);
    traverse_preorder_binary_tree(bt->right, visit);
}

/** Traverses recursively a tree according to postorder */
void traverse_postorder_binary_tree(link bt, void (*visit)(link)){
    if(is_empty_binary_tree(bt))
        return;
    
    traverse_postorder_binary_tree(bt->left, visit);
    traverse_postorder_binary_tree(bt->right, visit);
    (*visit) (bt);
}

/** Traverses iteratively a tree according to preorder (using a stack) */
void traverse_preorder_it_BT(link bt, void (*visit)(link)){
    if(is_empty_binary_tree(bt)) return;

    struct stack *s = init_stack(size_binary_tree(bt));
    push_stack(s, bt);

    while(!is_empty_stack(s)){
        link node = pop_stack(s);
        (*visit)(node);

        if(!is_empty_binary_tree(node->right))
            push_stack(s, node->right);

        if(!is_empty_binary_tree(node->left))
            push_stack(s, node->left);
    }

    delete_stack(&s);
}

/** Traverses iteratively a tree according to inorder (using a stack) */
void traverse_inorder_it_BT(link bt, void (*visit)(link)){
    struct stack *s = init_stack(size_binary_tree(bt));
    link current = bt;

    while(!is_empty_binary_tree(current) || !is_empty_stack(s)){
        while(!is_empty_binary_tree(current)){
            push_stack(s, current);
            current = current->left;
        }

        current = pop_stack(s);
        (*visit)(current);
        current = current->right;
    }

    delete_stack(&s);
}

/** Traverses iteratively a tree according to level-order (using a queue) */
void traverse_level_BT(link bt, void (*visit)(link)){
    if(is_empty_binary_tree(bt)) return;

    struct queue *q =  init_queue();

    enqueu(q, bt);

    while(!is_empty_queue(q)){
        link node = dequeue(q);
        (*visit)(node);

        if(!is_empty_binary_tree(node->left))
            enqueue(q, node->left);

        if(!is_empty_binary_tree(node->right))
            enqueue(q, node->right);
    }

    delete_queue(&q);
}