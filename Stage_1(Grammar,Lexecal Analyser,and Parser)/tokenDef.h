// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#ifndef TOKENDEF_H
#define TOKENDEF_H

// struct for tokens used for parsing and lexical analysis
typedef struct token
{
    char *token;
    union
    {
        char value_id[100];
        int value_num;
        double value_rnum;
    };
    int line_num;
} TOKEN;

#endif
