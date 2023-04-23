// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#include "AST.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Treenode *iterate_child(Treenode *parent, char *name)
{
    Treenode *temp = parent->first_child;
    while (temp != NULL)
    {
        if (!strcmp(temp->tree_tk.token, name))
        {
            return temp;
        }
        temp = temp->right_sibling;
    }
    return NULL;
}

Treenode *make_node(char *name, Treenode *child1, Treenode *child2)
{

    Treenode *temp = (Treenode *)malloc(sizeof(struct Treenode));
    temp->tree_tk.token = name;
    temp->right_sibling = NULL;
    temp->left_sibling = NULL;
    temp->first_child = child1;
    Treenode *temp1 = child1;
    Treenode *prev = NULL;
    if (child1 == NULL)
        return temp;

    if (child1)
    {
        while (temp1 != NULL)
        {
            temp1->parent = temp;
            prev = temp1;
            temp1 = temp1->right_sibling;
        }
    }

    if (child2)
    {
        Treenode *ptr = prev;
        ptr->right_sibling = child2;
        child2->left_sibling = ptr;
        Treenode *temp2 = child2;

        while(temp2 != NULL)
        {
            temp2->parent = temp;
            temp2 = temp2->right_sibling;
        }
    }
    else
    {
        prev->right_sibling = NULL;
    }

    return temp;
}

Treenode *make_node_wo_name(Treenode *node, Treenode *child1, Treenode *child2)
{
    Treenode *temp = (Treenode *)malloc(sizeof(struct Treenode));
    temp->tree_tk.token = node->tree_tk.token;
    temp->right_sibling = NULL;
    temp->left_sibling = NULL;
    temp->first_child = child1;
    Treenode *temp1 = child1;
    Treenode *prev = child1;
    if (child1)
    {
        while (temp1 != NULL)
        {
            temp1->parent = temp;
            prev = temp1;
            temp1 = temp1->right_sibling;
        }
    }

    if (child2)
    {
        Treenode *ptr = prev;
        ptr->right_sibling = child2;
        child2->left_sibling = ptr;
        child2->right_sibling = NULL;
        child2->parent = temp;
    }
    else
    {
        prev->right_sibling = NULL;
    }
    return temp;
}

Treenode *make_node4(char *name, Treenode *child1, Treenode *child2, Treenode *child3, Treenode *child4)
{
    Treenode *temp = (Treenode *)malloc(sizeof(struct Treenode));
    temp->tree_tk.token = name;
    temp->right_sibling = NULL;
    temp->left_sibling = NULL;
    temp->first_child = child1;
    Treenode *temp1 = child1;
    Treenode *prev = temp1;
    if (child1)
    {
        while (temp1 != NULL)
        {
            temp1->parent = temp;
            prev = temp1;
            temp1 = temp1->right_sibling;
        }
    }

    if (child2)
    {
        Treenode *ptr = prev;
        ptr->right_sibling = child2;
        child2->left_sibling = ptr;
        child2->right_sibling = NULL;
        child2->parent = temp;
    }
    else
    {
        prev->right_sibling = NULL;
        return temp;
    }

    if (child3)
    {
        Treenode *ptr = child2;
        ptr->right_sibling = child3;
        child3->left_sibling = ptr;
        child3->right_sibling = NULL;
        child3->parent = temp;
    }
    else
    {
        child2->right_sibling = NULL;
        return temp;
    }

    if (child4)
    {
        Treenode *ptr = child3;
        ptr->right_sibling = child4;
        child4->left_sibling = ptr;
        child4->right_sibling = NULL;
        child4->parent = temp;
    }
    else
    {
        child3->right_sibling = NULL;
        return temp;
    }
    return temp;
}

void free_ptr(Treenode *parent, char *name)
{
    Treenode *temp = parent->first_child;
    if (strcmp(temp->tree_tk.token, name) == 0)
    {
        parent->first_child = temp->right_sibling;
        if (temp->right_sibling)
        {
            temp->right_sibling->left_sibling = NULL;
        }
        free(temp);
        return;
    }

    while (temp != NULL)
    {
        if (!strcmp(temp->tree_tk.token, name))
        {
            temp->left_sibling->right_sibling = temp->right_sibling;
            if (temp->right_sibling != NULL)
                temp->right_sibling->left_sibling = temp->left_sibling;
            temp->right_sibling = NULL;
            temp->left_sibling = NULL;
            free(temp);
        }
        temp = temp->right_sibling;
    }
}

Treenode *make_list(Treenode *temp)
{
    return temp;
}

Treenode *insert_end_node(Treenode *ptr, Treenode *end)
{
    end->right_sibling = NULL;
    Treenode *temp1 = ptr;
    while (temp1->right_sibling != NULL)
    {
        temp1 = temp1->right_sibling;
    }
    temp1->right_sibling = end;
    end->left_sibling = temp1;
    end->parent = ptr->parent;
    return ptr;
}

Treenode *insert_head(Treenode *ptr, Treenode *node)
{
    if (ptr != NULL && ptr->parent != NULL)
        ptr->parent->first_child = node;
    node->right_sibling = ptr;
    if (ptr != NULL)
    {
        ptr->left_sibling = node;
        node->parent = ptr->parent;
    }
    return node;
}

