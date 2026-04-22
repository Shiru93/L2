#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include "stack_link.h"

/************************************************/
/*******  Maximal priority = least value ********/
/************************************************/

/** Searches a BST for a label and returns a pointer to a node with this label */
/* Returns NULL if there is no node with the required label */
/** Time complexity \Omega(n) in the worst case, where n is the size of the tree **/
link search_BST(link h, item v) {
  if (h == NULL) return NULL;
  item t = get_binary_tree_root(h);
  if eq(v, t) return h;
  if less(v, t) return search_BST(h->left, v);
    else return search_BST(h->right, v);
  }

/** Inserts RECURSIVELY a node with a given label in a BST (as a new leaf) */
/* and returns a link to the updated BST */
/** Time complexity \Omega(n) in the worst case, where n is the size of the tree **/
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

/**********  LEAF-INSERTION ****************/
/** Inserts ITERATIVELY a node with a given label in a BST (as a new leaf)*/
/* and returns the updated BST */
/** N.B. The function does not use a stack */
/** Time complexity \Omega(n) in the worst case, where n is the size of the tree **/
link insert_BST_it(link h, item v) {
  link p , x = h;
  if (h == NULL) return cons_binary_tree(v, NULL, NULL);
  while (x != NULL) {
    p = x;
    x = less(v, get_binary_tree_root(x)) ? x->left : x->right;
  }
  x = cons_binary_tree(v, NULL, NULL);
  if less(v, p->label) {
    p->left = x;
  }
  else {
    p->right = x;
  }
  return h;
}

/** Selects the kth label of a BST */
/* and returns a pointer to the corresponding node */
/* Returns NULL if the BST does not contain k labels */
/** Time complexity \Omega(n^2) in the worst case, where n is the size of the tree **/
link select_BST(link h, int k) {
    int t;
    if (h == NULL) return NULL;
    t = size_binary_tree(h->left);
    if (t > k) return select_BST(h->left, k);
    if (t < k) return select_BST(h->right, k-t-1);
    return h;
}

/*************     ROTATIONS        *************/

/** Applies a right rotation the root of a BST */
/** Time complexity \Theta(1) in the worst case **/
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

/************   ROOT-INSERTION ****************/
/** Inserts RECURSIVELY a node with a given label at the root of BST */
/* and returns the updated BST */
/** Time complexity \Omega(n) in the worst case, where n is the size of the tree **/
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
