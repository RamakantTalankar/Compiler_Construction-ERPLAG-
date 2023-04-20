// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

list *create_list()
{
    list *list1;
    list1 = (list *)malloc(sizeof(struct list));
    return list1;
}

st *create_st()
{
    st *st_table;
    st_table = (st *)malloc(sizeof(struct st));
    for (int i = 0; i < 53; i++)
    {
        (st_table->hash_array[i]) = NULL;
    }
    return st_table;
}

st_entry *create_st_entry()
{
    st_entry *ptr = (st_entry *)malloc(sizeof(struct st_entry));
    return ptr;
}

int st_hashfunction(char *k)
{

    if (k[0] == '_')
    {
        return 52;
    }
    if (k[0] <= 'Z' && k[0] >= 'A')
    {
        return abs(k[0] - 'A');
    }
    if (k[0] <= 'z' && k[0] >= 'a')
    {
        return 26 + abs(k[0] - 'a');
    }
}

void insert_symtable(st *sym_table, st_entry *entry)
{
    
    int index = st_hashfunction(entry->name);

    if (sym_table->hash_array[index] == NULL)
    {
        sym_table->hash_array[index] = entry;
    }
    else
    {
        st_entry* temp = sym_table->hash_array[index];
        int ramakant;

        while (temp->next_entry != NULL)
        {
            temp = temp->next_entry;
        }
        temp->next_entry = entry;
    }
}

st_entry *search_symtable(st *sym_table, Treenode *node)
{
    int index = st_hashfunction(node->tree_tk.value_id);

    if (sym_table->hash_array[index] == NULL)
    {
        st_entry *entry = create_st_entry();
        entry->next_entry = NULL;
        entry->name = "not found";
        return entry;
    }
    else
    {
        st_entry *temp = sym_table->hash_array[index];

        while (temp != NULL)
        {
            if (!strcmp(node->tree_tk.value_id, temp->name))
            {
                return temp;
            }
            temp = temp->next_entry;
        }
    }
}

void insert_list_input(Treenode *tree, st_entry *entry)
{
    

    Treenode* node = tree;
    list *result = NULL;
    list* last = NULL;
    while (node)
    {
        char* c = node->tree_tk.token;
        if (!strcmp(c, "ARRAY_DATATYPE"))
        {
            if (result == NULL)
            {
                struct list *lt = create_list();
                // lt->type.type_name = node->tree_tk.token;
                // fill_list_array_type_struct(node->right_sibling, lt);
                fill_list_array_type_struct(node, lt);
                node = node->right_sibling;
                lt->name = node->tree_tk.value_id;
                node = node->right_sibling;
                result = lt;
                last = result;
            }
            else
            {
                struct list *lt = create_list();
                // lt->type.type_name = node->tree_tk.token;
                // fill_list_array_type_struct(node->right_sibling, lt);
                fill_list_array_type_struct(node, lt);
                node = node->right_sibling;
                lt->name = node->tree_tk.value_id;
                node = node->right_sibling;
                last->next = lt;
                last = last->next;
            }
        }
        else
        {
            if(!result)
            {
                list *lt = create_list();
                lt->type.type_name = node->tree_tk.token;
                node = node->right_sibling;
                lt->name = node->tree_tk.value_id;
                node = node->right_sibling;
                result = lt;
                last = result;
            }
            else
            {
                list *lt = create_list();
                lt->type.type_name = node->tree_tk.token;
                node = node->right_sibling;
                lt->name = node->tree_tk.value_id;
                node = node->right_sibling;
                last->next = lt;
                last = last->next;
            }




        }

    }


    entry->type.input_list = result;
}

