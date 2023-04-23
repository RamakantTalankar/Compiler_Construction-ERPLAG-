// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#ifndef AST_H
#define AST_H

#include "treeAdt.h"
#include <stdio.h>
#include <stdlib.h>

Treenode *iterate_child(Treenode *parent, char *name);
Treenode *make_node(char *name, Treenode *child1, Treenode *child2);
Treenode *make_node_wo_name(Treenode *node, Treenode *child1, Treenode *child2);
Treenode *make_node4(char *name, Treenode *child1, Treenode *child2, Treenode *child3, Treenode *child4);
void free_ptr(Treenode *parent, char *name);
Treenode *make_list(Treenode *temp);
Treenode *insert_end_node(Treenode *ptr, Treenode *end);
Treenode *insert_head(Treenode *ptr, Treenode *node);
Treenode *AST(int syn_inh, Treenode *t_node);
int traverseASTTree(Treenode *temp);
void removerule0(Treenode *temp);

#endif