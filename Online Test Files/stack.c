// Group - 4
// Aryan Desai - 2020A7PS0123P
// Ramakant Pandurang Talankar - 2020A7PS0979P
// Jaysheel Shah - 2020A7PS0083P
// Deepam Desai - 2020A7PS0971P
// Rachit Agrawal - 2020A7PS0033P

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

stack* create()
{
    stack* stack1 = (stack *)malloc(sizeof(stack));
    stack1->top_element_index = 0;
    stack1->size = STACK_SIZE;
    stack1->array = (stack_node *)malloc(STACK_SIZE * sizeof(stack_node));
    return stack1;
}

void push_element(stack *stack, TOKEN tk, Treenode *tree_address)
{
    if (stack->top_element_index >= STACK_SIZE - 1)
    {
        perror("Stack is Full, please increase stack size \n");
    }
    else
    {
        stack->array[stack->top_element_index].tk_stk = tk;
        stack->array[stack->top_element_index].treenode = tree_address;
        stack->top_element_index += 1; 
    }
}

void pop_element(stack *stack)
{
    if (stack->top_element_index == 0)
    {
        perror("Stack is Empty, no element to pop \n");
    }
    else
    {
        stack->top_element_index -= 1;
    }
}

stack_node top_element(stack *stack)
{
    if (stack->top_element_index == 0)
    {
        perror("Stack is Empty, no top element \n");
    }
    else
    {
        return (stack->array[(stack->top_element_index)-1]);
    }
}