void insert_list_output(Treenode *tree, st_entry *entry)
{

    Treenode *node = tree;
    list *result = NULL;
    list *last = NULL;
    while (node)
    {
        if (!strcmp(node->tree_tk.token, "ARRAY_DATATYPE"))
        {
            if (result == NULL)
            {
                struct list *lt = create_list();
                // lt->type.type_name = node->tree_tk.token;
                // fill_list_array_type_struct(node->right_sibling, lt);
                fill_list_array_type_struct(node, lt);
                node = node->right_sibling;
                lt->name = node->tree_tk.value_id;
                node = node->right_sibling;
                result = lt;
                last = result;
            }
            else
            {
                struct list *lt = create_list();
                // lt->type.type_name = node->tree_tk.token;
                fill_list_array_type_struct(node, lt);
                node = node->right_sibling;
                lt->name = node->tree_tk.value_id;
                node = node->right_sibling;
                last->next = lt;
                last = last->next;
            }
        }
        else
        {
            if (result == NULL)
            {
                struct list *lt = create_list();
                lt->type.type_name = node->tree_tk.token;
                node = node->right_sibling;
                lt->name = node->tree_tk.value_id;
                node = node->right_sibling;
                result = lt;
                last = result;
            }
            else
            {
                struct list *lt = create_list();
                lt->type.type_name = node->tree_tk.token;
                node = node->right_sibling;
                lt->name = node->tree_tk.value_id;
                node = node->right_sibling;
                last->next = lt;
                last = last->next;
            }
        }
    }

    entry->type.output_list = result;
}


int string_to_int(char *string)
{
    if (!strcmp(string, "MAIN_PROG"))
    {
        return 0;
    }
    else if (!strcmp(string, "AST_MODULEDECLARATIONS"))
    {
        return 1;
    }
    else if (!strcmp(string, "AST_OTHERMODULES"))
    {
        return 2;
    }
    else if (!strcmp(string, "AST_MODULE"))
    {
        return 3;
    }
    else if (!strcmp(string, "id"))
    {
        return 4;
    }
    else if (!strcmp(string, "INPUT_PARAMETERS"))
    {
        return 5;
    }
    else if (!strcmp(string, "OUTPUT_PARAMETERS"))
    {
        return 6;
    }
    else if (!strcmp(string, "STMT_LIST"))
    {
        return 7;
    }
    else if (!strcmp(string, "SCANSTMT"))
    {
        return 8;
    }
    else if (!strcmp(string, "PRINTSTMT"))
    {
        return 9;
    }
    else if (!strcmp(string, "AST_DECLARESTATEMENT"))
    {
        return 10;
    }
    else if (!strcmp(string, "FOR_STMT"))
    {
        return 11;
    }
    else if (!strcmp(string, "WHILE_STMT"))
    {
        return 12;
    }
    else if (!strcmp(string, "ASSIGN"))
    {
        return 13;
    }
    else if (!strcmp(string, "INVOKE_FUNCTION"))
    {
        return 14;
    }
    else if (!strcmp(string, "SWITCH_CASE"))
    {
        return 15;
    }
    else if (!strcmp(string, "CASE_NUM"))
    {
        return 16;
    }
    else if (!strcmp(string, "AST_DEFAULT"))
    {
        return 17;
    }
    else if (!strcmp(string, "AST_CASE"))
    {
        return 18;
    }
    else if(!strcmp(string,"AST_DRIVERDEF"))
    {
        return 19;
    }
}

// fill_declare(sym_table,temp->first_child);

// fill_array_type_struct(last_ptr,entry);
char *to_string(int x)
{

    char* string= (char*)malloc(sizeof(char)*50);
    sprintf(string, "%d", x);
    return string;
}

// void fill_array_type_struct_list_entry
void fill_list_array_type_struct(Treenode *array_node, list *lt)
{
    

    lt->type.arr_type = array_node->first_child->tree_tk.token;
    Treenode *index_expr1 = array_node->first_child->right_sibling->first_child;
    Treenode *index_expr2 = index_expr1->right_sibling;
    int static_dynamic = 0;

    if (!strcmp(index_expr1->first_child->tree_tk.token, "num"))
    {
        lt->type.lower_index = to_string(index_expr1->first_child->tree_tk.value_num);
    }
    else if (!strcmp(index_expr1->first_child->tree_tk.token, "id"))
    {
        static_dynamic = 1;
        lt->type.lower_index = index_expr1->first_child->tree_tk.value_id;
    }

    if (!strcmp(index_expr2->first_child->tree_tk.token, "num"))
    {
        lt->type.higher_index = to_string(index_expr2->first_child->tree_tk.value_num);
    }
    else if (!strcmp(index_expr2->first_child->tree_tk.token, "id"))
    {
        static_dynamic = 1;
        lt->type.higher_index = index_expr2->first_child->tree_tk.value_id;
    }

    if (index_expr1->first_child->right_sibling)
    {
        lt->type.lower_sign = index_expr1->first_child->right_sibling->tree_tk.token;
    }
    else
    {
        lt->type.lower_sign = NULL;
    }

    if (index_expr2->first_child->right_sibling)
    {
        lt->type.higher_sign = index_expr2->first_child->right_sibling->tree_tk.token;
    }
    else
    {
        lt->type.higher_sign = NULL;
    }

    lt->type.array_static_dynamic = static_dynamic;
}

