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
#include "AST.h"
#include "symbol_table.h"

void print_tokens(FILE *ptr, map mp)
{
    fill_buffer_int(ptr);
    TOKEN testtkn;
    while (1)
    {
        char *str = "ENDFILE";

        testtkn = getNextToken(ptr, mp);
        if (strcmp(testtkn.token, str) == 0)
            break;
        if (strcmp(testtkn.token, "LEX_ERR") == 0)
        {
            printf("Line_no: %d , value: %s , Lexical Error", testtkn.line_num, testtkn.value_id);
        }
        if (strcmp(testtkn.token, "NUM") == 0)
            printf("Line_no: %d, lexeme: %d, token: %s \n", testtkn.line_num, testtkn.value_num, testtkn.token);
        else if (strcmp(testtkn.token, "RNUM") == 0)
            printf("Line_no: %d, lexeme: %.20lf, token: %s \n", testtkn.line_num, testtkn.value_rnum, testtkn.token);
        else
            printf("Line_no: %d, lexeme: %s, token: %s \n", testtkn.line_num, testtkn.value_id, testtkn.token);
    }
}

void lex_parse(FILE *fp, FILE *ptr, map mp)
{
    fill_buffer_int(ptr);
    stack *st = create();
    Treenode *temp;
    temp = parsing(fp, st, mp);
}

void print_asttree(FILE *fp, FILE *ptr, map mp)
{
    stack *st1 = create();
    Treenode *temp = parsing(fp, st1, mp);
    Treenode *temp1 = temp;
    
    removerule0(temp1);
    Treenode *ast_tree = AST(0, temp);
    int nodes = traverseTree(ast_tree);
}

Treenode *ast_creation(FILE *fp, FILE *ptr, map mp)
{
    stack *st1 = create();
    Treenode *temp = parsing(fp, st1, mp);
    Treenode *temp1 = temp;

    removerule0(temp1);
    Treenode *ast_tree = AST(0, temp);
    return ast_tree;
}

void allocated_memory(FILE *fp, FILE *ptr, map mp)
{
    fill_buffer_int(ptr);
    stack *st = create();
    Treenode *temp;
    temp = parsing(fp, st, mp);
    char *print_lexeme = "Lexeme";
    char *print_lineno = "Linenum";
    char *print_tokenName = "TokenName";
    char *print_valueIfNumber = "ValueIfNumber";
    char *print_parentNodeSymbol = "ParentNodeSymbol";
    char *print_isLeafNode = "IsLeafNode";
    char *print_nodeSymbol = "NodeSymbol";
    printf("%-30s %-30s %-30s %-30s %-30s %-30s %-30s\n", print_lexeme, print_lineno, print_tokenName, print_valueIfNumber, print_parentNodeSymbol, print_isLeafNode, print_nodeSymbol);
    int number_of_nodes_in_parse_tree = traverseTree(temp);

    Treenode *temp1 = temp;
    removerule0(temp1);
    Treenode *ast_tree = AST(0, temp);
    int number_of_nodes_in_ast = traverseASTTree(ast_tree);


    printf("\n\nAST tree Number of nodes = %d, Allocated Memory = %ld Bytes\n", number_of_nodes_in_ast, number_of_nodes_in_ast * sizeof(Treenode));
    printf("Parse Number of nodes = %d, Allocated Memory = %ld Bytes\n", number_of_nodes_in_parse_tree, number_of_nodes_in_parse_tree * sizeof(Treenode));
    double ratio = (1 - ((double)number_of_nodes_in_ast / number_of_nodes_in_parse_tree)) * 100;
    printf("Compression Percentage = %lf\n", ratio);
}

void print_menu()
{
    printf("Choose an option:\n");
    printf("0. Exit\n");
    printf("1. Print Tokens\n");
    printf("2. Run Parser\n");
    printf("3. Print Abstract Syntax Tree\n");
    printf("4. Amount of Allocated Memory\n");
    printf("5. Print Symbol Table\n");
    printf("6. Activation Record Size\n");
    printf("7. Print Static and Dynamic Array\n");
    printf("8. Error Reporting and Total Compile Time\n");
    printf("9. Code Generation\n\n\n");
}

