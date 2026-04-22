#ifndef FONCTIONS_H
#define FONCTIONS_H

#include <stdio.h>
#include <stdlib.h>

#include "BT.h"
#include "binary_tree.h"

// Retourne 1 si c est un opérateur arithmétique, 0 sinon
int is_operator(char c);

link parse_expr(const char *expr, int *pos);
int eval_tree(const link bt);
void tree_to_expr(const link bt, char *buf, int *pos);

#endif