void fill_array_type_struct(Treenode *array_node, st_entry *entry)
{
    entry->type.arr_type = array_node->first_child->tree_tk.token;
    Treenode *index_expr1 = array_node->first_child->right_sibling->first_child;
    Treenode *index_expr2 = index_expr1->right_sibling;
    int static_dynamic = 0;

    if (!strcmp(index_expr1->first_child->tree_tk.token, "num"))
    {
        entry->type.lower_index = to_string(index_expr1->first_child->tree_tk.value_num);
    }
    else if (!strcmp(index_expr1->first_child->tree_tk.token, "id"))
    {
        static_dynamic = 1;
        entry->type.lower_index = index_expr1->first_child->tree_tk.value_id;
    }

    if (!strcmp(index_expr2->first_child->tree_tk.token, "num"))
    {
        entry->type.higher_index = to_string(index_expr2->first_child->tree_tk.value_num);
    }
    else if (!strcmp(index_expr2->first_child->tree_tk.token, "id"))
    {
        static_dynamic = 1;
        entry->type.higher_index = index_expr2->first_child->tree_tk.value_id;
    }

    if (index_expr1->first_child->right_sibling)
    {
        entry->type.lower_sign = index_expr1->first_child->right_sibling->tree_tk.token;
    }
    else
    {
        entry->type.lower_sign = NULL;
    }

    if (index_expr2->first_child->right_sibling)
    {
        entry->type.higher_sign = index_expr2->first_child->right_sibling->tree_tk.token;
    }
    else
    {
        entry->type.higher_sign = NULL;
    }

    
    


    entry->type.array_static_dynamic = static_dynamic;
}

 void fill_declare(st* sym_table, Treenode* tr_node)
{ 
    int width_g = 0;                                
    char *temp_type;
    temp_type = tr_node->tree_tk.token;
    if(!strcmp(temp_type,"integer"))
    {
        width_g = 2;
    }
    else if (!strcmp(temp_type, "boolean"))
    {
        width_g = 1;

    }
    else if(!strcmp(temp_type,"real"))
    {
        width_g = 4;
    }

    Treenode *temp = tr_node;
    Treenode *temp2= tr_node;
    temp=temp->right_sibling;

    while (temp!= NULL)
    {
        st_entry *entry = create_st_entry();
        entry->st_ptr=NULL;
        entry->next_entry=NULL;
        entry->name = temp->tree_tk.value_id;
        if (!strcmp(temp_type, "ARRAY_DATATYPE"))
        {
            entry->type.type_name = "array";
            fill_array_type_struct(temp2, entry);
        }
        else
        {
            entry->type.type_name = temp_type;
            sym_table->activation_size += width_g;
        }
        entry->own_st = sym_table;
        insert_symtable(sym_table, entry);
        temp = temp->right_sibling;
    }

    
}

