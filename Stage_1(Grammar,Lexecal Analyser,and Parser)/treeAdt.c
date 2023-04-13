// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#include <stdio.h>
#include <stdlib.h>
#include "treeAdt.h"
#include "parser.h"
#include <string.h>

Treenode *create_treenode(TOKEN tk)
{
    Treenode *new_node = (Treenode *)malloc(sizeof(Treenode));
    new_node->tree_tk = tk;
    new_node->right_sibling = NULL;
    new_node->first_child = NULL;
    new_node->left_sibling = NULL;
    new_node->right_sibling = NULL;
    return new_node;
}

Treenode *add_firstChild(Treenode *parent, TOKEN tk)
{
    Treenode *new_node = create_treenode(tk);
    return parent->first_child = new_node;
}

Treenode *add_sibling(Treenode *parent, TOKEN tk)
{
    Treenode *new_node = create_treenode(tk);
    Treenode *new_node1 = create_treenode(tk);
    new_node1 = parent;

    while (new_node1->right_sibling != NULL)
    {
        new_node1->no_of_sibling++;
        new_node1 = new_node1->right_sibling;
    }
    new_node1->right_sibling = new_node;
    new_node->left_sibling = new_node1;
    new_node1->no_of_sibling++;
    return new_node;
}

char* isLeafNode(Treenode *temp)
{
    if (temp->first_child == NULL)
        return "yes";
    else
        return "no";
}

void traverseTree(Treenode *temp, FILE *out_p)
{
    if (temp == NULL)
    {
        return;
    }

    traverseTree(temp->first_child, out_p);
    
    Treenode * find_parent = temp;
    while(find_parent->parent == NULL && find_parent->left_sibling != NULL)
    {
        find_parent = find_parent->left_sibling;
    }
    char *dash = "----";
    char *yes = "yes";
    char *no = "no";
    
    if (strcmp(find_parent->tree_tk.token, "PROGRAM") == 0)
    {
        fprintf(out_p, "%-30s %-30s %-30s %-30s %-30s %-30s %-30s\n", dash, dash, temp->tree_tk.token, dash, dash, no, temp->tree_tk.token);
    }
    else if (strcmp(find_parent->tree_tk.token, "epsilon") == 0)
    {
        fprintf(out_p, "%-30s %-30s %-30s %-30s %-30s %-30s %-30s\n", dash, dash, temp->tree_tk.token, dash, dash, yes, temp->tree_tk.token);
    }
    else if (!checkTerminal(temp->tree_tk.token))
    {
        if (temp->parent != NULL)
        {
            if (strcmp(temp->tree_tk.token, "num") == 0)
                fprintf(out_p, "%-30s %-30s %-30s %-30d %-30s %-30s %-30s\n", dash, dash, dash, temp->tree_tk.value_num, (temp->parent)->tree_tk.token, isLeafNode(temp), temp->tree_tk.token);
            else if (strcmp(temp->tree_tk.token, "rnum") == 0)
                fprintf(out_p, "%-30s %-30s %-30s %-30.20lf %-30s %-30s %-30s\n", dash, dash, dash, temp->tree_tk.value_rnum, (temp->parent)->tree_tk.token, isLeafNode(temp), temp->tree_tk.token);
            else
                fprintf(out_p, "%-30s %-30s %-30s %-30s %-30s %-30s %-30s\n", dash, dash, dash, dash, (temp->parent)->tree_tk.token, isLeafNode(temp), temp->tree_tk.token);
        }
        else
        {
            if (strcmp(temp->tree_tk.token, "num") == 0)
                fprintf(out_p, "%-30s %-30d %-30s %-30d %-30s %-30s %-30s\n", dash, temp->tree_tk.line_num, dash, temp->tree_tk.value_num, (find_parent->parent)->tree_tk.token, isLeafNode(temp), temp->tree_tk.token);
            else if (strcmp(temp->tree_tk.token, "rnum") == 0)
                fprintf(out_p, "%-30s %-30d %-30s %-30.20lf %-30s %-30s %-30s\n", dash, temp->tree_tk.line_num, dash, temp->tree_tk.value_rnum, (find_parent->parent)->tree_tk.token, isLeafNode(temp), temp->tree_tk.token);
            else
                fprintf(out_p, "%-30s %-30d %-30s %-30s %-30s %-30s %-30s\n", dash, temp->tree_tk.line_num, dash, dash, (find_parent->parent)->tree_tk.token, isLeafNode(temp), temp->tree_tk.token);
        }
    }
    else
    {
        if (temp->parent != NULL)
        {
            if (strcmp(temp->tree_tk.token, "num") == 0)
                fprintf(out_p, "%-30d %-30d %-30s %-30d %-30s %-30s, %-30s\n", temp->tree_tk.value_num, temp->tree_tk.line_num, temp->tree_tk.token, temp->tree_tk.value_num, (temp->parent)->tree_tk.token, isLeafNode(temp), dash);
            else if (strcmp(temp->tree_tk.token, "rnum") == 0)
                fprintf(out_p, "%-30.20lf %-30d %-30s %-30.20lf %-30s %-30s %-30s\n", temp->tree_tk.value_rnum, temp->tree_tk.line_num, temp->tree_tk.token, temp->tree_tk.value_rnum, (temp->parent)->tree_tk.token, isLeafNode(temp), dash);
            else
                fprintf(out_p, "%-30s %-30d %-30s %-30s %-30s %-30s %-30s\n", temp->tree_tk.value_id, temp->tree_tk.line_num, temp->tree_tk.token, dash, (temp->parent)->tree_tk.token, isLeafNode(temp), dash);
        }
        else
        {
            if (strcmp(temp->tree_tk.token, "num") == 0)
                fprintf(out_p, "%-30d %-30d %-30s %-30d %-30s %-30s %-30s\n", temp->tree_tk.value_num, temp->tree_tk.line_num, temp->tree_tk.token, temp->tree_tk.value_num, (find_parent->parent)->tree_tk.token, isLeafNode(temp), dash);
            else if (strcmp(temp->tree_tk.token, "rnum") == 0)
                fprintf(out_p, "%-30.20lf %-30d %-30s %-30.20lf %-30s %-30s %-30s\n", temp->tree_tk.value_rnum, temp->tree_tk.line_num, temp->tree_tk.token, temp->tree_tk.value_rnum, (find_parent->parent)->tree_tk.token, isLeafNode(temp), dash);
            else
                fprintf(out_p, "%-30s %-30d %-30s %-30s %-30s %-30s %-30s\n", temp->tree_tk.value_id, temp->tree_tk.line_num, temp->tree_tk.token, dash, (find_parent->parent)->tree_tk.token, isLeafNode(temp), dash);
        }
    }
    traverseTree(temp->right_sibling, out_p);
}