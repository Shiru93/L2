/*********** RECURSIVE DEPTH-FIRST TRAVERSALS ****************/

/** Traverses recursively a tree according to inorder */
void traverse_inorder_binary_tree(link h, void (*visit)(link)) {
  if (h == NULL) return;
  traverse_inorder_binary_tree(h->left, visit);
  (*visit)(h);
  traverse_inorder_binary_tree(h->right, visit);
}

/** Traverses recursively a tree according to preorder */
void traverse_preorder_binary_tree(link h, void (*visit)(link)) {
  if (h == NULL) return;
  (*visit)(h);
  traverse_preorder_binary_tree(h->left, visit);
  traverse_preorder_binary_tree(h->right, visit);
}

/** Traverses recursively a tree according to postorder */
void traverse_postorder_binary_tree(link h, void (*visit)(link)) {
  if (h == NULL) return;
  traverse_postorder_binary_tree(h->left, visit);
  traverse_postorder_binary_tree(h->right, visit);
  (*visit)(h);
}

/******* ITERATIVE TRAVERSALS (PREORDER, INORDER AND LEVEL-ORDER)  ******/

/*******  DEPTH-FIRST TRAVERSALS  **********/
/** Traverses iteratively a tree according to preorder (using a stack) */
void traverse_preorder_it_BT(link h, void (*visit)(link)) {
  struct stack * st = init_stack(size_binary_tree(h)+1);
  if (h == NULL) return;
  push_stack(st, h);
  while (!is_empty_stack(st)) {
    (*visit)(h = pop_stack(st));
    if (h->right != NULL) push_stack(st, h->right);
    if (h->left != NULL) push_stack(st, h->left);
  }
  delete_stack(&st);
}

/********** alternative implementation ******/
void traverse_preorder_it_BT_var(link h, void (*visit)(link)) {
  struct stack * st = init_stack(size_binary_tree(h)+1);
  push_stack(st, h);
  while (!is_empty_stack(st)) {
    h = pop_stack(st);
    if (h != NULL) {
        (*visit)(h);
        push_stack(st, h->right);
        push_stack(st, h->left);
}
  }
  delete_stack(&st);
}

/** Traverses iteratively a tree according to inorder (using a stack) */
void traverse_inorder_it_BT(link h, void (*visit)(link)) {
    /* Initialization of the pile */
    link k;
    struct stack * st = init_stack(size_binary_tree(h)+1);
    push_stack(st, h);
    while (!is_empty_stack(st)) {
        h = pop_stack(st);
        if (h == NULL) {
            if (!is_empty_stack(st)) {
                k = pop_stack(st);
                (*visit)(k)=
                push_stack(st, k->right);
            }
        }
        else {
            push_stack(st, h);
            push_stack(st, h->left);
        }
    }
}

/*******  BREADTH-FIRST TRAVERSAL *********/
/** Traverses iteratively a tree according to level-order (using a queue) */
void traverse_level_BT(link h, void (*visit)(link)) {
    struct queue * q = init_queue();
    if (h == NULL) return;
    enqueue(q, h);
    while (!is_empty_queue(q)) {
        (*visit)(h = dequeue(q));
        if (h->left != NULL) enqueue(q, h->left);
        if (h->right != NULL) enqueue(q, h->right);
    }
    delete_queue(&q);
}
