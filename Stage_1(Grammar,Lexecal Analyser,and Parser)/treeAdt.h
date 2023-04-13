// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#ifndef TREEADT_H
#define TREEADT_H

#include "tokenDef.h"
#include "treeAdtDEF.h"
#include <stdio.h>

Treenode *create_treenode(TOKEN tk); // create a node of the tree with the given token
Treenode *add_firstChild(Treenode *parent, TOKEN tk);// add the first child in the tree
Treenode *add_sibling(Treenode *parent, TOKEN tk);// add the sibling of a node in tree
void traverseTree(Treenode *temp, FILE *out_p);// traverse the parse tree
char *isLeafNode(Treenode *temp); // check if the node is a leaf node 

#endif