// Group - 4
// Aryan Desai - 2020A7PS0123P 
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include "parser.h"
#include "hash_table.h"
#include "lexer.h"
#include "treeAdt.h"
#include "stack.h"

void give_uncomm(FILE* fp1)
{
    remove_comments_from_file(fp1); 
} 

void print_tokens(FILE* ptr, map mp)
{ 
    fill_buffer_int(ptr);
    TOKEN testtkn;
    while(1)
    {
        char * str = "ENDFILE";

        testtkn = getNextToken(ptr, mp);
        if(strcmp(testtkn.token, str) == 0)
            break;
        if (strcmp(testtkn.token, "LEX_ERR") == 0)
        {
            printf("Line_no: %d , value: %s , Lexical Error", testtkn.line_num, testtkn.value_id);
        }
        if(strcmp(testtkn.token, "NUM") == 0)
            printf("Line_no: %d, lexeme: %d, token: %s \n", testtkn.line_num, testtkn.value_num, testtkn.token);
        else if(strcmp(testtkn.token, "RNUM") == 0)
            printf("Line_no: %d, lexeme: %.20lf, token: %s \n", testtkn.line_num, testtkn.value_rnum, testtkn.token);
        else
            printf("Line_no: %d, lexeme: %s, token: %s \n", testtkn.line_num, testtkn.value_id, testtkn.token);
    }
} 

void print_parsetree(FILE *fp, FILE *ptr, map mp, char *filename)
{
    fill_buffer_int(ptr);
    stack *st = create();
    Treenode* temp;
    temp = parsing(fp, st, mp);
    FILE *out_p = fopen(filename, "w");
    char *print_lexeme = "Lexeme";
    char *print_lineno = "Linenum";
    char *print_tokenName = "TokenName";
    char *print_valueIfNumber = "ValueIfNumber";
    char *print_parentNodeSymbol = "ParentNodeSymbol";
    char *print_isLeafNode = "IsLeafNode";
    char *print_nodeSymbol = "NodeSymbol";
    fprintf(out_p, "%-30s %-30s %-30s %-30s %-30s %-30s %-30s\n", print_lexeme, print_lineno, print_tokenName, print_valueIfNumber, print_parentNodeSymbol, print_isLeafNode, print_nodeSymbol);
    traverseTree(temp, out_p);
} 

void lex_parse(FILE* fp, FILE* ptr, map mp)
{
    fill_buffer_int(ptr);
    stack *st = create();
    Treenode* temp;
    temp = parsing(fp, st, mp);
}

void total_time(FILE* fp, FILE* ptr, map mp)
{
    clock_t start_time, end_time;

    double total_CPU_time, total_CPU_time_in_seconds;

    start_time = clock();

    // invoke your lexer and parser here 
    lex_parse(fp,ptr,mp);

    end_time = clock();
    total_CPU_time = (double)(end_time - start_time);
    total_CPU_time_in_seconds = total_CPU_time / (CLOCKS_PER_SEC*10); // In our PC 1 second has 10 clock cycles

    printf("\n\nTotal time taken by Stage-1 code: %lf ticks\n", total_CPU_time); 
    printf("Total time in seconds: %lf seconds\n", total_CPU_time_in_seconds);
} 

void print_menu()
{
    printf("Choose an option:\n");
    printf("0. Exit\n"); 
    printf("1. Comment free code\n");
    printf("2. Print token list\n");
    printf("3. Print parse tree\n");
    printf("4. Total time taken by Stage-1 code\n\n");
}

int main(int argc, char *argv[])
{
    
    FILE *fp = fopen("grammar.txt", "r");
    grammarInitialize(fp);
    first();
    follow_set();
    fill_parse_table(); 
    map mp;
    mp=create_hashtable();
    ht_init(mp);
    int response = -1;

    buffer_size=atoi(argv[3]);
    printf("Both lexical and syntax analysis modules implemented\n\n\n");
    print_menu(); 
    scanf("%d", &response);
    printf("\n");

    while(response != 0)
    {
        state = 0;
        fwdptr = 0;
        bwdptr = 0;
        line_no = 1;
        buffer_no = 1;
        retract = 0;

        memset(buffer1, '\0', sizeof(buffer1));
        memset(buffer2, '\0', sizeof(buffer2));
        memset(lexeme, '\0', sizeof(lexeme));
        FILE* ptr=fopen(argv[1],"r");
        switch(response)
        {
            case 1:
                give_uncomm(ptr); 
                break; 
            case 2:
                print_tokens(ptr,mp); 
                break; 
            case 3:
                print_parsetree(fp,ptr,mp,argv[2]); 
                break; 
            case 4:
                total_time(fp,ptr,mp); 
                break; 
            default:
                printf("Invalid option\n"); 
                break; 
        } 
        printf("\n\n");
        fclose(ptr);
        print_menu(); 
        scanf("%d", &response); 
    } 

    return 0;
}