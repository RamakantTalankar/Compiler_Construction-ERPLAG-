// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#ifndef symbol_table_h
#define symbol_table_h


#include "symbol_table_def.h"
#include "treeAdt.h"
#include <stdio.h>
#include <stdlib.h>

list *create_list();
st *create_st();
st_entry *create_st_entry();
int st_hashfunction(char *k);
void insert_symtable(st *sym_table, st_entry *entry);
st_entry *search_symtable(st *sym_table, Treenode *node);
void insert_list_input(Treenode *tree, st_entry *entry);
void insert_list_output(Treenode *tree, st_entry *entry);
int string_to_int(char *string);
char *to_string(int x);
void fill_list_array_type_struct(Treenode *array_node, list *lt);
void fill_array_type_struct(Treenode *array_node, st_entry *entry);
void fill_declare(st *sym_table, Treenode *node);
void symbol_table_creation(Treenode *ast, st *sym_table);
void print_symbol_table_old(st *sym_table);
void print_symbol_table(st *sym_table);
void print_symbol_table_array(st *sym_table);

#endif