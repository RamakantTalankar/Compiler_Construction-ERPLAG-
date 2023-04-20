// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#include "parser.h" 
#include "lexer.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h> 

node *grammar[no_of_rules];
int check_first[no_of_rules] = {0};
int check_follow[no_of_nterminals] = {0};
char *terminal[no_of_terminals] = {"declare", "module", "id", "semicol", "driverdef", "driver", "program", "driverenddef", "def", "enddef", "takes", "input", "sqbo", "sqbc", "returns", "colon", "comma", "integer", "real", "boolean", "array", "of", "rangeop", "start", "end", "get_value", "bo", "bc", "print", "true", "false", "num", "rnum", "assignop", "plus", "minus", "use", "with", "parameters", "mul", "div", "and", "or", "lt", "le", "ge", "gt", "eq", "ne", "switch", "case", "break", "default", "for", "in", "while", "epsilon"};
char *non_terminal[no_of_nterminals] = {"PROGRAM", "MODULEDECLARATIONS", "OTHERMODULES", "DRIVERMODULE", "MODULEDECLARATION", "MODULE", "MODULEDEF", "INPUT_PLIST", "RET", "OUTPUT_PLIST", "DATATYPE", "INPUT_PLIST_ONE", "TYPE", "OUTPUT_PLIST_ONE", "RANGE_ARRAYS", "INDEX_ARR", "STATEMENTS", "STATEMENT", "IOSTMT", "SIMPLESTMT", "DECLARESTMT", "CONDITIONALSTMT", "ITERATIVESTMT", "VAR_PRINT", "VAR_PRINT_ONE", "NEW_INDEX", "ASSIGNMENTSTMT", "MODULEREUSESTMT", "WHICHSTMT", "ONEVALUEIDSTMT", "ONEVALUEARRSTMT", "EXPRESSION", "SIGN", "OPTIONAL", "ACTUAL_PARA_LIST", "ACTUAL_PARA_LIST_TWO", "K_OLD", "IDLIST", "IDLIST_ONE", "ARITHMETICORBOOLEANEXPR", "UNARY", "UNARY_OP", "NEW_NT", "ARITHMETICEXPR", "VAR_ID_NUM", "ANYTERM", "ARITHMETICORBOOLEANEXPR_ONE", "LOGICALOP", "ANYTERM_ONE", "RELATIONALOP", "TERM", "ARITHMETICEXPR_ONE", "OP_ONE", "TERM_ONE", "OP_TWO", "ELEMENT_INDEX_WITH_EXPRESSIONS", "N_TEN","N_ELEVEN", "FACTOR", "BOOLCONSTT", "ARREXPR", "ARRTERM", "ARR_N_FOUR", "ARRFACTOR", "ARR_N_FIVE", "CASESTMT", "VALUE", "CASESTMT_ONE", "DEFAULT", "RANGE_FOR_LOOP", "INDEX_FOR_LOOP", "SIGN_FOR_LOOP", "NEW_INDEX_FOR_LOOP"};
int first_linewise[no_of_rules][no_of_terminals] = {0};
int first_ntwise[no_of_nterminals][no_of_terminals] = {0};
int follow[no_of_nterminals][no_of_terminals + 1] = {0};   
int parse_table[no_of_nterminals][no_of_terminals + 1];

// check if a term is a terminal or not
int checkTerminal(char *name)
{
    if (name[0] - 'a' >= 0)
    {
        if ('z' - name[0] < 26)
        {
            return 1;
        }
    }
    return 0;
}

void grammarInitialize(FILE *fp)
{
    char buf[100];
    int lineno = 0;
    char delimit[] = " \n";
    while (fgets(buf, sizeof(buf), fp))
    {
        char *token = strtok(buf, delimit);
        node *curr = (node *)malloc(sizeof(node));
        curr->name = (char *)malloc(sizeof(char) * strlen(token));
        strcpy(curr->name, token);
        curr->isTerminal = checkTerminal(token);
        curr->next = NULL;
        curr->prev = NULL;
        grammar[lineno] = curr;
        token = strtok(NULL, delimit);
        while (token != NULL)
        {
            node *temp = (node *)malloc(sizeof(node));
            temp->name = (char *)malloc(sizeof(char) * strlen(token));
            strcpy(temp->name, token);
            temp->isTerminal = checkTerminal(token);
            temp->next = NULL;
            temp->prev = curr;
            curr->next = temp;
            curr = curr->next;
            token = strtok(NULL, delimit);
        }
        lineno++;
    }
    fclose(fp);
}

