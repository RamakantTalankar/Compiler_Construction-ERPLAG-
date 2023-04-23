// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "hash_table_def.h"

map create_hashtable(); // creates a hashtable
h_node create_node(char *k, char *t); // creates a node of the hashtable
int hashfunction(char *k); // helps in the filling of the hashtable
void insert_hashtable(map ht, char *k, char *t); // inserts a node in the hashtable
char *search_hashtable(map ht, char *k); // to search for a node in a hashtable

#endif
