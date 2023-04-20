// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#ifndef PARSER_H
#define PARSER_H

#include "parserDef.h" 
#include "treeAdt.h"
#include "stack.h"
#include "hash_table.h"
#include<stdio.h>
#include <stdlib.h>

int checkTerminal(char *name);    // check if a term is a terminal or not
void grammarInitialize(FILE *fp); // initializes the grammar in a global variable
void print_gr(); // prints the entire grammar line by line

int get_col(char *name);      // return the column number of a terminal from terminal array
int get_row(char *name);      // return the row number of a non-terminal from the line wise grammar
int get_index_nt(char *name); // return index of the nonterminal from the nonterminal array

int check_rhs(node *rhs); // returns if the rhs node needs to be checked furthur for the first calculation
void make_first(int i);   // calculates the first set of a line
void first();             // calls make_first line by line if the first for that line is not calculated
void first_nt_in();       // populates the first ntwise array
void print_first(); // prints all the first sets line by line

void fill_follow(int i, int a);    // copy the follow of one NT to another NT
void follow_F_first(int i, int a); // copy the first from one NT to another
int first_contains_epsilon(int a); // checks if the first set of row a comtains epsilon
void make_follow(int i);           // calculates the follow of a NT specified
void follow_set();                 // calls make_follow NT by NT
void print_follow(); //print the follow table

void parse_table_init(); // initialize parse table
void fill_parse_table(); // populates the parse table
void print_parsetable(); //print the parse table 

void push_stack_grammar_rule(stack *st, int rule_no, Treenode *parent); // makes a treenode and pushes the node in the stack
char* do_uppercase(char *str1); // converts a string to uppercase and returns a new string
char* do_lowercase(char *str1); // converts a string to lowercase and returns a new string
Treenode* parsing(FILE *fp, stack *st, map mp); // parses the input file and returns the parse tree root node
int syn_func(char* c1, char* c2); // used for error recovery


#endif
