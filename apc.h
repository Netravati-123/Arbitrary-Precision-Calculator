#ifndef APC_H
#define APC_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node
{
    int data;
    struct node *prev;
    struct node *next;
} Dlist;

/* DLL functions */
int insert_last(Dlist **head, Dlist **tail, int data);
int insert_first(Dlist **head, Dlist **tail, int data);
void print_list(Dlist *head);
void delete_list(Dlist **head, Dlist **tail);

/* APC functions */
int store_operand(Dlist **head, Dlist **tail, char *str);
int compare_lists(Dlist *head1,Dlist*head2);
int is_zero(Dlist *head);

int addition(Dlist *tail1, Dlist *tail2,Dlist **result_head, Dlist **result_tail);
int subtraction(Dlist *tail1, Dlist *tail2, Dlist **result_head, Dlist **result_tail);
int multiplication(Dlist *tail1, Dlist *tail2, Dlist **result_head, Dlist **result_tail);            
int division(Dlist *head1, Dlist *head2, Dlist **result_head, Dlist **result_tail);            

#endif