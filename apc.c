#include "apc.h"

int store_operand(Dlist **head, Dlist **tail, char *str)
{
    int i = 0;

    if (str[0] == '\0')
        return 1;

    while (str[i] != '\0')
    {
        if (!isdigit((unsigned char)str[i]))
            return 1;

        if (insert_last(head, tail, str[i] - '0'))
            return 1;

        i++;
    }

    return 0;
}

int compare_lists(Dlist *head1, Dlist *head2)
{
    int count1 = 0, count2 = 0;
    Dlist *temp1 = head1;
    Dlist *temp2 = head2;

    while (temp1 != NULL && temp1->data == 0 &&
           temp1->next != NULL)
    {
        temp1 = temp1->next;
    }

    while (temp2 != NULL && temp2->data == 0 &&
           temp2->next != NULL)
    {
        temp2 = temp2->next;
    }

    while (temp1 != NULL)
    {
        count1++;
        temp1 = temp1->next;
    }

    while (temp2 != NULL)
    {
        count2++;
        temp2 = temp2->next;
    }

    if (count1 > count2)
        return 1;

    if (count1 < count2)
        return -1;

    temp1 = head1;
    temp2 = head2;

    while (temp1 != NULL && temp1->data == 0 &&
           temp1->next != NULL)
    {
        temp1 = temp1->next;
    }

    while (temp2 != NULL && temp2->data == 0 &&
           temp2->next != NULL)
    {
        temp2 = temp2->next;
    }

    while (temp1 != NULL && temp2 != NULL)
    {
        if (temp1->data > temp2->data)
            return 1;

        if (temp1->data < temp2->data)
            return -1;

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return 0;
}

int addition(Dlist *tail1, Dlist *tail2,
             Dlist **result_head, Dlist **result_tail)
{
    int sum, carry = 0, digit;

    while (tail1 != NULL || tail2 != NULL || carry != 0)
    {
        sum = carry;

        if (tail1 != NULL)
        {
            sum += tail1->data;
            tail1 = tail1->prev;
        }

        if (tail2 != NULL)
        {
            sum += tail2->data;
            tail2 = tail2->prev;
        }

        digit = sum % 10;
        carry = sum / 10;

        if (insert_first(result_head, result_tail, digit))
            return 1;
    }

    return 0;
}

int subtraction(Dlist *tail1, Dlist *tail2,
                Dlist **result_head, Dlist **result_tail)
{
    int diff, borrow = 0;

    while (tail1 != NULL)
    {
        diff = tail1->data - borrow;
        borrow = 0;

        if (tail2 != NULL)
        {
            diff = diff - tail2->data;
            tail2 = tail2->prev;
        }

        if (diff < 0)
        {
            diff = diff + 10;
            borrow = 1;
        }

        if (insert_first(result_head, result_tail, diff))
            return 1;

        tail1 = tail1->prev;
    }

    return 0;
}