void symbol_table_creation(Treenode *ast, st *sym_table)
{
    int i = string_to_int(ast->tree_tk.token);
    
    st_entry *entry;
    switch (i)
    {
        
    case 0: ;// program
        Treenode *temp1= ast;
        temp1 = temp1->first_child->right_sibling;
        symbol_table_creation(temp1, sym_table);
        break;

    case 2: ;// othermodules
        Treenode *temp2 = ast;
        if (temp2->first_child)
        {
            symbol_table_creation(temp2->first_child, sym_table);
        }
        if (temp2->right_sibling)
        {
            symbol_table_creation(temp2->right_sibling, sym_table);
        }
        break;

    case 3: ; // module
        Treenode *temp3 = ast;
        if (temp3->first_child)
        {
            symbol_table_creation(temp3->first_child, sym_table);
        }
        if (temp3->right_sibling)
        {
            symbol_table_creation(temp3->right_sibling, sym_table);
        }
        break;

    case 4: ;// id
        Treenode *temp4 = ast;
        if (temp4->parent != NULL && !strcmp(temp4->parent->tree_tk.token , "AST_MODULE"))
        {
            st_entry *entry = create_st_entry();
            entry->next_entry = NULL;
            entry->name = temp4->tree_tk.value_id;
            entry->own_st = sym_table;
            entry->type.type_name = "function";

            st *sym_table_function = create_st();
            entry->st_ptr = sym_table_function;
            sym_table_function->st_parent = sym_table;
            sym_table_function->start_scope = temp4->tree_tk.line_num; // end scope ka resolve karna hai.
            sym_table_function->nesting_level = sym_table->nesting_level + 1;
            sym_table_function->module_name = entry->name;
            sym_table_function->activation_size = 0;
            insert_symtable(sym_table, entry);
            temp4 = temp4->right_sibling;
            symbol_table_creation(temp4, sym_table);
        }
        break;

    case 5:; // input_parameters
        Treenode *temp5 = ast;
        st_entry *entry = search_symtable(sym_table, temp5->left_sibling);
        insert_list_input(temp5->first_child, entry);
        symbol_table_creation(temp5->right_sibling, sym_table);
        break;

    case 6:; // output_parameters
        Treenode *temp6 = ast;
        st_entry *entry1 = search_symtable(sym_table, temp6->left_sibling->left_sibling);
        insert_list_output(temp6->first_child, entry1);
        symbol_table_creation(temp6->right_sibling, entry1->st_ptr);
        break;

    case 7:; // statements(STMT_LIST)
        Treenode *temp7 = ast;
        if (temp7->first_child)
        {
            symbol_table_creation(temp7->first_child, sym_table);
        }
        break;

    case 8:; // scanstmt
        Treenode *temp8 = ast;
        if (temp8->right_sibling)
        {
            symbol_table_creation(temp8->right_sibling, sym_table);
        }
        break;

    case 9:; // printstmt
        Treenode *temp9 = ast;
        if (temp9->right_sibling)
        {
            symbol_table_creation(temp9->right_sibling, sym_table);
        }
        break;

        // to ask desai about assignment stmt node.

    case 10:; // declare stmt
        Treenode *temp10 = ast;
        // st_entry* entry = search_symtable(sym_table,temp->left_sibling->left_sibling->left_sibling);
         fill_declare(sym_table, temp10->first_child);
        if (temp10->right_sibling)
        {
            symbol_table_creation(temp10->right_sibling, sym_table);
        }
        break;

    case 11: ;// for stmt
        Treenode *temp11 = ast;
        entry = create_st_entry();
        entry->next_entry = NULL;
        entry->name = "for";
        entry->own_st = sym_table;
        st *sym_table_for_loop = create_st();
        entry->st_ptr = sym_table_for_loop;
        sym_table_for_loop->st_parent = sym_table;
        sym_table_for_loop->nesting_level = sym_table->nesting_level + 1;
        sym_table_for_loop->module_name = sym_table->module_name;
        sym_table_for_loop->start_scope = temp11->tree_tk.line_num;
        sym_table_for_loop->activation_size = 0;
        insert_symtable(sym_table, entry);
        symbol_table_creation(temp11->first_child->right_sibling->right_sibling, sym_table_for_loop);
        if (temp11->right_sibling)
        {
            symbol_table_creation(temp11->right_sibling, sym_table);
        }
        break;

    case 12: ;// while loop
        Treenode *temp12 = ast;
        entry = create_st_entry();
        entry->next_entry = NULL;
        entry->name = "while";
        entry->own_st = sym_table;
        st *sym_table_while_loop = create_st();
        entry->st_ptr = sym_table_while_loop;
        sym_table_while_loop->st_parent = sym_table;
        sym_table_while_loop->nesting_level = sym_table->nesting_level + 1;
        sym_table_while_loop->module_name = sym_table->module_name;
        sym_table_while_loop->start_scope = temp12->tree_tk.line_num;
        sym_table_while_loop->activation_size = 0;
        insert_symtable(sym_table, entry);
        symbol_table_creation(temp12->first_child->right_sibling, sym_table_while_loop);
        if(temp12->right_sibling)
        {
            symbol_table_creation(temp12->right_sibling, sym_table);
        }
        break;

        // ask desai to draw the ast of conditional statement.

    case 13: ;// assign
        Treenode *temp13 = ast;
        if (temp13->right_sibling)
        {
            symbol_table_creation(temp13->right_sibling, sym_table);
        }
        break;

    case 14: ;// invoke_function
        Treenode *temp14 = ast;
        if (temp14->right_sibling)
        {
            symbol_table_creation(temp14->right_sibling, sym_table);
        }
        break;

    case 15: ;// switch_case
        Treenode *temp15 = ast;
        symbol_table_creation(temp15->first_child->right_sibling, sym_table);
        break;

    case 16:; // case_num
        Treenode *temp16= ast;
        entry = create_st_entry();
        entry->next_entry = NULL;
        entry->name = "switch";
        entry->own_st = sym_table;
        st *sym_table_switch_stmt = create_st();
        entry->st_ptr = sym_table_switch_stmt;
        sym_table_switch_stmt->st_parent = sym_table;
        sym_table_switch_stmt->nesting_level = sym_table->nesting_level + 1;
        sym_table_switch_stmt->module_name = sym_table->module_name;
        sym_table_switch_stmt->start_scope = temp16->tree_tk.line_num;
        sym_table_switch_stmt->activation_size = 0;
        insert_symtable(sym_table, entry);
        if (temp16->first_child)
        {
            symbol_table_creation(temp16->first_child, sym_table_switch_stmt);
        }
        if (temp16->right_sibling)
        {
            symbol_table_creation(temp16->right_sibling, sym_table);
        }
        break;

    case 17:; // AST_DEFAUL
        Treenode *temp17 = ast;
        if (temp17->first_child)
        {
            symbol_table_creation(temp17->first_child, sym_table);
        }
        break;

    case 18: ;// ast_case
        Treenode *temp18 = ast;
        entry = create_st_entry();
        entry->next_entry = NULL;
        entry->name = "case";
        entry->own_st = sym_table;
        st *sym_table_ast_case = create_st();
        entry->st_ptr = sym_table_ast_case;
        sym_table_ast_case->st_parent = sym_table;
        sym_table_ast_case->nesting_level = sym_table->nesting_level + 1;
        sym_table_ast_case->module_name = sym_table->module_name;
        sym_table_ast_case->start_scope = temp18->tree_tk.line_num;
        sym_table_ast_case->activation_size = 0;
        insert_symtable(sym_table, entry);

        if (temp18->right_sibling)
        {
            symbol_table_creation(temp18->right_sibling, sym_table);
        }
        if (temp18->first_child && temp18->first_child->right_sibling)
        {
            symbol_table_creation(temp18->first_child->right_sibling, sym_table_ast_case);
        }
     
       break;
    
    case 19: ;//drivermodule
        Treenode* temp19=ast;
        if (temp19->first_child)
        {
            symbol_table_creation(temp19->first_child, sym_table);
        }
        if (temp19->right_sibling)
        {
            symbol_table_creation(temp19->right_sibling, sym_table);
        }
        
        break;
    }
}