Treenode *AST(int syn_inh, Treenode *t_node)
{
    switch (t_node->rule_no)
    {

    case 1:
        if (syn_inh == 0)
        {
            Treenode *child1 = iterate_child(t_node, "MODULEDECLARATIONS");
            Treenode *child2 = child1->right_sibling;
            Treenode *child3 = child2->right_sibling;
            Treenode *child4 = child3->right_sibling;
            child1->list_syn = AST(0, child1);
            child2->list_syn = AST(0, child2);
            child3->syn = AST(0, child3);
            child4->list_syn = AST(0, child4);
            t_node->syn = make_node4("MAIN_PROG", make_node("AST_MODULEDECLARATIONS", child1->list_syn, NULL),
                                     make_node("AST_OTHERMODULES", child2->list_syn, NULL),
                                     child3->syn,
                                     make_node("AST_OTHERMODULES", child4->list_syn, NULL));
            free_ptr(t_node, "MODULEDECLARATIONS");
            free_ptr(t_node, "OTHERMODULES");
            free_ptr(t_node, "DRIVERMODULE");
            free_ptr(t_node, "OTHERMODULES");
            return t_node->syn;
        }
        break;
    case 2:
        if (syn_inh == 0)
        {
            Treenode *child1 = iterate_child(t_node, "MODULEDECLARATION");
            Treenode *child2 = child1->right_sibling;
            child1->syn = AST(0, child1);
            child2->list_syn = AST(0, child2);
            t_node->list_syn = insert_head(child2->list_syn, child1->syn);
            free_ptr(t_node, "MODULEDECLARATION");
            free_ptr(t_node, "MODULEDECLARATIONS");
            return t_node->list_syn;
        }
        break;
    case 3:
        if (syn_inh == 0)
        {
            return t_node->list_syn = NULL;
        }
        break;
    case 4:
        if (syn_inh == 0)
        {
            t_node->syn = iterate_child(t_node, "id");
            free_ptr(t_node, "declare");
            free_ptr(t_node, "module");
            free_ptr(t_node, "semicol");
            return t_node->syn;
        }
        break;
    case 5:
        if (syn_inh == 0)
        {
            Treenode *child1 = iterate_child(t_node, "MODULE");
            Treenode *child2 = child1->right_sibling;
            child1->syn = AST(0, child1);
            child2->list_syn = AST(0, child2);
            t_node->list_syn = insert_head(child2->list_syn, child1->syn);
            free_ptr(t_node, "MODULE");
            free_ptr(t_node, "OTHERMODULES");
            return t_node->list_syn;
        }
        break;

    case 6:
        if (syn_inh == 0)
        {
            free_ptr(t_node, "epsilon");
            return t_node->list_syn = NULL;
        }

    case 7:
        if (syn_inh == 0)
        {
            Treenode *child1 = iterate_child(t_node, "MODULEDEF");
            child1->syn = AST(0, child1);
            t_node->syn = make_node("AST_DRIVERDEF", child1->syn, NULL);
            free_ptr(t_node, "driverdef");
            free_ptr(t_node, "driver");
            free_ptr(t_node, "program");
            free_ptr(t_node, "driverenddef");
            free_ptr(t_node, "MODULEDEF");
            return t_node->syn;
        }
        break;

    case 8:
        if (syn_inh == 0)
        {
            Treenode *child1 = iterate_child(t_node, "INPUT_PLIST");
            Treenode *child2 = iterate_child(t_node, "RET");
            Treenode *child3 = iterate_child(t_node, "MODULEDEF");
            child1->list_syn = AST(0, child1);
            child2->syn = AST(0, child2);
            child3->syn = AST(0, child3);
            t_node->syn = make_node4("AST_MODULE", iterate_child(t_node, "id"), make_node("INPUT_PARAMETERS", child1->list_syn, NULL), child2->syn, child3->syn);
            free_ptr(t_node, "def");
            free_ptr(t_node, "module");
            free_ptr(t_node, "enddef");
            free_ptr(t_node, "takes");
            free_ptr(t_node, "input");
            free_ptr(t_node, "sqbo");
            free_ptr(t_node, "INPUT_PLIST");
            free_ptr(t_node, "sqbc");
            free_ptr(t_node, "semicol");
            free_ptr(t_node, "RET");
            free_ptr(t_node, "MODULEDEF");
            return t_node->syn;
        }
        break;
    case 9:
        if (syn_inh == 0)
        {
            Treenode *child1 = iterate_child(t_node, "OUTPUT_PLIST");
            child1->list_syn = AST(0, child1);
            t_node->syn = make_node("OUTPUT_PARAMETERS", child1->list_syn, NULL);
            free_ptr(t_node, "returns");
            free_ptr(t_node, "sqbo");
            free_ptr(t_node, "OUTPUT_PLIST");
            free_ptr(t_node, "sqbc");
            free_ptr(t_node, "semicol");
            return t_node->syn;
        }
        break;
    case 10:
        if (syn_inh == 0)
        {
            t_node->syn = make_node("OUTPUT_PARAMETERS", NULL, NULL);
            return t_node->syn;
        }
        break;
    case 11:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "INPUT_PLIST_ONE");
            child->list_syn = AST(0, child);
            t_node->list_syn = child->list_syn;
            free_ptr(t_node, "colon");
            free_ptr(t_node, "DATATYPE");
            free_ptr(t_node, "INPUT_PLIST_ONE");
            return t_node->list_syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *child1 = iterate_child(t_node, "DATATYPE");
            Treenode *child2 = iterate_child(t_node, "INPUT_PLIST_ONE");
            child1->syn = AST(0, child1);
            child2->list_inh = make_list(child1->syn);
            child2->list_inh = insert_end_node(child2->list_inh, iterate_child(t_node, "id"));
            return child2->list_inh;
        }
        break;

    case 12:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "INPUT_PLIST_ONE");
            child->list_syn = AST(0, child);
            t_node->list_syn = child->list_syn;
            free_ptr(t_node, "comma");
            free_ptr(t_node, "colon");
            free_ptr(t_node, "DATATYPE");
            free_ptr(t_node, "INPUT_PLIST_ONE");
            return t_node->list_syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *child1 = iterate_child(t_node, "DATATYPE");
            Treenode *child2 = iterate_child(t_node, "INPUT_PLIST_ONE");
            child1->syn = AST(0, child1);
            t_node->list_inh = AST(1, t_node->parent);
            child2->list_inh = insert_end_node(t_node->list_inh, child1->syn);
            child2->list_inh = insert_end_node(t_node->list_inh, iterate_child(t_node, "id"));
            return t_node->list_inh;
        }
        break;
    case 13:
        if (syn_inh == 0)
        {
            t_node->list_inh = AST(1, t_node->parent);
            free_ptr(t_node, "epsilon");
            t_node->list_syn = t_node->list_inh;
            return t_node->list_syn;
        }
        break;
    case 14:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "OUTPUT_PLIST_ONE");
            child->list_syn = AST(0, child);
            t_node->list_syn = child->list_syn;
            free_ptr(t_node, "colon");
            free_ptr(t_node, "TYPE");
            free_ptr(t_node, "OUTPUT_PLIST_ONE");
            return t_node->list_syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *child1 = iterate_child(t_node, "TYPE");
            Treenode *child2 = iterate_child(t_node, "OUTPUT_PLIST_ONE");
            child1->syn = AST(0, child1);
            child2->list_inh = make_list(child1->syn);
            child2->list_inh = insert_end_node(child2->list_inh, iterate_child(t_node, "id"));
            return child2->list_inh;
        }
        break;
    case 15:
        if (syn_inh == 0)
        {
            Treenode *child1 = iterate_child(t_node, "OUTPUT_PLIST_ONE");
            child1->list_syn = AST(0, child1);
            t_node->list_syn = child1->list_syn;
            free_ptr(t_node, "comma");
            free_ptr(t_node, "colon");
            free_ptr(t_node, "TYPE");
            free_ptr(t_node, "OUTPUT_PLIST_ONE");
            return t_node->list_syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *child1 = iterate_child(t_node, "TYPE");
            Treenode *child2 = iterate_child(t_node, "OUTPUT_PLIST_ONE");
            child1->syn = AST(0, child1);
            t_node->list_inh = AST(1, t_node->parent);
            child2->list_inh = insert_end_node(t_node->list_inh, child1->syn);
            child2->list_inh = insert_end_node(t_node->list_inh, iterate_child(t_node, "id"));
            return child2->list_inh;
        }
        break;

    case 16:
        if (syn_inh == 0)
        {
            t_node->list_inh = AST(1, t_node->parent);
            free_ptr(t_node, "epsilon");
            return t_node->list_syn = t_node->list_inh;
        }
        break;
    case 17:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "integer");
        }
        break;
    case 18:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "real");
        }
        break;
    case 19:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "boolean");
        }

    case 20:
        if (syn_inh == 0)
        {
            Treenode *child1 = iterate_child(t_node, "TYPE");
            Treenode *child2 = iterate_child(t_node, "RANGE_ARRAYS");
            child1->syn = AST(0, child1);
            child2->syn = AST(0, child2);
            t_node->syn = make_node("ARRAY_DATATYPE", child1->syn, child2->syn);
            free_ptr(t_node, "array");
            free_ptr(t_node, "sqbo");
            free_ptr(t_node, "RANGE_ARRAYS");
            free_ptr(t_node, "sqbc");
            free_ptr(t_node, "of");
            free_ptr(t_node, "TYPE");
            return t_node->syn;
        }
        break;

    case 21:
        if (syn_inh == 0)
        {
            Treenode *child1 = t_node->first_child;
            Treenode *child2 = (child1->right_sibling)->right_sibling;
            child1->syn = AST(0, child1);
            child2->syn = AST(0, child2);
            t_node->syn = make_node("..", child1->syn, child2->syn);
            free_ptr(t_node, "rangeop");
            free_ptr(t_node, "INDEX_ARR");
            free_ptr(t_node, "INDEX_ARR");
            return t_node->syn;
        }
        break;

    case 22:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "integer");
        }
        break;
    case 23:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "real");
        }
        break;
    case 24:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "boolean");
        }
        break;
    case 25:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "STATEMENTS");
            child->list_syn = AST(0, child);
            // Treenode *end_node = iterate_child(t_node, "end");
            t_node->syn = make_node("STMT_LIST", child->list_syn, NULL);
            free_ptr(t_node, "start");
            free_ptr(t_node, "STATEMENTS");
            free_ptr(t_node, "end");
            return t_node->syn;
        }
        break;
    case 26:
        if (syn_inh == 0)
        {
            Treenode *child2 = iterate_child(t_node, "STATEMENT");
            Treenode *child1 = iterate_child(t_node, "STATEMENTS");
            child1->list_syn = AST(0, child1);
            child2->syn = AST(0, child2);
            t_node->list_syn = insert_head(child1->list_syn, child2->syn);
            free_ptr(t_node, "STATEMENTS");
            free_ptr(t_node, "STATEMENT");
            return t_node->list_syn;
        }
        break;

    case 27:
        if (syn_inh == 0)
        {
            free_ptr(t_node, "epsilon");
            return t_node->list_syn = NULL;
        }
        break;

    case 28:
        if (syn_inh == 0)
        {
            Treenode *child = t_node->first_child;
            t_node->syn = AST(0, child);
            free_ptr(t_node, "IOSTMT");
            return t_node->syn;
        }
        break;
    case 29:
        if (syn_inh == 0)
        {
            Treenode *child = t_node->first_child;
            t_node->syn = AST(0, child);
            free_ptr(t_node, "SIMPLESTMT");
            return t_node->syn;
        }
        break;
    case 30:
        if (syn_inh == 0)
        {
            Treenode *child = t_node->first_child;
            t_node->syn = AST(0, child);
            free_ptr(t_node, "DECLARESTMT");
            return t_node->syn;
        }
        break;
    case 31:
        if (syn_inh == 0)
        {
            Treenode *child = t_node->first_child;
            t_node->syn = AST(0, child);
            free_ptr(t_node, "CONDITIONALSTMT");
            return t_node->syn;
        }
        break;
    case 32:
        if (syn_inh == 0)
        {
            Treenode *child = t_node->first_child;
            t_node->syn = AST(0, child);
            free_ptr(t_node, "ITERATIVESTMT");
            return t_node->syn;
        }
        break;

    case 33:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "id");
            Treenode *temp = child;
            t_node->syn = make_node("SCANSTMT", temp, NULL);
            free_ptr(t_node, "get_value");
            free_ptr(t_node, "bo");
            free_ptr(t_node, "bc");
            free_ptr(t_node, "semicol");
            return t_node->syn;
        }
        break;

    case 34:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "VAR_PRINT");
            child->syn = AST(0, child);
            t_node->syn = make_node("PRINTSTMT", child->syn, NULL);
            free_ptr(t_node, "print");
            free_ptr(t_node, "bo");
            free_ptr(t_node, "VAR_PRINT");
            free_ptr(t_node, "bc");
            free_ptr(t_node, "semicol");
            return t_node->syn;
        }
        break;

    case 35:
        if (syn_inh == 0)
        {
            Treenode *child = t_node->first_child;
            return t_node->syn = child;
        }
        break;
    case 36:
        if (syn_inh == 0)
        {
            Treenode *child = t_node->first_child;
            return t_node->syn = child;
        }
        break;

    case 37:
        if (syn_inh == 0)
        {
            Treenode *child = t_node->first_child->right_sibling;
            t_node->syn = AST(0, child);
            free_ptr(t_node, "VAR_PRINT_ONE");
            return t_node->syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *child = t_node->first_child;
            return t_node->inh = child;
        }
        break;

    case 38:
        if (syn_inh == 0)
        {
            Treenode *child = t_node->first_child;
            return t_node->syn = child;
        }
        break;
    case 39:
        if (syn_inh == 0)
        {
            Treenode *child = t_node->first_child;
            return t_node->syn = child;
        }
        break;

    case 40:
        if (syn_inh == 0)
        {
            Treenode *child = t_node->first_child;
            t_node->syn = AST(0, child);
            free_ptr(t_node, "BOOLCONSTT");
            return t_node->syn;
        }
        break;

    case 41:
        if (syn_inh == 0)
        {
            Treenode *child1 = iterate_child(t_node, "SIGN");
            Treenode *child2 = iterate_child(t_node, "NEW_INDEX");
            child1->syn = AST(0, child1);
            child2->syn = AST(0, child2);
            t_node->syn = make_node("ARRAY_ADDR", make_node("INDEX_ARR", child2->syn, child1->syn), NULL);
            free_ptr(t_node, "sqbo");
            free_ptr(t_node, "SIGN");
            free_ptr(t_node, "NEW_INDEX");
            free_ptr(t_node, "sqbc");
            return t_node->syn;
        }
        break;

    case 42:
        if (syn_inh == 0)
        {
            t_node->inh = AST(1, t_node->parent);
            free_ptr(t_node, "epsilon");
            return t_node->syn = t_node->inh;
        }
        break;

    case 43:
        if (syn_inh == 0)
        {
            Treenode *child = t_node->first_child;
            child->syn = AST(0, child);
            t_node->syn = child->syn;
            free_ptr(t_node, "ASSIGNMENTSTMT");
            return t_node->syn;
        }
        break;

    case 44:
        if (syn_inh == 0)
        {
            Treenode *child = t_node->first_child;
            child->syn = AST(0, child);
            t_node->syn = child->syn;
            free_ptr(t_node, "MODULEREUSESTMT");
            return t_node->syn;
        }
        break;

    case 45:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "WHICHSTMT");
            child->syn = AST(0, child);
            t_node->syn = child->syn;
            free_ptr(t_node, "WHICHSTMT");
            return t_node->syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *child1 = t_node->first_child;
            Treenode *child2 = iterate_child(t_node, "WHICHSTMT");
            free_ptr(t_node, "WHICHSTMT");
            return child2->inh = child1;
        }
        break;

    case 46:
        if (syn_inh == 0)
        {
            Treenode *child = t_node->first_child;
            t_node->syn = AST(0, child);
            free_ptr(t_node, "ONEVALUEIDSTMT");
            return t_node->syn;
        }

        else if (syn_inh == 1)
        {
            Treenode *child = t_node->first_child;
            t_node->inh = AST(1, t_node->parent);
            return child->inh = t_node->inh;
        }
        break;

    case 47:
        if (syn_inh == 0)
        {
            Treenode *child = t_node->first_child;
            t_node->syn = AST(0, child);
            free_ptr(t_node, "ONEVALUEARRSTMT");
            return t_node->syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *child = t_node->first_child;
            t_node->inh = AST(1, t_node->parent);
            return child->inh = t_node->inh;
        }
        break;

    case 48:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "EXPRESSION");
            t_node->inh = AST(1, t_node->parent);
            child->syn = AST(0, child);
            t_node->syn = make_node("ASSIGN", t_node->inh, child->syn);
            free_ptr(t_node, "assignop");
            free_ptr(t_node, "EXPRESSION");
            free_ptr(t_node, "semicol");
            return t_node->syn;
        }
        break;

    case 49:
        if (syn_inh == 0)
        {
            Treenode *child1 = iterate_child(t_node, "ELEMENT_INDEX_WITH_EXPRESSIONS");
            Treenode *child2 = iterate_child(t_node, "EXPRESSION");
            t_node->inh = AST(1, t_node->parent);
            child1->syn = AST(0, child1);
            child2->syn = AST(0, child2);
            t_node->syn = make_node("ASSIGN", make_node("ARRAY_ADDR", t_node->inh, child1->syn), child2->syn);
            free_ptr(t_node, "sqbo");
            free_ptr(t_node, "ELEMENT_INDEX_WITH_EXPRESSIONS");
            free_ptr(t_node, "sqbc");
            free_ptr(t_node, "assignop");
            free_ptr(t_node, "EXPRESSION");
            free_ptr(t_node, "semicol");
            return t_node->syn;
        }
        break;

    case 50:
        if (syn_inh == 0)
        {
            Treenode *child1 = iterate_child(t_node, "SIGN");
            Treenode *child2 = iterate_child(t_node, "NEW_INDEX");
            child1->syn = AST(0, child1);
            child2->syn = AST(0, child2);
            t_node->syn = make_node("INDEX_EXPR", child2->syn, child1->syn);
            free_ptr(t_node,"SIGN");
            free_ptr(t_node, "NEW_INDEX");
            return t_node->syn;
        }
        break;

    case 51:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "num");
        }
        break;
    case 52:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "id");
        }
        break;
    case 53:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "plus");
        }
        break;
    case 54:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "minus");
        }
        break;
    case 55:
        if (syn_inh == 0)
        {
            free_ptr(t_node, "epsilon");
            return t_node->syn = NULL;
        }
        break;

    case 56:
        if (syn_inh == 0)
        {
            Treenode *child1 = iterate_child(t_node, "OPTIONAL");
            Treenode *child2 = iterate_child(t_node, "ACTUAL_PARA_LIST");
            Treenode *child3 = iterate_child(t_node, "id");
            child1->list_syn = AST(0, child1);
            child2->list_syn = AST(0, child2);
            t_node->syn = make_node4("INVOKE_FUNCTION", child3, make_node("OPTIONAL_PARAMETERS", child1->list_syn, NULL), make_node("ACTUAL_PARAMETERS", child2->list_syn, NULL), NULL);
            free_ptr(t_node, "OPTIONAL");
            free_ptr(t_node, "use");
            free_ptr(t_node, "module");
            free_ptr(t_node, "with");
            free_ptr(t_node, "parameters");
            free_ptr(t_node, "ACTUAL_PARA_LIST");
            free_ptr(t_node, "semicol");
            return t_node->syn;
        }
        break;

    case 57:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "ACTUAL_PARA_LIST_TWO");
            child->list_syn = AST(0, child);
            t_node->list_syn = child->list_syn;
            free_ptr(t_node, "SIGN");
            free_ptr(t_node, "K_OLD");
            free_ptr(t_node, "ACTUAL_PARA_LIST_TWO");
            return t_node->list_syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *child1 = iterate_child(t_node, "ACTUAL_PARA_LIST_TWO");
            Treenode *child2 = iterate_child(t_node, "SIGN");
            Treenode *child3 = iterate_child(t_node, "K_OLD");
            child2->syn = AST(0, child2);
            child3->syn = AST(0, child3);
            return child1->list_inh = make_list(make_node("PARAM_EXPR", child3->syn, child2->syn));
        }
        break;

    case 58:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "ACTUAL_PARA_LIST_TWO");
            child->list_syn = AST(0, child);
            t_node->list_syn = child->list_syn;
            free_ptr(t_node, "comma");
            free_ptr(t_node, "SIGN");
            free_ptr(t_node, "K_OLD");
            free_ptr(t_node, "ACTUAL_PARA_LIST_TWO");
            return t_node->list_syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *child1 = iterate_child(t_node, "ACTUAL_PARA_LIST_TWO");
            Treenode *child2 = iterate_child(t_node, "SIGN");
            Treenode *child3 = iterate_child(t_node, "K_OLD");
            t_node->list_inh = AST(1, t_node->parent);
            child2->syn = AST(0, child2);
            child3->syn = AST(0, child3);
            return child1->list_inh = insert_end_node(t_node->list_inh, make_node("PARAM_EXPR", child3->syn, child2->syn));
        }
        break;

    case 59:
        if (syn_inh == 0)
        {
            t_node->list_inh = AST(1, t_node->parent);
            t_node->list_syn = t_node->list_inh;
            free_ptr(t_node, "epsilon");
            return t_node->list_syn;
        }
        break;

    case 60:
        if (syn_inh == 0)
        {
            return t_node->syn = t_node->first_child;
        }
        break;

    case 61:
        if (syn_inh == 0)
        {
            return t_node->syn = t_node->first_child;
        }
        break;

    case 62:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "BOOLCONSTT");
            child->syn = AST(0, child);
            t_node->syn = child->syn;
            free_ptr(t_node, "BOOLCONSTT");
            return t_node->syn;
        }
        break;

    case 63:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "N_ELEVEN");
            child->syn = AST(0, child);
            t_node->syn = child->syn;
            free_ptr(t_node, "N_ELEVEN");
            return t_node->syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *child = iterate_child(t_node, "N_ELEVEN");
            return child->inh = t_node->first_child;
        }
        break;

    case 64:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "IDLIST");
            child->list_syn = AST(0, child);
            t_node->list_syn = child->list_syn;
            free_ptr(t_node, "sqbo");
            free_ptr(t_node, "IDLIST");
            free_ptr(t_node, "sqbc");
            free_ptr(t_node, "assignop");
            return t_node->list_syn;
        }
        break;

    case 65:
        if (syn_inh == 0)
        {
            free_ptr(t_node, "epsilon");
            return t_node->list_syn = NULL;
        }
        break;

    case 66:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "IDLIST_ONE");
            child->list_syn = AST(0, child);
            t_node->list_syn = child->list_syn;
            free_ptr(t_node, "IDLIST_ONE");
            return t_node->list_syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *child = iterate_child(t_node, "IDLIST_ONE");
            return child->list_inh = make_list(iterate_child(t_node, "id"));
        }
        break;
    case 67:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "IDLIST_ONE");
            t_node->list_syn = AST(0, child);
            free_ptr(t_node, "comma");
            free_ptr(t_node, "IDLIST_ONE");
            return t_node->list_syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *child = iterate_child(t_node, "IDLIST_ONE");
            t_node->list_inh = AST(1, t_node->parent);
            return child->list_inh = insert_end_node(t_node->list_inh, iterate_child(t_node, "id"));
        }
        break;

    case 68:
        if (syn_inh == 0)
        {
            t_node->list_inh = AST(1, t_node->parent);
            t_node->list_syn = t_node->list_inh;
            free_ptr(t_node, "epsilon");
            return t_node->list_syn;
        }
        break;

    case 69:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "ARITHMETICORBOOLEANEXPR");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "ARITHMETICORBOOLEANEXPR");
            return t_node->syn;
        }
        break;

    case 70:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "UNARY");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "UNARY");
            return t_node->syn;
        }
        break;

    case 71:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "NEW_NT");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "UNARY_OP");
            free_ptr(t_node, "NEW_NT");
            return t_node->syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *p = iterate_child(t_node, "NEW_NT");
            Treenode *q = iterate_child(t_node, "UNARY_OP");
            q->syn = AST(0, q);
            return p->inh = q->syn;
        }
        break;

    case 72:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "ARITHMETICEXPR");
            child->syn = AST(0, child);
            t_node->inh = AST(1, t_node->parent);
            t_node->syn = make_node("UNARYEXPR", t_node->inh, child->syn);
            free_ptr(t_node, "bo");
            free_ptr(t_node, "ARITHMETICEXPR");
            free_ptr(t_node, "bc");
            return t_node->syn;
        }
        break;

    case 73:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "VAR_ID_NUM");
            child->syn = AST(0, child);
            t_node->syn = child->syn;
            free_ptr(t_node, "VAR_ID_NUM");
            return t_node->syn;
        }
        break;

    case 74:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "id");
        }
        break;

    case 75:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "num");
        }
        break;

    case 76:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "rnum");
        }
        break;

    case 77:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "plus");
        }
        break;

    case 78:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "minus");
        }
        break;

    case 79:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "ARITHMETICORBOOLEANEXPR_ONE");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "ANYTERM");
            free_ptr(t_node, "ARITHMETICORBOOLEANEXPR_ONE");
            return t_node->syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *p = iterate_child(t_node, "ARITHMETICORBOOLEANEXPR_ONE");
            Treenode *q = iterate_child(t_node, "ANYTERM");
            q->syn = AST(0, q);
            return p->inh = q->syn;
        }
        break;

    case 80:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "ARITHMETICORBOOLEANEXPR_ONE");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "LOGICALOP");
            free_ptr(t_node, "ANYTERM");
            free_ptr(t_node, "ARITHMETICORBOOLEANEXPR_ONE");
            return t_node->syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *p = iterate_child(t_node, "ARITHMETICORBOOLEANEXPR_ONE");
            Treenode *q = iterate_child(t_node, "LOGICALOP");
            Treenode *r = iterate_child(t_node, "ANYTERM");
            q->syn = AST(0, q);
            r->syn = AST(0, r);
            t_node->inh = AST(1, t_node->parent);
            return p->inh = make_node_wo_name(q->syn, t_node->inh, r->syn);
        }
        break;

    case 81:
        if (syn_inh == 0)
        {
            t_node->inh = AST(1, t_node->parent);
            t_node->syn = t_node->inh;
            free_ptr(t_node, "epsilon");
            return t_node->syn;
        }
        break;

    case 82:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "ANYTERM_ONE");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "ARITHMETICEXPR");
            free_ptr(t_node, "ANYTERM_ONE");
            return t_node->syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *p = iterate_child(t_node, "ANYTERM_ONE");
            Treenode *q = iterate_child(t_node, "ARITHMETICEXPR");
            q->syn = AST(0, q);
            return p->inh = q->syn;
        }
        break;

    case 83:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "BOOLCONSTT");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "BOOLCONSTT");
            return t_node->syn;
        }
        break;

    case 84:
        if (syn_inh == 0)
        {
            Treenode *child1 = iterate_child(t_node, "RELATIONALOP");
            Treenode *child2 = iterate_child(t_node, "ARITHMETICEXPR");
            t_node->inh = AST(1, t_node->parent);
            child1->syn = AST(0, child1);
            child2->syn = AST(0, child2);
            t_node->syn = make_node_wo_name(child1->syn, t_node->inh, child2->syn);
            free_ptr(t_node, "RELATIONALOP");
            free_ptr(t_node, "ARITHMETICEXPR");
            return t_node->syn;
        }
        break;

    case 85:
        if (syn_inh == 0)
        {
            t_node->inh = AST(1, t_node->parent);
            t_node->syn = t_node->inh;
            free_ptr(t_node, "epsilon");
            return t_node->syn;
        }
        break;

    case 86:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "ARITHMETICEXPR_ONE");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "TERM");
            free_ptr(t_node, "ARITHMETICEXPR_ONE");
            return t_node->syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *p = iterate_child(t_node, "ARITHMETICEXPR_ONE");
            Treenode *q = iterate_child(t_node, "TERM");
            q->syn = AST(0, q);
            return p->inh = q->syn;
        }
        break;

    case 87:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "ARITHMETICEXPR_ONE");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "OP_ONE");
            free_ptr(t_node, "TERM");
            free_ptr(t_node, "ARITHMETICEXPR_ONE");
            return t_node->syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *p = iterate_child(t_node, "ARITHMETICEXPR_ONE");
            Treenode *q = iterate_child(t_node, "OP_ONE");
            Treenode *r = iterate_child(t_node, "TERM");
            q->syn = AST(0, q);
            r->syn = AST(0, r);
            t_node->inh = AST(1, t_node->parent);
            return p->inh = make_node_wo_name(q->syn, t_node->inh, r->syn);
        }
        break;

    case 88:
        if (syn_inh == 0)
        {
            t_node->inh = AST(1, t_node->parent);
            t_node->syn = t_node->inh;
            free_ptr(t_node, "epsilon");
            return t_node->syn;
        }
        break;

    case 89:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "TERM_ONE");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "FACTOR");
            free_ptr(t_node, "TERM_ONE");
            return t_node->syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *p = iterate_child(t_node, "TERM_ONE");
            Treenode *q = iterate_child(t_node, "FACTOR");
            q->syn = AST(0, q);
            return p->inh = q->syn;
        }
        break;

    case 90:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "TERM_ONE");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "OP_TWO");
            free_ptr(t_node, "FACTOR");
            free_ptr(t_node, "TERM_ONE");
            return t_node->syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *p = iterate_child(t_node, "TERM_ONE");
            Treenode *q = iterate_child(t_node, "OP_TWO");
            Treenode *r = iterate_child(t_node, "FACTOR");
            q->syn = AST(0, q);
            r->syn = AST(0, r);
            t_node->inh = AST(1, t_node->parent);
            return p->inh = make_node_wo_name(q->syn, t_node->inh, r->syn);
        }
        break;

    case 91:
        if (syn_inh == 0)
        {
            t_node->inh = AST(1, t_node->parent);
            t_node->syn = t_node->inh;
            free_ptr(t_node, "epsilon");
            return t_node->syn;
        }
        break;

    case 92:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "ARITHMETICORBOOLEANEXPR");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "bo");
            free_ptr(t_node, "ARITHMETICORBOOLEANEXPR");
            free_ptr(t_node, "bc");
            return t_node->syn;
        }
        break;

    case 93:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "num");
        }
        break;

    case 94:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "rnum");
        }
        break;

    case 95:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "BOOLCONSTT");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "BOOLCONSTT");
            return t_node->syn;
        }
        break;

    case 96:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "N_ELEVEN");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "N_ELEVEN");
            return t_node->syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *p = iterate_child(t_node, "N_ELEVEN");
            return p->inh = iterate_child(t_node, "id");
        }
        break;

    case 97:
        if (syn_inh == 0)
        {
            Treenode *child1 = iterate_child(t_node, "ELEMENT_INDEX_WITH_EXPRESSIONS");
            child1->syn = AST(0, child1);
            t_node->inh = AST(1, t_node->parent);
            t_node->syn = make_node("ARRAY_ADDR", t_node->inh, child1->syn);
            free_ptr(t_node, "sqbo");
            free_ptr(t_node, "ELEMENT_INDEX_WITH_EXPRESSIONS");
            free_ptr(t_node, "sqbc");
            return t_node->syn;
        }
        break;

    case 98:
        if (syn_inh == 0)
        {
            t_node->inh = AST(1, t_node->parent);
            t_node->syn = t_node->inh;
            free_ptr(t_node, "epsilon");
            return t_node->syn;
        }
        break;

    case 99:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "N_TEN");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "SIGN");
            free_ptr(t_node, "N_TEN");
            return t_node->syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *p = iterate_child(t_node, "N_TEN");
            Treenode *q = iterate_child(t_node, "SIGN");
            q->syn = AST(0, q);
            return p->inh = q->syn;
        }
        break;

    case 100:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "ARREXPR");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "ARREXPR");
            return t_node->syn;
        }
        break;

    case 101:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "NEW_INDEX");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "NEW_INDEX");
            return t_node->syn;
        }
        break;

    case 102:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "ARREXPR");
            t_node->inh = AST(1, t_node->parent);
            child->syn = AST(0, child);
            t_node->syn = make_node("UNARYARREXPR", t_node->inh, child->syn);
            free_ptr(t_node, "bo");
            free_ptr(t_node, "ARREXPR");
            free_ptr(t_node, "bc");
            return t_node->syn;
        }
        break;

    case 103:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "ARR_N_FOUR");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "ARRTERM");
            free_ptr(t_node, "ARR_N_FOUR");
            return t_node->syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *p = iterate_child(t_node, "ARR_N_FOUR");
            Treenode *q = iterate_child(t_node, "ARRTERM");
            q->syn = AST(0, q);
            return p->inh = q->syn;
        }
        break;

    case 104:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "ARR_N_FOUR");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "OP_ONE");
            free_ptr(t_node, "ARRTERM");
            free_ptr(t_node, "ARR_N_FOUR");
            return t_node->syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *p = iterate_child(t_node, "OP_ONE");
            Treenode *q = iterate_child(t_node, "ARRTERM");
            Treenode *r = iterate_child(t_node, "ARR_N_FOUR");
            p->syn = AST(0, p);
            q->syn = AST(0, q);
            t_node->inh = AST(1, t_node->parent);
            return r->inh = make_node_wo_name(p->syn, t_node->inh, q->syn);
        }
        break;

    case 105:
        if (syn_inh == 0)
        {
            t_node->inh = AST(1, t_node->parent);
            t_node->syn = t_node->inh;
            free_ptr(t_node, "epsilon");
            return t_node->syn;
        }
        break;

    case 106:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "ARR_N_FIVE");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "ARRFACTOR");
            free_ptr(t_node, "ARR_N_FIVE");
            return t_node->syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *p = iterate_child(t_node, "ARR_N_FIVE");
            Treenode *q = iterate_child(t_node, "ARRFACTOR");
            q->syn = AST(0, q);
            return p->inh = q->syn;
        }
        break;

    case 107:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "ARR_N_FIVE");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "OP_TWO");
            free_ptr(t_node, "ARRFACTOR");
            free_ptr(t_node, "ARR_N_FIVE");
            return t_node->syn;
        }
        else if (syn_inh == 1)
        {
            Treenode *p = iterate_child(t_node, "OP_TWO");
            Treenode *q = iterate_child(t_node, "ARRFACTOR");
            Treenode *r = iterate_child(t_node, "ARR_N_FIVE");
            p->syn = AST(0, p);
            q->syn = AST(0, q);
            t_node->inh = AST(1, t_node->parent);
            return r->inh = make_node_wo_name(p->syn, t_node->inh, q->syn);
        }
        break;

    case 108:
        if (syn_inh == 0)
        {
            t_node->inh = AST(1, t_node->parent);
            t_node->syn = t_node->inh;
            free_ptr(t_node, "epsilon");
            return t_node->syn;
        }
        break;

    case 109:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "id");
        }
        break;

    case 110:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "num");
        }
        break;

    case 111:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "BOOLCONSTT");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "BOOLCONSTT");
            return t_node->syn;
        }
        break;

    case 112:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "ARREXPR");
            t_node->syn = AST(0, child);
            free_ptr(t_node, "bo");
            free_ptr(t_node, "ARREXPR");
            free_ptr(t_node, "bc");
            return t_node->syn;
        }
        break;

    case 113:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "plus");
        }
        break;

    case 114:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "minus");
        }
        break;

    case 115:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "mul");
        }
        break;

    case 116:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "div");
        }
        break;

    case 117:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "and");
        }
        break;

    case 118:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "or");
        }
        break;

    case 119:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "lt");
        }
        break;

    case 120:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "le");
        }
        break;

    case 121:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "gt");
        }
        break;

    case 122:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "ge");
        }
        break;

    case 123:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "eq");
        }
        break;

    case 124:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "ne");
        }
        break;

    case 125:
        if (syn_inh == 0)
        {
            Treenode *child1 = iterate_child(t_node, "IDLIST");
            Treenode *child2 = iterate_child(t_node, "DATATYPE");
            child1->list_syn = AST(0, child1);
            child2->syn = AST(0, child2);
            t_node->syn = make_node("AST_DECLARESTATEMENT", child2->syn, child1->list_syn);
            free_ptr(t_node, "declare");
            free_ptr(t_node, "IDLIST");
            free_ptr(t_node, "colon");
            free_ptr(t_node, "DATATYPE");
            free_ptr(t_node, "semicol");
            return t_node->syn;
        }
        break;

    case 126:
        if (syn_inh == 0)
        {
            Treenode *child3 = iterate_child(t_node, "id");
            Treenode *child1 = iterate_child(t_node, "CASESTMT");
            Treenode *child2 = iterate_child(t_node, "DEFAULT");
            child1->list_syn = AST(0, child1);
            child2->syn = AST(0, child2);
            child3->right_sibling = NULL;
            t_node->syn = make_node4("SWITCH_CASE", child3, make_node("CASE_NUM", child1->list_syn, NULL), child2->syn, NULL);
            free_ptr(t_node, "switch");
            free_ptr(t_node, "bo");
            free_ptr(t_node, "bc");
            free_ptr(t_node, "start");
            free_ptr(t_node, "CASESTMT");
            free_ptr(t_node, "DEFAULT");
            free_ptr(t_node, "end");
            return t_node->syn;
        }
        break;

    case 127:
        if (syn_inh == 0)
        {
            Treenode *child2 = iterate_child(t_node, "VALUE");
            Treenode *child3 = iterate_child(t_node, "STATEMENTS");
            Treenode *child1 = iterate_child(t_node, "CASESTMT_ONE");
            child1->list_syn = AST(0, child1);
            child2->syn = AST(0, child2);
            child3->list_syn = AST(0, child3);
            t_node->list_syn = insert_head(child1->list_syn, make_node("AST_CASE", child2->syn, make_node("STMT_LIST", child3->list_syn, NULL)));
            free_ptr(t_node, "case");
            free_ptr(t_node, "VALUE");
            free_ptr(t_node, "colon");
            free_ptr(t_node, "STATEMENTS");
            free_ptr(t_node, "break");
            free_ptr(t_node, "semicol");
            free_ptr(t_node, "CASESTMT_ONE");
            return t_node->list_syn;
        }
        break;

    case 128:
        if (syn_inh == 0)
        {
            Treenode *child1 = iterate_child(t_node, "VALUE");
            Treenode *child2 = iterate_child(t_node, "STATEMENTS");
            Treenode *child3 = iterate_child(t_node, "CASESTMT_ONE");
            child1->syn = AST(0, child1);
            child2->list_syn = AST(0, child2);
            child3->list_syn = AST(0, child3);
            t_node->list_syn = insert_head(child3->list_syn, make_node("AST_CASE", child1->syn, make_node("STMT_LIST", child2->list_syn, NULL)));
            free_ptr(t_node, "case");
            free_ptr(t_node, "VALUE");
            free_ptr(t_node, "colon");
            free_ptr(t_node, "STATEMENTS");
            free_ptr(t_node, "break");
            free_ptr(t_node, "semicol");
            free_ptr(t_node, "CASESTMT_ONE");
            return t_node->list_syn;
        }
        break;

    case 129:
        if (syn_inh == 0)
        {
            free_ptr(t_node, "epsilon");
            return t_node->list_syn = NULL;
        }
        break;

    case 130:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "num");
        }
        break;

    case 131:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "true");
        }
        break;

    case 132:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "false");
        }
        break;

    case 133:
        if (syn_inh == 0)
        {
            Treenode *child = iterate_child(t_node, "STATEMENTS");
            child->list_syn = AST(0, child);
            t_node->syn = make_node("AST_DEFAULT", make_node("STMT_LIST", child->list_syn, NULL), NULL);
            free_ptr(t_node, "default");
            free_ptr(t_node, "colon");
            free_ptr(t_node, "break");
            free_ptr(t_node, "semicol");
            free_ptr(t_node, "STATEMENTS");
            return t_node->syn;
        }
        break;

    case 134:
        if (syn_inh == 0)
        {
            free_ptr(t_node, "epsilon");
            return t_node->syn = NULL;
        }
        break;

    case 135:
        if (syn_inh == 0)
        {
            Treenode *child1 = iterate_child(t_node, "RANGE_FOR_LOOP");
            Treenode *child2 = iterate_child(t_node, "STATEMENTS");
            child1->syn = AST(0, child1);
            child2->list_syn = AST(0, child2);
            // Treenode *end_node = iterate_child(t_node, "end");
            t_node->syn = make_node4("FOR_STMT", iterate_child(t_node, "id"), child1->syn, make_node("STMT_LIST", child2->list_syn, NULL), NULL);
            free_ptr(t_node, "for");
            free_ptr(t_node, "bo");
            free_ptr(t_node, "in");
            free_ptr(t_node, "RANGE_FOR_LOOP");
            free_ptr(t_node, "bc");
            free_ptr(t_node, "start");
            free_ptr(t_node, "STATEMENTS");
            free_ptr(t_node, "end");
            return t_node->syn;
        }
        break;

    case 136:
        if (syn_inh == 0)
        {
            Treenode *child1 = iterate_child(t_node, "ARITHMETICORBOOLEANEXPR");
            Treenode *child2 = iterate_child(t_node, "STATEMENTS");
            child1->syn = AST(0, child1);
            child2->list_syn = AST(0, child2);
            // Treenode *end_node = iterate_child(t_node, "end");
            t_node->syn = make_node("WHILE_STMT", child1->syn, make_node("STMT_LIST", child2->list_syn, NULL));
            free_ptr(t_node, "while");
            free_ptr(t_node, "bo");
            free_ptr(t_node, "ARITHMETICORBOOLEANEXPR");
            free_ptr(t_node, "bc");
            free_ptr(t_node, "start");
            free_ptr(t_node, "STATEMENTS");
            free_ptr(t_node, "end");
            return t_node->syn;
        }
        break;

    case 137:
        if (syn_inh == 0)
        {
            Treenode *child1 = t_node->first_child;
            Treenode *child2 = child1->right_sibling->right_sibling;
            child1->syn = AST(0, child1);
            child2->syn = AST(0, child2);
            t_node->syn = make_node("..", child1->syn, child2->syn);
            free_ptr(t_node, "rangeop");
            free_ptr(t_node, "INDEX_FOR_LOOP");
            free_ptr(t_node, "INDEX_FOR_LOOP");
            return t_node->syn;
        }
        break;

    case 138:
        if (syn_inh == 0)
        {
            Treenode *child1 = iterate_child(t_node, "SIGN_FOR_LOOP");
            Treenode *child2 = iterate_child(t_node, "NEW_INDEX_FOR_LOOP");
            child1->syn = AST(0, child1);
            child2->syn = AST(0, child2);
            t_node->syn = make_node("INDEX_EXPR", child2->syn, child1->syn);
            free_ptr(t_node, "SIGN_FOR_LOOP");
            free_ptr(t_node, "NEW_INDEX_FOR_LOOP");
            return t_node->syn;
        }
        break;

    case 139:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "num");
        }
        break;

    case 140:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "plus");
        }
        break;

    case 141:
        if (syn_inh == 0)
        {
            return t_node->syn = iterate_child(t_node, "minus");
        }
        break;

    case 142:
        if (syn_inh == 0)
        {
            free_ptr(t_node, "epsilon");
            return t_node->syn = NULL;
        }
        break;
    }
}

int traverseASTTree(Treenode *temp)
{
    int number_of_nodes_in_ast = 0;
    if (temp == NULL)
    {
        return 0;
    }

    number_of_nodes_in_ast += traverseASTTree(temp->first_child);

    if(strcmp(temp->tree_tk.token, "MAIN_PROG") == 0)
    {
        temp->parent = NULL;
    }
    
    printf("Node: %s", temp->tree_tk.token);
    
    if (temp->parent != NULL)
        printf(" Parent: %s\n", (temp->parent)->tree_tk.token);
    else
        printf(" Parent: NULL\n");
    number_of_nodes_in_ast += traverseASTTree(temp->right_sibling);

    return number_of_nodes_in_ast+1;
}

void removerule0(Treenode *temp)
{
    if (temp == NULL)
    {
        return;
    }

    removerule0(temp->first_child);
    if (strcmp(temp->tree_tk.token, "OTHERMODULES") == 0 && temp->first_child != NULL && strcmp(temp->first_child->tree_tk.token, "epsilon") == 0 && temp->rule_no == 0)
    {
        temp->rule_no = 6;
    }
    removerule0(temp->right_sibling);
}