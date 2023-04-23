// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include"lexerDef.h"
#include"hash_table.h"

void ht_init(map mp); //Initialize hashtable and add keywords
char *substring(int buffer_num, int ptr1, int size); //custom function for obtaining substring of specific size
char *concat(char *ch1, int size1, char *ch2, int size2); //function for concatenating string
void buffer_input(FILE *fptr); //Function for loading input in the buffer
void discard(); //Function for discarding extra input char read in the DFA
void fill_buffer_int(FILE *fp); //wrapper function to fill the buffer
char get_char(FILE *fp); //Function to obatin a character from the buffer
char *tokenizer(); //Returns the lexeme value for a token in the form of a string
void remove_comments_from_file(FILE *fptr1); //Function for removing the comments from the file
int letter(char ch); //Check if the char passed as argument is a letter
int digit(char ch); //Check if the char passed as argument is a digit
TOKEN getNextToken(FILE *fp, map mp); //Function for obtaining the next Token

#endif