// struct st_entry
// {
//     char *name;
//     Type type;
//     st *st_ptr;
//     st_entry *next_entry;
//     st *own_st; // points to the symbol table whare the entry resides in order to pass it to the parent;
// };

// struct st
// {
//     st_entry *hash_array[53];
//     st *st_parent;
//     int start_scope;
//     int end_scope;
//     char *module_name;
//     int nesting_level;
// };

void print_symbol_table_old(st *sym_table)
{
    for (int i = 0; i < 53; i++)
    {
        st_entry *temp = sym_table->hash_array[i];
        while (temp != NULL)
        {
            if (strcmp(temp->type.type_name, "array"))
            {
                int width;
                if (!strcmp(temp->type.type_name, "integer"))
                {
                    width = 2;
                }
                else if (!strcmp(temp->type.type_name, "real"))
                {
                    width = 4;
                }
                else if (!strcmp(temp->type.type_name, "boolean"))
                {
                    width = 1;
                }

                if (temp->st_ptr == NULL)
                {
                    printf("id:%s  scope:%s  start:%d  type = %s  isarray = no  Static/dynamic:**   array range:**  width:%d  offset:  nesting_level:%d\n", temp->name, temp->own_st->module_name, temp->own_st->start_scope, temp->type.type_name, width, temp->own_st->nesting_level);
                }
                else
                {
                    print_symbol_table_old(temp->st_ptr);
                }
                temp = temp->next_entry;
            }
            else
            {
                char* sign_low = (char*) malloc(sizeof(char*));
                char *sign_high = (char *)malloc(sizeof(char *));
                if (temp->type.lower_sign)
                {
                    sign_low = temp->type.lower_sign;
                }
                else
                {
                    sign_low = " ";
                }

                if (temp->type.higher_sign)
                {
                    sign_high = temp->type.higher_sign;
                }
                else
                {
                    sign_high = " ";
                }

                int width;
                if (!strcmp(temp->type.arr_type, "integer"))
                {
                    width = 2;
                }
                else if (!strcmp(temp->type.arr_type, "real"))
                {
                    width = 4;
                }
                else if (!strcmp(temp->type.arr_type, "boolean"))
                {
                    width = 1;
                }

                if (temp->type.array_static_dynamic == 0)
                {
                    width = width * (atoi(temp->type.higher_index) - atoi(temp->type.lower_index) + 1) + 1;
                    if (temp->st_ptr == NULL)
                    {
                        printf("id:%s  scope:%s  start:%d  type = %s  isarray = yes     Static/dynamic: static   array range:[%s %s , %s %s] width:%d offset:  nesting_level:%d\n", temp->name, temp->own_st->module_name, temp->own_st->start_scope, temp->type.arr_type, sign_low, temp->type.lower_index, sign_high, temp->type.higher_index, width, temp->own_st->nesting_level);
                    }
                    else
                    {
                        print_symbol_table(temp->st_ptr);
                    }
                }
                else
                {
                    if (temp->st_ptr == NULL)
                    {
                        printf("id:%s  scope:%s  start:%d  type = %s  isarray = yes    Static/dynamic:dynamic  array range:[%s %s , %s %s] width:** offset: nesting_level:%d\n", temp->name, temp->own_st->module_name, temp->own_st->start_scope, temp->type.arr_type, sign_low, temp->type.lower_index, sign_high, temp->type.higher_index, temp->own_st->nesting_level);
                    }
                    else
                    {
                        print_symbol_table_old(temp->st_ptr);
                    }
                }
                temp = temp->next_entry;
            }

            
        }
    }
}