void print_gr()
{
    for(int i = 0; i < no_of_rules; i++)
    {
        node* curr = grammar[i];
        while(curr != NULL)
        {
            printf("%s ", curr->name);
            curr = curr -> next;
        }
        printf("\n");
    }
}

int get_col(char *name)
{
    for (int i = 0; i < no_of_terminals; i++)
    {
        if (strcmp(terminal[i], name) == 0)
        {
            return i;
        }
    }
}

int get_row(char *name)
{
    for (int i = 0; i < no_of_rules; i++)
    {
        if (strcmp(grammar[i]->name, name) == 0)
        {
            return i;
        }
    }
    return 0;
}

int get_index_nt(char *name)
{
    for (int i = 0; i < no_of_nterminals; i++)
    {
        if (!strcmp(name, non_terminal[i]))
            return i;
    }
}

int check_rhs(node *rhs)
{
    if (checkTerminal(rhs->name) == 1)
    {
        return 0;
    }

    int flag = 1;
    int r = get_row(rhs->name);
    while ((r < no_of_rules) && (strcmp(rhs->name, grammar[r]->name) == 0))
    {
        if (check_first[r] == 0)
        {
            flag = 0;
        }
        r++;
    }
    return flag;
}

void make_first(int i)
{
    char *lhs = malloc(sizeof(char) * strlen(grammar[i]->name));
    strcpy(lhs, grammar[i]->name);
    node *rhs = malloc(sizeof(node));
    rhs = grammar[i]->next;


    x: 
    while ((rhs != NULL) && (check_rhs(rhs) == 0))
    {
        if (rhs->isTerminal == 1)
        {
            int col = get_col(rhs->name);
            first_linewise[i][col] = 1;
            break;
        }
        else
        {
            int row = get_row(rhs->name);
            if (check_first[row] != 1)
            {
                make_first(row);
            }

            while ((row < no_of_rules) && (strcmp(grammar[row]->name, rhs->name) == 0))
            {
                if (check_first[row] != 1)
                {
                    make_first(row);
                }
                for (int j = 0; j < (no_of_terminals - 1); j++)
                {
                    if ((first_linewise[row][j] == 1))
                    {
                        first_linewise[i][j] = 1;
                    }
                }
                if (first_linewise[row][no_of_terminals - 1] == 1)
                {
                    if (rhs->next == NULL)
                    {
                        first_linewise[i][no_of_terminals - 1] = 1;
                    }
                    rhs = rhs->next;
                    break;
                }
                row++;
            }
            if (row >= no_of_rules)
            {
                break;
            }
        }
    }
    if(rhs == NULL)
    {
        check_first[i] = 1;
        return;
    }
    int row1 = get_row(rhs->name);
    while ((row1 < no_of_rules) && (strcmp(grammar[row1]->name, rhs->name) == 0))
    {
        if (check_first[row1] != 1)
        {
            make_first(row1);
        }
        for (int j = 0; j < (no_of_terminals - 1); j++)
        {
            if ((first_linewise[row1][j] == 1))
            {
                first_linewise[i][j] = 1;
            }
        }
        if (first_linewise[row1][no_of_terminals - 1] == 1)
        {
            if (rhs->next == NULL)
            {
                first_linewise[i][no_of_terminals - 1] = 1;
            }
            rhs = rhs->next; 
            goto x; 
            break;
        }
        (row1)++;
    }
    check_first[i] = 1;
}

void first_nt_in()
{
    for (int i = 0; i < no_of_rules; i++)
    {
        int index = get_index_nt(grammar[i]->name);
        for (int j = 0; j < no_of_terminals; j++)
        {
            if (first_linewise[i][j] == 1)
            {
                first_ntwise[index][j] = 1;
            }
        }
    }
}

void first()
{ 
    for (int i = 0; i < no_of_rules; i++)
    {
        if (check_first[i] == 0)
        {
            make_first(i);
        }
    }
    first_nt_in();
}

void print_first()
{
    for(int i = 0; i<no_of_nterminals; i++)
    { 
        printf("first(%s) -> ", non_terminal[i]);
        for(int j = 0; j<no_of_terminals; j++)
        {
            if(first_ntwise[i][j] == 1)
            {
                printf("%s ", terminal[j]);
            }
        } 
        printf("\n");
    }
}

