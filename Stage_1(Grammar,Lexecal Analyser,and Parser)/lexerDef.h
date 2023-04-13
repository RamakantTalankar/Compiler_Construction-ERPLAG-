// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#ifndef LEXERDEF_H
#define LEXERDEF_H

#include "tokenDef.h" 

extern int state;
extern int fwdptr;
extern int bwdptr;
extern int line_no;
extern char buffer1[1024];
extern char buffer2[1024];
extern int buffer_no;
extern char lexeme[100];
extern int retract;
extern char *ptr_strtod; // Declared for string to double function. 
extern int buffer_size;

#endif