int main(int argc, char *argv[])
{

    FILE *fp = fopen("grammar.txt", "r");
    grammarInitialize(fp);
    first();
    follow_set();
    fill_parse_table();
    map mp;
    mp = create_hashtable();
    ht_init(mp);
    int response = -1;

    buffer_size = atoi(argv[3]);
    printf("Both lexical and syntax analysis modules implemented\n\n\n");
    print_menu();
    scanf("%d", &response);
    printf("\n");

    while (response != 0)
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
        FILE *ptr = fopen(argv[1], "r");
        switch (response)
        {
        case 0:
            return 0;
        case 1:
            print_tokens(ptr, mp);
            // fclose(ptr);
            // return 0;
            return 0;
        case 2:
            lex_parse(fp, ptr, mp);
            // fclose(ptr);
            // return 0;
            return 0;
        case 3:
            print_asttree(fp, ptr, mp);
            // fclose(ptr);
            // return 0;
            return 0;
        case 4:
            allocated_memory(fp, ptr, mp);
            fclose(ptr);
            // return 0;
            return 0;
        case 5:;
            st *sym_table = create_st();
            sym_table->nesting_level = 0;
            sym_table->start_scope = 1;
            sym_table->module_name = "main";
            sym_table->st_parent = NULL;
            symbol_table_creation(ast_creation(fp,ptr,mp), sym_table);
            // print_symbol_table_old(sym_table);
            char *p_id = "variable_name";
            char *p_scope = "scope(module_name)";
            char *p_start_end = "scope(line_no)";
            char *p_type = "type_of_element";
            char *p_isarray = "is_array";
            char *p_st_dyn = "Static/Dynamic";
            char *p_arr_range = "array_range";
            char *p_width = "width";
            char *p_offset = "offset";
            char *p_nest_lvl = "nesting_level";
            printf("%-30s %-30s %-30s %-30s %-30s %-30s %-45s %-30s %-30s %-30s\n", p_id, p_scope, p_start_end, p_type, p_isarray, p_st_dyn, p_arr_range, p_width, p_offset, p_nest_lvl);
            print_symbol_table(sym_table);

            return 0;
        case 6:
            printf("Not Implemented\n");
            return 0;
        case 7:;
            st *sym_table1 = create_st();
            sym_table1->nesting_level = 0;
            sym_table1->start_scope = 1;
            sym_table1->module_name = "main";
            sym_table1->st_parent = NULL;
            
            symbol_table_creation(ast_creation(fp, ptr, mp), sym_table1);
            printf("Printing Static and Dynamic arrays: \n");
            print_symbol_table_array(sym_table1);

            return 0;
        case 8:;
            clock_t start_time, end_time;

            double total_CPU_time, total_CPU_time_in_seconds;

            start_time = clock();

            // invoke your lexer and parser here
            st *sym_table2 = create_st();
            sym_table2->nesting_level = 0;
            sym_table2->start_scope = 1;
            sym_table2->module_name = "main";
            sym_table2->st_parent = NULL;
            symbol_table_creation(ast_creation(fp, ptr, mp), sym_table2);
            end_time = clock();
            total_CPU_time = (double)(end_time - start_time);
            total_CPU_time_in_seconds = total_CPU_time / (CLOCKS_PER_SEC * 10);
            printf("\n\nTotal time taken by Stage-1 code: %lf ticks\n", total_CPU_time);
            printf("Total time in seconds: %lf seconds\n", total_CPU_time_in_seconds);
            printf("Not Implemented Error Reporting\n");
            return 0;
        case 9:
            printf("Not Implemented\n");
            return 0;
        default:
            printf("Invalid option\n");
            return 0;
        }
        printf("\n\n");
        fclose(ptr);
        print_menu();
        scanf("%d", &response);
    }

    return 0;
}