void fill_follow(int i, int a)
{
    for (int k = 0; k <= no_of_terminals; k++)
    {
        if (follow[a][k] == 1)
        {
            follow[i][k] = 1;
        }
    }
}

void follow_F_first(int i, int a)
{
    for (int j = 0; j < no_of_terminals - 1; j++)
    {
        if (first_ntwise[a][j] == 1)
        {
            follow[i][j] = 1;
        }
    }
}

int first_contains_epsilon(int a)
{
    return first_ntwise[a][no_of_terminals - 1];
}

void make_follow(int i)
{
    if (check_follow[i] == 0)
    {
        for (int j = 0; j < no_of_rules; j++)
        {
            node *p = grammar[j];
            p = p->next;

            while (p != NULL)
            {
                if (!strcmp(p->name, non_terminal[i]))
                {
                    if (p->next == NULL)
                    {
                        int a = get_index_nt(grammar[j]->name);
                        if (!check_follow[a] && i != a)
                        {
                            make_follow(a);
                        }
                        fill_follow(i, a);
                        break;
                    }

                    else if (p->next != NULL && (p->next)->isTerminal == 1)
                    {
                        int b = get_col((p->next)->name); // mark in follow that follow(p) is p->next->name;
                        follow[i][b] = 1;
                        break;
                    }
                    else if (p->next != NULL && (p->next)->isTerminal == 0)
                    {
                        while ((p->next) != NULL)
                        {
                            int a = get_index_nt((p->next)->name);
                            follow_F_first(i, a);          // fill everything except epsilon at initial time
                            if (first_contains_epsilon(a)) // now if the first contains epsilon move to next non terminal in rule
                            {
                                p = p->next;
                            }
                            else // else your job is done simply break
                            {
                                p = p->next;
                                break;
                            }
                        }
                        if (p->next == NULL)
                        {
                            int a = get_index_nt(grammar[j]->name);
                            if (!check_follow[a] && i != a)
                            {
                                make_follow(a);
                            }
                            fill_follow(i, a);
                            break;
                        }
                    }
                }
                else
                {
                    p = p->next;
                }
            }
        }
        check_follow[i] = 1;
    }
}

void follow_set()
{
    follow[0][no_of_terminals] = 1; // Follow of start is $
    check_follow[0] = 1;

    for (int i = 1; i < no_of_nterminals; i++)
    {
        make_follow(i);
    }
}

void print_follow()
{
    for(int i = 0; i<no_of_nterminals; i++)
    {
        printf("follow(%s) -> ", non_terminal[i]);
        for(int j = 0; j<no_of_terminals; j++)
        {
            if(follow[i][j] == 1)
            {
                printf("%s ", terminal[j]);
            }
        }
        if(follow[i][no_of_terminals] == 1)
        {
            printf("$");
        }
        printf("\n");
    }
}

void parse_table_init()
{
    for (int i = 0; i < no_of_nterminals; i++)
    {
        for (int j = 0; j < no_of_terminals + 1; j++)
        {
            parse_table[i][j] = -1;
        }
    }
}

void fill_parse_table()
{
    parse_table_init();
    for (int i = 0; i < no_of_rules; i++)
    {
        int x = get_index_nt(grammar[i]->name);

        if (first_linewise[i][no_of_terminals - 1] == 1)
        {
            for (int k = 0; k <= no_of_terminals; k++)
            {
                if (follow[x][k] == 1)
                {
                    parse_table[x][k] = i;
                }
            }
        }

        for (int j = 0; j < no_of_terminals - 1; j++)
        {
            if (first_linewise[i][j] == 1)
            {
                parse_table[x][j] = i;
            }
        }
    }
}

void print_parsetable()
{
    for(int i = 0; i<no_of_nterminals; i++)
    {
        for(int j = 0; j<no_of_terminals+1; j++)
        {
            printf("%d ", parse_table[i][j]);
        }
        printf("\n");
    }
} 

