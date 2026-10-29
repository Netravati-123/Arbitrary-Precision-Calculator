#include "apc.h"

int insert_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *newnode = malloc(sizeof(Dlist));

    if (newnode == NULL)
        return 1;

    newnode->data = data;
    newnode->prev = *tail;
    newnode->next = NULL;

    if (*head == NULL) //check list is empty
    {
        *head = newnode;
        *tail = newnode;
    }
    else
    {
        (*tail)->next = newnode;
        *tail = newnode;
    }

    return 0;
}

int insert_first(Dlist **head, Dlist **tail, int data) //result must be from left to right
{
    Dlist *newnode = malloc(sizeof(Dlist));

    if (newnode == NULL)
        return 1;

    newnode->data = data;
    newnode->prev = NULL;
    newnode->next = *head;

    if (*head == NULL)
    {
        *head = newnode;
        *tail = newnode;
    }
    else
    {
        (*head)->prev = newnode;
        *head = newnode;
    }

    return 0;
}

void print_list(Dlist *head)            // Dispalying opernads and results
{
    while (head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }

    printf("\n");
}

void delete_list(Dlist **head, Dlist **tail) //clean up memory
{
    Dlist *temp;

    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    *tail = NULL;
}