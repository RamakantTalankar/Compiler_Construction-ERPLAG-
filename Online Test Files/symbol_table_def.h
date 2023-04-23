// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#ifndef SYMBOL_TABLE_DEF_H
#define SYMBOL_TABLE_DEF_H

typedef struct st_entry st_entry;
typedef struct st st;
typedef struct Type Type;
typedef struct list list;

struct Type
{

    char *type_name;          // can be integer ,real, boolean, array, function.
    int array_static_dynamic; // 0-static 1-dynamic derieve from lower_index and higher_index by comparing with ascii 0-9 with first char
    char *lower_sign;
    char *higher_sign;
    char *lower_index;
    char *higher_index;
    char *arr_type;
    list *input_list;
    list *output_list;
};

struct list
{

    char *name;
    Type type;
    list *next;
};


struct st_entry
{
    char *name;
    Type type;
    st *st_ptr;
    st_entry *next_entry;
    st *own_st; // points to the symbol table whare the entry resides in order to pass it to the parent;
};

struct st
{
    st_entry *hash_array[53];
    st *st_parent;
    int start_scope;
    int end_scope;
    char *module_name;
    int nesting_level;
    int activation_size;
};


#endif