void print_symbol_table(st *sym_table)
{
   
    char *dash = "----";
    char *yes = "yes";
    char *no = "no";
    char *p_static = "static";
    char *p_dyn = "dynamic";
    char *p_sqbc = "]";

    // printf("%-30s %-30s %-30s %-30s %-30s %-30s %-30s %-30s %-30s %-30s %-30s", p_id, p_scope, p_start, p_end, p_type, p_isarray, p_st_dyn, p_arr_range, p_width, p_offset, p_nest_lvl);

    for (int i = 0; i < 53; i++)
    {
        st_entry *temp = sym_table->hash_array[i];
        while (temp != NULL)
        {
            if (strcmp(temp->type.type_name, "array"))
            {
                int width;
                if (!strcmp(temp->type.type_name, "integer"))
                {
                    width = 2;
                }
                else if (!strcmp(temp->type.type_name, "real"))
                {
                    width = 4;
                }
                else if (!strcmp(temp->type.type_name, "boolean"))
                {
                    width = 1;
                }

                if (temp->st_ptr == NULL)
                {
                    printf("%-30s %-30s [%d, %s%-30s %-30s %-30s %-30s %-50s %-30d %-30s %-30d\n", temp->name, temp->own_st->module_name, temp->own_st->start_scope, dash, p_sqbc, temp->type.type_name, no, dash, dash, width, dash, temp->own_st->nesting_level);
                }
                else
                {
                    print_symbol_table(temp->st_ptr);
                }
                temp = temp->next_entry;
            }
            else
            {
                char *sign_low = (char *)malloc(sizeof(char *));
                char *sign_high = (char *)malloc(sizeof(char *));
                if (temp->type.lower_sign)
                {
                    if(strcmp(temp->type.lower_sign, "minus") == 0)
                    {
                        sign_low = "-";
                    }
                    else if (strcmp(temp->type.lower_sign, "plus") == 0)
                    {
                        sign_low = "+";
                    }
                    else
                    {
                        sign_low = " ";
                    }
                    // sign_low = temp->type.lower_sign;
                }
                else
                {
                    sign_low = " ";
                }

                // if (temp->type.higher_sign)
                // {
                //     sign_high = temp->type.higher_sign;
                // }
                // else
                // {
                //     sign_high = " ";
                // }

                if (temp->type.higher_sign)
                {
                    if (strcmp(temp->type.higher_sign, "minus") == 0)
                    {
                        sign_high = "-";
                    }
                    else if (strcmp(temp->type.higher_sign, "plus") == 0)
                    {
                        sign_high = "+";
                    }
                    else
                    {
                        sign_high = " ";
                    }
                }
                else
                {
                    sign_high = " ";
                }

                int width;
                if (!strcmp(temp->type.arr_type, "integer"))
                {
                    width = 2;
                }
                else if (!strcmp(temp->type.arr_type, "real"))
                {
                    width = 4;
                }
                else if (!strcmp(temp->type.arr_type, "boolean"))
                {
                    width = 1;
                }

                if (temp->type.array_static_dynamic == 0)
                {
                    int x=1;
                    int y=1;
                    if(!strcmp(sign_low,"-"))
                    {
                        x=-1;
                    }
                    if(!strcmp(sign_high,"-"))
                    {
                        y=-1;
                    }
                    
                    width = width * (y*atoi(temp->type.higher_index) - x*atoi(temp->type.lower_index) + 1) + 1;
                    if (temp->st_ptr == NULL)
                    {
                        printf("%-30s %-30s [%d ,%s%-30s %-30s %-30s %-30s [%s %s , %s %s%-37s %-30d %-30s %-30d\n", temp->name, temp->own_st->module_name, temp->own_st->start_scope, dash, p_sqbc, temp->type.arr_type, yes, p_static, sign_low, temp->type.lower_index, sign_high, temp->type.higher_index, p_sqbc,width, dash, temp->own_st->nesting_level);
                    }
                    else
                    {
                        print_symbol_table(temp->st_ptr);
                    }
                }
                else
                {
                    if (temp->st_ptr == NULL)
                    {
                        printf("%-30s %-30s [%d, %s%-30s %-30s %-30s %-30s [%s %s , %s %s%-37s %-30s %-30s %-30d\n", temp->name, temp->own_st->module_name, temp->own_st->start_scope, dash, p_sqbc, temp->type.arr_type, yes, p_dyn, sign_low, temp->type.lower_index, sign_high, temp->type.higher_index, p_sqbc,dash, dash, temp->own_st->nesting_level);
                    }
                    else
                    {
                        print_symbol_table(temp->st_ptr);
                    }
                }
                temp = temp->next_entry;
            }
        }
    }
}





