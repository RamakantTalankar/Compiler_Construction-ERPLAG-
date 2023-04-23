// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#ifndef TREEADTDEF_H
#define TREEADTDEF_H

#include "tokenDef.h"

// Tree node structure
typedef struct Treenode
{
    TOKEN tree_tk;
    struct Treenode *parent;
    struct Treenode *first_child;
    struct Treenode *left_sibling;
    struct Treenode *right_sibling;
    int no_of_sibling;
    int rule_no;
    struct Treenode *syn;
    struct Treenode *inh;
    struct Treenode *list_syn;
    struct Treenode *list_inh;
} Treenode;

#endif