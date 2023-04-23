// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#ifndef STACKDEF_H
#define STACKDEF_H

#include "tokenDef.h"
#include "treeAdt.h"

// struct for nodes of the tree
typedef struct stack_node
{
    TOKEN tk_stk;
    Treenode *treenode;
} stack_node;

// struct for the stack
typedef struct stack
{
    int size;
    int top_element_index;
    stack_node *array;
} stack;

#define STACK_SIZE 10000

#endif