void print_symbol_table_array(st *sym_table)
{

    char *dash = "----";
    char *yes = "yes";
    char *no = "no";
    char *p_static = "static";
    char *p_dyn = "dynamic";
    char *p_sqbc = "]";

    // printf("%-30s %-30s %-30s %-30s %-30s %-30s %-30s %-30s %-30s %-30s %-30s", p_id, p_scope, p_start, p_end, p_type, p_isarray, p_st_dyn, p_arr_range, p_width, p_offset, p_nest_lvl);

    for (int i = 0; i < 53; i++)
    {
        st_entry *temp = sym_table->hash_array[i];
        while (temp != NULL)
        {
            if (strcmp(temp->type.type_name, "array"))
            {
                int width;
                if (!strcmp(temp->type.type_name, "integer"))
                {
                    width = 2;
                }
                else if (!strcmp(temp->type.type_name, "real"))
                {
                    width = 4;
                }
                else if (!strcmp(temp->type.type_name, "boolean"))
                {
                    width = 1;
                }

                if (temp->st_ptr == NULL)
                {
                    // printf("%-30s %-30s [%d, %s%-30s %-30s %-30s %-30s %-50s %-30d %-30s %-30d\n", temp->name, temp->own_st->module_name, temp->own_st->start_scope, dash, p_sqbc, temp->type.type_name, no, dash, dash, width, dash, temp->own_st->nesting_level);
                }
                else
                {
                    print_symbol_table_array(temp->st_ptr);
                }
                temp = temp->next_entry;
            }
            else
            {
                char *sign_low = (char *)malloc(sizeof(char *));
                char *sign_high = (char *)malloc(sizeof(char *));
                if (temp->type.lower_sign)
                {
                    if (strcmp(temp->type.lower_sign, "minus") == 0)
                    {
                        sign_low = "-";
                    }
                    else if (strcmp(temp->type.lower_sign, "plus") == 0)
                    {
                        sign_low = "+";
                    }
                    else
                    {
                        sign_low = " ";
                    }
                    // sign_low = temp->type.lower_sign;
                }
                else
                {
                    sign_low = " ";
                }

                // if (temp->type.higher_sign)
                // {
                //     sign_high = temp->type.higher_sign;
                // }
                // else
                // {
                //     sign_high = " ";
                // }

                if (temp->type.higher_sign)
                {
                    if (strcmp(temp->type.higher_sign, "minus") == 0)
                    {
                        sign_high = "-";
                    }
                    else if (strcmp(temp->type.higher_sign, "plus") == 0)
                    {
                        sign_high = "+";
                    }
                    else
                    {
                        sign_high = " ";
                    }
                }
                else
                {
                    sign_high = " ";
                }

                int width;
                if (!strcmp(temp->type.arr_type, "integer"))
                {
                    width = 2;
                }
                else if (!strcmp(temp->type.arr_type, "real"))
                {
                    width = 4;
                }
                else if (!strcmp(temp->type.arr_type, "boolean"))
                {
                    width = 1;
                }

                if (temp->type.array_static_dynamic == 0)
                {
                    int x = 1;
                    int y = 1;
                    if (!strcmp(sign_low, "-"))
                    {
                        x = -1;
                    }
                    if (!strcmp(sign_high, "-"))
                    {
                        y = -1;
                    }

                    width = width * (y * atoi(temp->type.higher_index) - x * atoi(temp->type.lower_index) + 1) + 1;
                    if (temp->st_ptr == NULL)
                    {

                        // printf("scope:%s  start:%d  id:%s    static array   array range:[%s %s , %s %s]  type = %s ",temp->own_st->module_name,temp->own_st->start_scope,temp->name, temp->type.array_static_dynamic,sign_low,temp->type.lower_index,sign_high,temp->type.higher_index,temp->type.arr_type);

                        // printf("%s  %d  %s   static array   [%s %s , %s %s]   %s \n", temp->own_st->module_name, temp->own_st->start_scope, temp->name, sign_low, temp->type.lower_index, sign_high, temp->type.higher_index, temp->type.arr_type);

                        printf("%-30s [%d ,%s%-30s %-30s %-30s [%s %s , %s %s%-37s %-30s\n", temp->own_st->module_name, temp->own_st->start_scope, dash, p_sqbc, temp->name, p_static, sign_low, temp->type.lower_index, sign_high, temp->type.higher_index, p_sqbc, temp->type.arr_type);
                    }
                    else
                    {
                        print_symbol_table_array(temp->st_ptr);
                    }
                }
                else
                {
                    if (temp->st_ptr == NULL)
                    {
                        // printf("%s  %d  %s   dynamic array   [%s %s , %s %s]   %s \n", temp->own_st->module_name, temp->own_st->start_scope, temp->name, sign_low, temp->type.lower_index, sign_high, temp->type.higher_index, temp->type.arr_type);

                        printf("%-30s [%d ,%s%-30s %-30s %-30s [%s %s , %s %s%-37s %-30s\n", temp->own_st->module_name, temp->own_st->start_scope, dash, p_sqbc, temp->name, p_dyn, sign_low, temp->type.lower_index, sign_high, temp->type.higher_index, p_sqbc, temp->type.arr_type);
                    }
                    else
                    {
                        print_symbol_table_array(temp->st_ptr);
                    }
                }
                temp = temp->next_entry;
            }
        }
    }
}