void push_stack_grammar_rule(stack *st, int rule_no, Treenode *parent)
{
    node *nd = grammar[rule_no];
    node *curr = nd;
    Treenode *children;
    curr = curr->next;
    if (strcmp((nd->next)->name, "epsilon")) 
    {
        TOKEN t;
        t.token = curr->name;
        Treenode *temp = add_firstChild(parent, t);
        temp->parent=parent;
        // printf("%s\n", t.token);
        // printf("%d ",q);
        // q++;
        children = temp;
        curr = curr->next;
    }
    else
    {
        TOKEN t;
        t.token = curr->name;
        Treenode *temp = add_firstChild(parent, t);
        temp->parent=parent;
        // printf("%s\n", t.token);
        // printf("%d ",q);
        // q++;
        return;
    }

    if (curr == NULL)
    {
        TOKEN t;
        Treenode *unit_child = parent->first_child;
        unit_child->parent = parent;
        // printf("%s\n", unit_child->tree_tk.token);
        // printf("%d ",q);
        // q++;
        t.token = unit_child->tree_tk.token;
        push_element(st, t, unit_child);
        return;
    }

    while (curr->next != NULL)
    {
        TOKEN t;
        t.token = curr->name;
        Treenode *temp = add_sibling(children, t);
        temp->parent = parent;
        // printf("%s\n", t.token);
        // printf("%d ",q);
        // q++;
        curr = curr->next;
    }
    TOKEN t;
    t.token = curr->name;
    Treenode *temp = add_sibling(children, t);
    temp->parent = parent;
    // printf("%s\n", t.token);
    // printf("%d ",q);
    //     q++;

    while (temp != children)
    {
        TOKEN t;
        t.token = temp->tree_tk.token;
        push_element(st, t, temp);
        temp = temp->left_sibling;
    }
    TOKEN t2; 
    t2.token = temp->tree_tk.token;
    push_element(st, t2, temp);
}

char* do_uppercase(char *str1)
{
    char* str2 = (char*)malloc(sizeof(char)*strlen(str1)); 
    for(int i=0; i<strlen(str1); i++)
    {
        if(str1[i] >= 'a' && str1[i] <= 'z')
        {
            str2[i] = str1[i] - 32;
        }
        else
        {
            str2[i] = str1[i];
        }
    }
   return str2;
} 

char* do_lowercase(char *str1)
{
   char* str2 = (char*)malloc(sizeof(char)*strlen(str1)); 
   for(int i=0; i<strlen(str1); i++)
   {
        if(str1[i] >= 'A' && str1[i] <= 'Z')
        {
            str2[i] = str1[i] + 32;
        }
        else
        {
            str2[i] = str1[i];
        }
   }
   return str2;
}

