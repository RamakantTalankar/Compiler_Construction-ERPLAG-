// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#ifndef STACK_H
#define STACK_H

#include "stackDef.h"

stack *create(); // creates and returns a stack
void push_element(stack *stack, TOKEN tk, Treenode *tree_address); // pushes an element into the stack
void pop_element(stack *stack); // pops an element from the stack
stack_node top_element(stack *stack); // returns the top element of the stack

#endif
