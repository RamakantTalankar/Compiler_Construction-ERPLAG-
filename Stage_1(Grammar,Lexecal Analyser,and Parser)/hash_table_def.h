// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#ifndef HASH_TABLE_DEF_H
#define HASH_TABLE_DEF_H

//structure to store the key and token and next pointer
typedef struct HTNode *h_node;
struct HTNode
{
    char *key;
    char *token;
    h_node next;
};

//structure to store the array of hashtable node
typedef struct hashtable *map;
struct hashtable
{
    h_node hash_array;
};

#endif
