/** À COMPLÉTER AVEC LE NOM, LE PRÉNOM ET LE N° D'ÉTUDIANT(E) **/
/** DE CHAQUE ÉTUDIANT(E) AYANT TRAVAILLÉ SUR LE FICHIER **/
/* Etudiant(e) n°1, NOM :                Prénom :               N° :             */
/* Etudiant(e) n°2, NOM :                Prénom :               N° :             */

#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include "stack_link.h"

/** Searches a BST for a label and returns a pointer to a node with this label */
/* Returns NULL if there is no node with this label */
link search_BST(link h, item v) {
  if (h == NULL) return NULL;
  item t = get_binary_tree_root(h);
  if eq(v, t) return h;
  if less(v, t) return search_BST(h->left, v);
    else return search_BST(h->right, v);
  }

/** Inserts RECURSIVELY a node with a given label in a BST (as a leaf) */
/* and returns a link to the updated BST */
link insert_BST(link h, item v) {
  if (h == NULL) return cons_binary_tree(v, NULL, NULL);
  if less(v, get_binary_tree_root(h)) {
    h->left = insert_BST(h->left, v);
  }
  else {
    h->right = insert_BST(h->right, v);
  }
  return h;
}

/** Inserts ITERATIVELY a node with a given label in a BST (as a leaf)*/
/* and returns the updated BST */
/** N.B. The function DOES NOT require the use a stack */
link insert_BST_it(link h, item v) {
    /** TO BE COMPLETED **/
}

/** Selects the kth label of a BST */
/* and returns a pointer to the corresponding node */
/* Returns NULL if the BST does not contain k labels */
link select_BST(link h, int k) {
    int t;
    if (h == NULL) return NULL;
    t = size_binary_tree(h->left);
    if (t > k) return select_BST(h->left, k);
    if (t < k) return select_BST(h->right, k-t-1);
    return h;
}

/*************     ROTATIONS        *************/

/** Applies a right rotation to the root of a BST */
link rotate_right(link h) {
  link x;
  if (NULL == h) return NULL;
  x = h->left;
  h->left = x->right;
  x->right = h;
  return x;
}

/** Applies a left rotation to the root of a BST */
link rotate_left(link h) {
  link x;
  if (NULL == h) return NULL;
  x = h->right;
  h->right = x->left;
  x->left = h;
  return x;
}

/** Inserts RECURSIVELY a node with a given label at the root of BST */
/* and returns the updated BST */
link insert_BST_root(link h, item v) {
  if (h == NULL) return cons_binary_tree(v, NULL, NULL);
  if (less(v, get_binary_tree_root(h))) {
    h->left = insert_BST_root(h->left, v);
    h = rotate_right(h);
  }
  else {
    h->right = insert_BST_root(h->right, v);
    h = rotate_left(h);
  }
  return h;
}

/** Inserts ITERATIVELY a node with a given label at the root of BST */
/* and returns the updated BST */
/** The function DOES make use of a stack */
link insert_BST_root_it(link h, int v) {
    /** TO BE COMPLETED **/
}

/** Partitions a BST with respect to the node of rank k */
/* and returns the updated BST */
link partition_BST(link h, int k) {
  int t = size_binary_tree(h->left);
  if (is_empty_binary_tree(h)) return h;
  if (t > k) {
    h->left = partition_BST(h->left, k);
    h = rotate_right(h);
  }
  if (t < k) {
    h->right = partition_BST(h->right, k-t-1);
    h = rotate_left(h);
  }
  return h;
}

/** Deletes a node of label v in a BST */
/* and returns the updated BST */
link delete_node_BST(link h, item v) {
    /** TO BE COMPLETED **/
}

/** Returns the address of the predecessor of the root, */
/* i.e. a link to the node with the least priority in the left subtree */
/* (returns NULL if no such predecessor) */
link predecessor_BST(link h) {
    /** TO BE COMPLETED **/
}

/** Deletes the first node of label v in a BST */
/* and returns the updated BST */
/** N.B. This function DOES NOT call partition_BST */
/** N.B. This function calls predecessor_BST **/
link remove_node_BST(link h, item v) {
    /** TO BE COMPLETED **/
}

/** Puts a BST into perfect balance, by recursively */
/* putting the median node at the root */
link balance_BST(link h) {
    /** TO BE COMPLETED **/
}

/** Returns the adresse of the binary_tree resulting from merging */
/* the binary trees pointed by h and k */
/** N.B. The total amount of memory allocated on the heap is not modified by the function */
link join_BST(link h, link k) {
    /** TO BE COMPLETED **/
}
