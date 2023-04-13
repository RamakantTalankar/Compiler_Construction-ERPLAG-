// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_table.h"

map create_hashtable()
{
    map ht;
    ht = (map)malloc(26 * sizeof(struct hashtable));
    for (int i = 0; i < 26; i++)
    {
        ((ht[i].hash_array)) = NULL;
    }
    return ht;
}

h_node create_node(char *k, char *t)
{
    h_node new = (h_node)malloc(sizeof(struct HTNode));
    (new->key) = k;
    new->next = NULL;
    (new->token) = t;
    return new;
}

int hashfunction(char *k)
{
    
    if(strcmp(k,"AND") == 0)
    {
        return 0; 
    } 
    if(strcmp(k,"OR") == 0)
    {
        return 'o' - 'a'; 
    }
    if (k[0] == '_' || (k[0]>='A' && k[0]<='Z') ) 
    {
        return 100;
    } 
    return abs(k[0] - 'a');
}

void insert_hashtable(map ht, char *k, char *t)
{

    int index = hashfunction(k);
    h_node new;
    new = create_node(k, t);

    if (ht[index].hash_array == NULL)
    {
        ht[index].hash_array = new;
    }
    else
    {
        h_node t = ht[index].hash_array;

        while (t->next != NULL)
        {
            t = t->next;
        }
        t->next = new;
    }
}

char *search_hashtable(map ht, char *k)
{
    int index = hashfunction(k);

    if (index == 100) 
    {
        return "not found";
    }

    if (ht[index].hash_array == NULL)
    {
        return "not found";
    }
    else
    {
        h_node nd = ht[index].hash_array;
        while (nd != NULL)
        {
            if (strlen(k) != strlen(nd->key))
                nd = nd->next;
            else
            {
                int flag = 1;
                for (int i = 0; i < strlen(k); i++)
                {
                    if (k[i] != nd->key[i])
                    {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1)
                {
                    return nd->token;
                }
                else
                {
                    nd = nd->next;
                }
            }
        }
    }
    return "not found";
}