int syn_func(char* c1, char* c2) 
{
    int i = get_index_nt(c1);
    char* c3=do_lowercase(c2);

    int j = get_col(c3);

    if (follow[i][j] == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


Treenode* parsing(FILE *fp, stack *st, map mp)
{
    int flag = 1;
    TOKEN tk$;
    tk$.token = "$";
    push_element(st, tk$, NULL);
    
    TOKEN tk_start;
    tk_start.token = grammar[0]->name;
    
    Treenode *tree = create_treenode(tk_start);
    push_element(st, tk_start, tree);
    TOKEN tk = getNextToken(fp,mp);
    char *c = tk.token;
    while(strcmp(c,"LEX_ERR") == 0)
    {
        tk = getNextToken(fp,mp);
        c = tk.token;
    }
   
    while (1)
    {
        char* ch2=top_element(st).tk_stk.token;
        int flag2=0;
        if(!strcmp(tk.token, "ENDFILE"))
        {
            char* str_top = top_element(st).tk_stk.token; 
            while(strcmp(str_top, "$") != 0) 
            { 
                if(checkTerminal(str_top))
                {
                    flag = 0;
                    printf("Error 3 reported,stack still not empty even if token is EOF ----- at line no %d\n",tk.line_num);
                    flag2=1;
                    break;
                } 
                else
                {
                    int index = get_index_nt(str_top); 
                    if(first_ntwise[index][no_of_terminals-1] == 1)
                    {
                        Treenode* address = top_element(st).treenode;
                        pop_element(st); 
                        TOKEN tk_epsilon;
                        tk_epsilon.token="epsilon";
                        Treenode* node = create_treenode(tk_epsilon);
                        address->first_child = node;
                        node->parent = address;
                    } 
                    else
                    {
                        flag = 0;
                        printf("Error 3 reported,stack still not empty even if token is EOF ----- at line no %d\n",tk.line_num);
                        flag2=1;
                        break; 
                    }
                } 
                str_top = top_element(st).tk_stk.token;
            }
            if(flag2==1)
            {
                break;
            }
        }
        if ((strcmp(top_element(st).tk_stk.token, "$") == 0) && (strcmp(tk.token, "ENDFILE") ==0))
        {
            break;
        }
        if (strcmp(top_element(st).tk_stk.token, "$")==0) 
        {
            flag = 0;
            printf("Error 4 ---- stack empty only $ symbol left but token still not EOF, at line no %d\n",tk.line_num);
            break;
        }
        char* ch1=top_element(st).tk_stk.token;
        if (checkTerminal(ch1)==1)
        {
            if (strcmp(do_uppercase(ch1), c)==0)
            {
                Treenode* address = top_element(st).treenode;
                pop_element(st);
                address->tree_tk.line_num = tk.line_num;
                if(!strcmp(address->tree_tk.token,"NUM"))
                {
                    address->tree_tk.value_num = tk.value_num;
                }
                else if(!strcmp(address->tree_tk.token,"RNUM"))
                {
                    address->tree_tk.value_rnum = tk.value_rnum;
                }
                else
                {
                    strncpy(address->tree_tk.value_id, tk.value_id, 100);
                }

                tk = getNextToken(fp,mp);
                c = tk.token;
                while(strcmp(c,"LEX_ERR") == 0)
                {
                    tk = getNextToken(fp,mp);
                    c = tk.token;
                }
                if(strcmp(c,"ENDFILE") == 0)
                {
                    continue;
                }
            }
            else
            {
                flag = 0;
                printf("Error1 reported ---- terminals not same, at line no %d \n",tk.line_num);
                pop_element(st);
                continue;
            }
        }
        else
        {
            while (checkTerminal(top_element(st).tk_stk.token)==0)
            {
                
                int i = get_index_nt(top_element(st).tk_stk.token); 
                char* lower_c = do_lowercase(c);
                int j = get_col(lower_c);
                Treenode *parent = top_element(st).treenode;

               
                if (parse_table[i][j] != -1)
                {
                    pop_element(st);
                    
                    parent->rule_no = parse_table[i][j]+1;
                    // printf("%d %s\n", parent->rule_no, parent->tree_tk.token);
                    // printf("%s %s\n",non_terminal[i],terminal[j]);
                    // if (i == 2 && j == no_of_terminals-1)
                    // {
                    
                   
                    // }
                    // printf("hello\n");
                    // printf("%d\n", parent->rule_no);
                    
                    push_stack_grammar_rule(st, parse_table[i][j], parent);
                    // printf("Hello");
                    // printf("\n%d %s %s\n\n", parent->rule_no, parent->tree_tk.token, parent->first_child->tree_tk.token);
                }
                else if(parse_table[i][j] == -1)
                {
                    flag = 0;
                    printf("Error2 reported------ no rule found, at line no %d \n",tk.line_num);
                    if(syn_func(top_element(st).tk_stk.token, c)==1)
                    {
                        pop_element(st);
                    }
                    else
                    {
                        tk = getNextToken(fp, mp);
                        c = tk.token;
                        while(strcmp(c,"LEX_ERR") == 0)
                        {
                            tk = getNextToken(fp,mp);
                            c = tk.token;
                        }
                        if(strcmp(c,"ENDFILE") == 0)
                        {
                            break;
                        }   
                    }
                }                    
            }
        }
    }

    if (flag == 1)
    {
        printf("Input source code is syntactically correct...........\n \n \n");
    }

    return tree;
}

// int main()
// {
//     FILE *fp = fopen("grammar.txt", "r");
  
//     grammarInitialize(fp);
//     // print_gr();
//     // printf("\n\n\n");

//     first();
//     // print_first();
//     //  printf("\n\n\n");

//     follow_set();
//     //  print_follow();
//     //  printf("\n\n\n");

//     fill_parse_table();
//     // print_parsetable();
//     // printf("\n\n\n"); 

//     FILE* ptr=fopen("testcase.txt","r");
//     map mp;
//     mp=create_hashtable();
//     ht_init(mp);
//     fill_buffer_int(ptr); 
//     stack *st = create();
//     parsing(fp, st, mp);
//     return 0;
// }