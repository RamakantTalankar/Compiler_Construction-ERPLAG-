// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#ifndef PARSERDEF_H
#define PARSERDEF_H

#define no_of_rules 142
#define no_of_terminals 57
#define no_of_nterminals 73


typedef struct grammarNode
{
    int isTerminal;
    struct grammarNode *next;
    struct grammarNode *prev;
    char *name;
} node;   

extern node *grammar[no_of_rules];
extern int check_first[no_of_rules];
extern int check_follow[no_of_nterminals];
extern char *terminal[no_of_terminals];
extern char *non_terminal[no_of_nterminals];
extern int first_linewise[no_of_rules][no_of_terminals];
extern int first_ntwise[no_of_nterminals][no_of_terminals];
extern int follow[no_of_nterminals][no_of_terminals + 1];   
extern int parse_table[no_of_nterminals][no_of_terminals + 1];

#endif
